//Header files
#include<reg51.h>

//sbit pin declarations
sbit ir_left=P0^0;
sbit ir_right=P0^1;
sbit rf=P2^0;
sbit rb=P2^1;
sbit lf=P2^2;
sbit lb=P2^3; 

//Global variables declarations
int var_left=0,var_right=0,var_back=0;

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
	P2=0x00;
	stop();
	while(1)
	{
		if(ir_right == 0 && ir_left == 1)	// for right turn
		{			
			right();
			var_right++;
		}
		else if(ir_left == 0 && ir_right == 1)	// for left turn
		{
			left();
			var_left++;
		}
		else if(ir_left == 0 && ir_right == 0) 
		{
			forward();
		}	
		else if(ir_left == 1 && ir_right == 1)
		{
			backward();
			var_back++;
			if(var_back > 5)
			{
				var_back=0;
				if(var_left > var_right)
				{
					left();
					delay(200);
				}
				else
				{
					right();
					delay(200);
				}
			}
		}
		else
		{
			stop();
		}
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
	delay(200);
}

// to move left
void left()
{
	//Lcd8_Display(0x80,"..Moving  Left..",16);
	lf=0;
	rf=1;
	lb=0;
	rb=0;
	//delay(100);
}

// to move left
void right()
{
	//Lcd8_Display(0x80,"..Moving Right..",16);
	lf=1;
	rf=0;
	lb=0;
	rb=0;
//	delay(50);
}

void delay(int x)
{
	int i,j;
	for(i=0;i<x;i++)
		for(j=0;j<250;j++);
}