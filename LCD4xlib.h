#include	<delays.h>
#include	"LCDdefs.h"

#define		LCD                 // to remove conflict with Hyperterminal routines

#define		E	PORTEbits.RE2
#define		RW	PORTEbits.RE1
#define		RS	PORTEbits.RE0
typedef const far rom char ROM;


void SendCmd(char);
void SendNibble(char);
void Wait4LCD(void);

void InitLCD(void)                  // initialize LCD in 4-bit mode, <RD3:RD0> = data
{
    char LCDstr[] = {0x33, 0x32, 0x28, 0x0C, 0x01, 0x06, '\0'};
    unsigned char i = 0;

    ANSELE = 0x00; TRISE = 0x00;    // RE2, RE1, RE0 are output pins
    ANSELD = 0x00;                  // PORTD digital port
   
    Delay10KTCYx(10);               // small initial delay
    while (LCDstr[i] != '\0')
	SendCmd(LCDstr[i++]);
}

void SendCmd(char cmd)              // send a command to the LCD
{
    RS = 0; RW = 0; E = 0;          // set LCD in command mode
    SendNibble((cmd >> 4) & 0x0F);  // send upper nibble of command
    SendNibble(cmd & 0x0F);         // send lower nibble of command
    Wait4LCD();
}

void SendChar(char ch)              // send a character to the LCD
{
    RS = 1; RW = 0; E = 0;          // set LCD in data mode
    SendNibble((ch >> 4) & 0x0F);   // send upper nibble of ASCII data
    SendNibble(ch & 0x0F);          // send lower nibble of ASCII data
    Wait4LCD();
}

void SendNibble(char ch)
{
    TRISD &= 0b10000000;            // RD6..RD0 are output pins (LCD bus)
    PORTD = (PORTD & 0xF0) | ch;    // send data to LCD W/O modifying upper nibble of PORTD
    E = 1;                          // +ve edge latches control state (RS/R_W)
    Delay10TCYx(2);                 // 20 cycles delay
    E = 0;                          // -ve edge latches data/command
}

void Wait4LCD(void)                 // Wait for the LCD busy flag to clear.
{ 
    unsigned char LoNibble, HiNibble, status;
	
    TRISD |= 0x0F;                  // switch data port to input
    RW = 1; RS = 0; E = 0;          // read busy flag
    do {
        E = 1;                      // provide logic high on E
        Nop();                      // 1 cycle delay
	HiNibble = PORTD << 4;      // read the high nibble
	E = 0;                      // provide falling edge
	E = 1;                      // provide logic high on E
        Nop();                      // 1 cycle delay
	LoNibble = PORTD & 0x0F;    // read the low nibble
	E = 0;                      // provide falling edge
	status = HiNibble | LoNibble;	// combine to form busy status and DD address
    } while (status & 0x80);        // test busy flag
}

// display null-terminated string (in ROM) at StartPos
void DispRomStr(char StartPos, ROM *Str)
{
    SendCmd(StartPos);
    while (*Str != '\0')
	SendChar(*Str++);
}

// display null-terminated string (in RAM) at StartPos
void DispRamStr(char StartPos, char *Str)
{
    SendCmd(StartPos);
    while (*Str != '\0')
        SendChar(*Str++);
}

// Display ASCII variable of specified length at StartPos.
void DispVarStr(char *Str, char StartPos, unsigned char NumOfChars)	
{
    unsigned char i;

    SendCmd(StartPos);
    for (i = 0; i < NumOfChars; i++)
	SendChar(*Str++);
}				

// Display a number of blank characters at StartPos.
void DispBlanks(char StartPos, unsigned char NumOfChars)	
{
	unsigned char i;

	SendCmd(StartPos);
	for (i = 0; i < NumOfChars; i++)
		SendChar(' ');					// send a blank character
}

// Convert BCD array of length Len to ASCII.
void Bcd2Asc(char *a, unsigned char Len)
{
    unsigned char i;
    for (i = 0; i < Len; i++)
        a[i] += '0';				// convert to ASCII
}

// Convert ASCII array of length Len to BCD.
void Asc2Bcd(char *a, unsigned char Len)
{
    unsigned char i;
    for (i = 0; i < Len; i++)
        a[i] &= 0x0F;				// convert to BCD
}


// Convert 8-bit N to ASCII characters and store in array a (starting with MSD)
void Bin2Asc(unsigned char N, char *a)				// max of 425 cycles
{
    a[2] = (N % 10) + '0';					// least significant ASCII digit
    N = N / 10;
    a[1] = (N % 10) + '0';					// middle significant ASCII digit
    a[0] = (N / 10) + '0';					// most significant ASCII digit
}

// Convert 16-bit N to ASCII characters and store in array a (starting with MSD)
void Bin2AscE(unsigned int N, char *a)				// max of 2212 cycles
{
    unsigned char i;

    for (i = 0; i < 4; i++)
    {
	a[4-i] = (N % 10) + '0';				// rem of division by 10 in ASCII
	N = N / 10;
    }
    a[0] = N + '0';
}

// Convert 3-digit ASCII array to binary
unsigned int Asc2Bin(char *a)                                           // Convert the 3-byte ASCII array to binary
{
    return (int) (a[0] & 0x0F)*100 + (a[1] & 0x0F)*10 + (a[2] & 0x0F);
}

// Convert 4-digit ASCII array to binary
unsigned int Asc2BinE(char *a)                                          // Convert the 4-byte ASCII array a to binary
{
    return (int) (a[0] & 0x0F) * 1000 + (a[1] & 0x0F) * 100 +
                 (a[2] & 0x0F) * 10 + (a[3] & 0x0F);
}

// packed BCD to ASCII
void PBCD2Asc(unsigned char SrcReg, char *DstArr)
{
    *DstArr++ = (SrcReg >> 4) | '0';				// convert upper nibble to ASCII
    *DstArr-- = (SrcReg & 0x0F) | '0';				// convert lower nibble to ASCII
}
