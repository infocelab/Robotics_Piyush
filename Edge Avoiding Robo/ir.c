//Header files
#include<reg51.h>

//sbit pin declarations
sbit ir=P0^0;
sbit rf=P2^0;
sbit rb=P2^1;
sbit lf=P2^2;
sbit lb=P2^3; 

//Function Prototypes
void stop();
void forward();
void backward();
void left();
void right();
void delay(int);

//main function
void main()
{
	P0=0xFF;	// declared input port
	stop();
	while(1)
	{
		if(ir == 0)
		{			
			stop();
			delay(200);
			backward();
			delay(1000);
			stop();
			delay(100);
			left();
			delay(1000);
		}
		forward();
	}
}
//end of main function

/**************************** Function Definitions ************************************/

//to stop all wheels
void stop()

{
	//Lcd8_Display(0x80,"...DEAD  END!...",16);
	lf=0;
	rf=0;
	lb=0;
	rb=0;
	//delay_motor(50);
}

// to move forward:
void forward()
{
	//Lcd8_Display(0x80,".Moving Forward.",16);
	lf=1;
	rf=1;
	lb=0;
	rb=0;
}

// to move backwards:
void backward()
{
	//Lcd8_Display(0x80,"Moving  Backward",16);
	lb=1;
	rb=1;
	lf=0;
	rf=0;
}

// to move left
void left()
{
	//Lcd8_Display(0x80,"..Moving  Left..",16);
	lf=0;
	rf=1;
	lb=0;
	rb=0;
	//delay(50);
}

// to move left
void right()
{
	//Lcd8_Display(0x80,"..Moving Right..",16);
	lf=1;
	rf=0;
	lb=0;
	rb=1;
	delay(50);
}

void delay(int x)
{
	int i,j;
	for(i=0;i<x;i++)
		for(j=0;j<250;j++);
}