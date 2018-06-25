#include <p18cxxx.h>
#include <delays.h>
#include "LCD4xlib.h"
#include "LCDdefs.h"


unsigned long a;
float b;
char temp;
void SetupUltrasonic(void);
char Digits[3];


void main (void)
{
	OSCCON=0x50;
	OSCTUNEbits.INTSRC = 0;
	OSCTUNEbits.PLLEN = 0;
	
		SetupUltrasonic();
	InitLCD();
	DispRomStr(Ln1Ch0, (ROM *) "Developed by");
	DispRomStr(Ln2Ch0, (ROM *) "Chris & Ziad");
	Delay10KTCYx(1000);
	DispRomStr(Ln1Ch0,(ROM *) "Distance =    cm");
	DispRomStr(Ln2Ch0,(ROM *) "                 ");
	
	
	while(1)
{
	

	 // PORTBbits.RB1=1;			//Trigger High
	//	Delay10TCYx(1);				//Delay 10 us
	//	PORTBbits.RB1=0;			//Trigger Low
	
	while(!PORTBbits.RB0);		//Waiting for echo
		TMR0H =0;					//Sets the initial value of time
		TMR0L =0;					//Sets the initial value of time
		T0CONbits.TMR0ON =1;		//Timer starts
		while(PORTBbits.RB0);		//Waiting for echo to go Low
		temp = TMR0L;				//Reads timer value
		a = TMR0H;	
		a = (a<<8)|temp;
		T0CONbits.TMR0ON =0;		//Timer stops
		b= 340 * (float) a/1000000;	//Converts time to distance
if(b<0.1)
		{
		PORTA = 0b01111111;
		PORTBbits.RB6 =1;	
		PORTBbits.RB7 =1;
		PORTBbits.RB5 =1;
		}
		if(b>=0.1 && b<0.2)
		{
		
		PORTA = 0b01111111;
		PORTBbits.RB6 =1;	
		PORTBbits.RB7 =0;
		PORTBbits.RB5 =1;
		
		}
		if(b>=0.2 && b<0.3)
		{
		PORTA = 0b01111111;
		PORTBbits.RB6 =0;	
		PORTBbits.RB7 =0;
		PORTBbits.RB5 =1;
		}
		if(b>=0.3 && b<0.4)
	    {
		PORTA = 0b01111111;
		PORTBbits.RB6 =0;	
		PORTBbits.RB7 =0;
		PORTBbits.RB5 =0;
		}
		if(b>=0.4 && b<0.5)
		{
		PORTA = 0b00111111;
		PORTBbits.RB6 =0;	
		PORTBbits.RB7 =0;
		PORTBbits.RB5 =0;
		}
		if(b>=0.5 && b<0.6)
		{
		PORTA = 0b00011111;
		PORTBbits.RB6 =0;	
		PORTBbits.RB7 =0;
		PORTBbits.RB5 =0;
		}
		if(b>=0.6 && b<0.7)
		{
		PORTA = 0b00001111;
		PORTBbits.RB6 =0;	
		PORTBbits.RB7 =0;
		PORTBbits.RB5 =0;
		}
		if(b>=0.7 && b<0.8)
		{
		PORTA = 0b00000111;
		PORTBbits.RB6 =0;	
		PORTBbits.RB7 =0;
		PORTBbits.RB5 =0;
		}
		if(b>=0.8 && b<0.9)
		{
		PORTA = 0b00000011;
		PORTBbits.RB6 =0;	
		PORTBbits.RB7 =0;
		PORTBbits.RB5 =0;
		}
		if(b>=1)
		{
		PORTA = 0b00000001;
		PORTBbits.RB6 =0;	
		PORTBbits.RB7 =0;
		PORTBbits.RB5 =0;
		}

		Bin2AscE(b*100,Digits);
		DispVarStr(&Digits[2],Ln1Ch10,3);

		

}


}

void SetupUltrasonic(void)
{
	TRISB = 0x01;
	ANSELB = 0x00;
	T0CON = 0x00;
	TRISC = 0x00;
	ANSELC = 0x00;
	TRISA = 0x00;
	ANSELA=0x00;	
}

