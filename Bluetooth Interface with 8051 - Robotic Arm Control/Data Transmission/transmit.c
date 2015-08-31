#include<reg52.h>							 //including sfr registers for ports of the controller
#include<lcd.h>
#include <stdio.h>  

//LCD Module Connections
sbit RS = P0^0;                                                                   
sbit EN = P0^1;                            
sbit D0 = P2^0;
sbit D1 = P2^1;
sbit D2 = P2^2;
sbit D3 = P2^3;
sbit D4 = P2^4;
sbit D5 = P2^5;
sbit D6 = P2^6;
sbit D7 = P2^7;                           
sbit p=P0^2;	//pick 
sbit d=P0^3;	//drop
sbit r=P3^2;	//left
sbit l=P3^3;	//right
sbit up=P3^6;	//up
sbit down=P3^7;	//down

//Function Prototypes
void pick();
void drop();
void move_up();
void move_down();
void stop();
void left();
void right();
void delay(int);
void set_intr();

//Global variables
unsigned char c='x';
char count=0;

//Begin main function
void main()
{
	int i=0;
	char str[20];
  char a;
	//P0=0x00;
	//P3=0x00;
	
	/*------------------------------------------------
Setup the serial port for 9600 baud at 11.0592MHz.
------------------------------------------------*/
	
	TMOD=0x20;                                //Choosing Timer mode    
	TH1=0xFD;                                   //Selecting Baud Rate to 9600   
	SCON=0x50;                               //Serial mode selection    
	TR1=1;    
	IE=0x90; 
	
	Lcd8_init();
	Lcd8_Set_Cursor(1,1);
	Lcd8_Write_String("Bluetooth Controlled");
	Lcd8_Set_Cursor(2,1);
	Lcd8_Write_String("Robotic Arm");
	
  while(1)
  {   
		set_intr();	
	}
	IE=0x90;
}

void set_intr(void)	//interrupt 4        //Subroutine for Interrupt  
{
	IE=0x00;
	TI=0;
	SBUF=c;
	delay(100);
	TI==1;
	count++;
	//delay(1000);
	Lcd8_Clear();
  Lcd8_Set_Cursor(1,4);
	Lcd8_Write_Char(c);
	Lcd8_Set_Cursor(2,4);
	Lcd8_Write_Char(count);
	//IE=0x90;
}

void delay(int x)
{	
	int i,j;
  for(i=0;i<x;i++)
    for(j=0;j<100;j++);
}