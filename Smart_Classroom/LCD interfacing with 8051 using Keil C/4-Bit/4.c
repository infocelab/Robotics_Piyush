#include<reg52.h>							
#include<lcd.h>

//LCD Module Connections
sbit RS = P0^0;                                                                   
sbit EN = P0^1;                            
sbit D0 = P2^0;
sbit D1 = P2^1;
sbit D2 = P2^2;
sbit D3 = P2^3;
//End LCD Module Connections
void Delay(int a)
{
    int j;
    int i;
    for(i=0;i<a;i++)
    {
        for(j=0;j<100;j++)
        {
        }
    }
}
void main()
{
	int i;
	Lcd4_init();                                  
  while(1)
  {  
		Lcd4_Clear();
    Lcd4_Set_Cursor(2,2);
	  Lcd4_Write_String("Celab LCD Example");
		for(i=0;i<15;i++)
		{
		  Delay(400);
			Lcd4_Shift_Left();
		}
		
		for(i=0;i<15;i++)
		{
			Delay(400);
			Lcd4_Shift_Right();
		}/*
		Lcd_Clear();
		Lcd4_Set_Cursor(0,2);
		Lcd4_Write_Char('H');
		Lcd4_Write_Char('I');
		Delay(2000);*/
  }
}




