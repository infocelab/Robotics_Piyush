/************************* HEADER FILES ************************/
#include<reg52.h>
#include <intrins.h>

/*********************** SBIT DECLARATIONS *********************/
sbit Lcd_rs = P0^0;
sbit Lcd_rw = P0^2;
sbit Lcd_en = P0^1;
sbit rf=P3^0;
sbit rb=P3^1;
sbit lf=P3^2;
sbit lb=P3^3;
sbit echo= P3^4; 
sbit trig= P3^5;
sbit motor_pin = P3^7;

/************************* #DEFINITIONS ************************/
#define First_Line 0x80
#define Second_Line 0xc0
#define Curser_On  0x0f
#define Curser_Off 0x0c
#define Clear_Display 0x01
#define Data_Port P2
#define DELAY 2000
#define D 10

/*********************** FUNCTION PROTOTYPES *********************/ 
void distance_measure();
void Lcd8_Init();
void Lcd8_Command(unsigned char);
void Lcd8_Write(unsigned char,unsigned char);
void Lcd8_Display(unsigned char,const unsigned char*,unsigned int);
void Lcd8_Decimal2(unsigned char,unsigned char);
void Lcd8_Decimal3(unsigned char,unsigned char);
void Lcd8_Decimal4(unsigned char,unsigned int);
void delay_ultrasonic(unsigned int);
void del();  
void delay_motor(unsigned int);
void Servo_Delay(unsigned int);
void scan_front();
void scan_left();
void scan_right();
void stop();
void forward();
void backward();
void left();
void right();
void wait(int);
void check_servo();

/************************* GLOBAL VARIABLES ************************/
unsigned char i,rept,sec,j,a=0,c=0,kc,cu=0xc0,l,e[20],num[20],n,v[20];
unsigned int count=0,count1=0,obj_distance,inch1,inch2,result;

/************************* MAIN FUNCTION ************************/
void main()
{
	int left_distance=0,right_distance=0;
	int i;
	motor_pin = 0;
	P3=0x00;
	EA=1;
	ET0=1;
	TMOD=0x01;
	TH0=TL0=0x00;
	TR0=1;
	Lcd8_Init();
	delay_ultrasonic(65000); 
	Lcd8_Display(0xC0,"Distance:       ",16);
	check_servo();
		
	while(1)
	{
		distance_measure();
		if(obj_distance > D)
		{
			forward();
		}
		else
		{
			stop();			
			for(i=0;i<100;i++)		// scan left area
			{
				scan_left();
				wait(1);
			}			
			distance_measure();
			wait(200);
			left_distance=obj_distance;
			for(i=0;i<100;i++)			// scan right area
			{
				scan_right();
				wait(1);
			}
			distance_measure();
			wait(200);
			right_distance=obj_distance;
			for(i=0;i<100;i++)
			{
				scan_front();
				wait(1);
			}
			//wait(100);
			if(left_distance > D && right_distance < D)
			{
				left();
				while(obj_distance < D)
				{
					left();
				}
			}
			else if(left_distance < D && right_distance > D)
			{
				right();
				while(obj_distance < D)
				{
					right();
				}
			}
			else if(left_distance > right_distance)
			{	
				left();
				while(obj_distance < D)
				{
					left();
				}
			}
			else if(left_distance < right_distance)
			{
				right();
				while(obj_distance < D)
				{
					right();
				}
			}			
		}
	}
}
/*************************** END OF MAIN ***************************/

/*********************** FUNCTION DEFINITIONS **********************/
// to scan the front area
void scan_front()
{
    motor_pin = 1;
    Servo_Delay(110);
    motor_pin = 0;
}

// to scan the left area
void scan_left()
{
    motor_pin = 1;
    Servo_Delay(180);
    motor_pin = 0;
}

// to scan the right area
void scan_right()
{
    motor_pin = 1;
    Servo_Delay(50);
    motor_pin = 0;
}

// to stop all wheels:
void stop()
{
	//Lcd8_Display(0x80,"...DEAD  END!...",16);
	lf=0;
	rf=0;
	lb=0;
	rb=0;
	wait(500);
}

// to move forward:
void forward()
{
	Lcd8_Display(0x80,".Moving Forward.",16);
	lf=1;
	rf=1;
	lb=0;
	rb=0;
}

// to move backwards:
void backward()
{
	Lcd8_Display(0x80,"Moving  Backward",16);
	lb=1;
	rb=1;
	lf=0;
	rf=0;
}

// to move left
void left()
{
	Lcd8_Display(0x80,"..Moving  Left..",16);
	Lcd8_Decimal3(0XCb,obj_distance);
	lf=0;
	rf=1;
	lb=0;
	rb=0;
	distance_measure();
	//delay_motor(10);
}

// to move left
void right()
{
	Lcd8_Display(0x80,"..Moving Right..",16);
	Lcd8_Decimal3(0XCb,obj_distance);
	lf=1;
	rf=0;
	lb=0;
	rb=0;
	distance_measure();
	//delay_motor(10);
}

// to calculate the distance of object
void distance_measure()
{
	count=count1=0;
	TH0=0x00;TL0=0x00; 
	TR0=0;
	for(i=0;i<10;i++)         
	{
		trig=0;           
		delay_ultrasonic(1000);
		trig=1;           
		delay_ultrasonic(10);
		trig=0;   
		while(echo==0);
		TR0=1; 
		while(echo==1);
		TR0=0;
		count=TH0<<8;      
		count=count|TL0;    
		TH0=TL0=0x00; 
		count1=count1+count;
		delay_ultrasonic(500);        
	}
	count=count1/10;
	inch1=count%10000/1000;
	inch2=count%1000/100;
	result=(inch1*10)+inch2;
	 
	obj_distance=result-2;  
	Lcd8_Decimal3(0XCb,obj_distance); 
}

void Lcd8_Init()
{
	Lcd8_Command(0x38); //to select function set
	Lcd8_Command(0x06); //entry mode set
	Lcd8_Command(0x0c); //display on
	Lcd8_Command(0x01); //clear display
}
 
void Lcd8_Command(unsigned char com)
{
	Data_Port=com;
	Lcd_en=1;
	Lcd_rs=Lcd_rw=0;
	delay_ultrasonic(125);
	Lcd_en=0;
	delay_ultrasonic(125);
}
 
void Lcd8_Write(unsigned char com,unsigned char lr)
{
	Lcd8_Command(com);
	 
	Data_Port=lr; // Data 
	Lcd_en=Lcd_rs=1;
	Lcd_rw=0;
	delay_ultrasonic(125);
	Lcd_en=0;
	delay_ultrasonic(125);
}
 
void Lcd8_Display(unsigned char com,const unsigned char *word,unsigned int n)
{
	unsigned char Lcd_i;
	 
	for(Lcd_i=0;Lcd_i<n;Lcd_i++)
	{ 
	Lcd8_Write(com+Lcd_i,word[Lcd_i]);
		}
}
 
void Lcd8_Decimal2(unsigned char com,unsigned char val)
{
	unsigned int Lcd_hr,Lcd_t,Lcd_o;
	 
	Lcd_hr=val%100;
	Lcd_t=Lcd_hr/10;
	Lcd_o=Lcd_hr%10;
	 
	Lcd8_Write(com,Lcd_t+0x30);
	Lcd8_Write(com+1,Lcd_o+0x30);
}
 
 
void Lcd8_Decimal3(unsigned char com,unsigned char val)
{
	unsigned int Lcd_h,Lcd_hr,Lcd_t,Lcd_o;
	 
	Lcd_h=val/100;
	Lcd_hr=val%100;
	Lcd_t=Lcd_hr/10;
	Lcd_o=Lcd_hr%10;
	 
	Lcd8_Write(com,Lcd_h+0x30);
	Lcd8_Write(com+1,Lcd_t+0x30);
	Lcd8_Write(com+2,Lcd_o+0x30);
}

void check_servo()
{
	for(i=0;i<100;i++)
	{
		scan_left();
		wait(1);
	}
	wait(500);
	for(i=0;i<100;i++)
	{
		scan_right();
		wait(1);
	}
	wait(500);
	for(i=0;i<100;i++)
	{
		scan_front();
		wait(1);
	}
	wait(500);
}

void delay_ultrasonic(unsigned int del)
{
	while(del--);
}

void delay_motor(unsigned int ms)
{
  unsigned long int us = ms*1000;
  while(us--)
  {
    _nop_();
  }
}

void Servo_Delay(unsigned int us)
{
  while(us--)
  {
    _nop_();
  }
}

void wait(int x)
{
	int i,j;
	for(i=0;i<x;i++)
		for(j=0;j<275;j++);
}