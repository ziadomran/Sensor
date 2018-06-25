
#include <p18cxxx.h>
#include <delays.h>
#include "LCD4xlib.h"
#include "LCDdefs.h"





unsigned long a;
float b;
char temp;
void SetupUltrasonic(void);
char Digits[5];

void main(void)
{
	

	SetupUltrasonic();
	InitLCD();
	DispRomStr(Ln1Ch0, (ROM *) "Developed by");
	DispRomStr(Ln2Ch0, (ROM *) "Chris & Ziad");
	Delay10KTCYx(1000);
	DispRomStr(Ln1Ch0,(ROM *) "Distance =    cm");
	DispRomStr(Ln2Ch0,(ROM *) "                 ");
	
	
	while(1)
{

	
//
//	  PORTBbits.RB1=1;			//Trigger High
//		Delay10TCYx(1);				//Delay 10 us
//		PORTBbits.RB1=0;			//Trigger Low
	
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
		if(b<0.4)
		{
		PORTA = 0b01111111;
		PORTBbits.RB6 =1;	
		PORTBbits.RB7 =1;
		PORTBbits.RB5 =1;
		}
		if(b>=0.4 && b<0.8)
		{
		
		PORTA = 0b01111111;
		PORTBbits.RB6 =1;	
		PORTBbits.RB7 =0;
		PORTBbits.RB5 =1;
		
		}
		if(b>=0.8 && b<1.2)
		{
		PORTA = 0b01111111;
		PORTBbits.RB6 =0;	
		PORTBbits.RB7 =0;
		PORTBbits.RB5 =1;
		}
		if(b>=1.2 && b<1.6)
	    {
		PORTA = 0b01111110;
		PORTBbits.RB6 =0;	
		PORTBbits.RB7 =0;
		PORTBbits.RB5 =1;
		}
		if(b>=1.6 && b<2)
		{
		PORTA = 0b01111100;
		PORTBbits.RB6 =0;	
		PORTBbits.RB7 =0;
		PORTBbits.RB5 =1;
		}
		if(b>=2 && b<2.4)
		{
		PORTA = 0b01111000;
		PORTBbits.RB6 =0;	
		PORTBbits.RB7 =0;
		PORTBbits.RB5 =1;
		}
		if(b>=2.4 && b<2.8)
		{
		PORTA = 0b01110000;
		PORTBbits.RB6 =0;	
		PORTBbits.RB7 =0;
		PORTBbits.RB5 =1;
		}
		if(b>=2.8 && b<3.2)
		{
		PORTA = 0b01100000;
		PORTBbits.RB6 =0;	
		PORTBbits.RB7 =0;
		PORTBbits.RB5 =1;
		}
		if(b>=3.2 && b<3.6)
		{
		PORTA = 0b01000000;
		PORTBbits.RB6 =0;	
		PORTBbits.RB7 =0;
		PORTBbits.RB5 =1;
		}
		if(b>=3.6)
		{
		PORTA = 0b00000000;
		PORTBbits.RB6 =0;	
		PORTBbits.RB7 =0;
		PORTBbits.RB5 =1;
		}

		

		
		

	Bin2AscE(b*100,Digits);
		DispVarStr(&Digits[1],Ln1Ch10,3);
		
		

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