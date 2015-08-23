#include<reg52.h> //including sfr registers for ports of the controller
#include<lcd.h>

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
//End LCD Module Connections

//Keypad Connections
sbit R1 = P1^0;
sbit R2 = P1^1;
sbit R3 = P1^2;
sbit R4 = P1^3;
sbit C1 = P1^4;
sbit C2 = P1^5;
sbit C3 = P1^6;
sbit C4 = P1^7;
//End Keypad Connections

void delay(int x)
{
  int i,j;
  for(i=0;i<x;i++)
  {
    for(j=0;j<100;j++)
    {
    }
  }
}

char read_keypad()
{
  C1=1;
  C2=1;
  C3=1;
  C4=1;
  R1=0;
  R2=1;
  R3=1;
  R4=1;
  if(C1==0){delay(100);while(C1==0);return '7';}
  if(C2==0){delay(100);while(C2==0);return '8';}
  if(C3==0){delay(100);while(C3==0);return '9';}
  if(C4==0){delay(100);while(C4==0);return '/';}
  R1=1;
  R2=0;
  R3=1;
  R4=1;
  if(C1==0){delay(100);while(C1==0);return '4';}
  if(C2==0){delay(100);while(C2==0);return '5';}
  if(C3==0){delay(100);while(C3==0);return '6';}
  if(C4==0){delay(100);while(C4==0);return 'X';}
  R1=1;
  R2=1;
  R3=0;
  R4=1;
  if(C1==0){delay(100);while(C1==0);return '1';}
  if(C2==0){delay(100);while(C2==0);return '2';}
  if(C3==0){delay(100);while(C3==0);return '3';}
  if(C4==0){delay(100);while(C4==0);return '-';}
  R1=1;
  R2=1;
  R3=1;
  R4=0;
  if(C1==0){delay(100);while(C1==0);return 'C';}
  if(C2==0){delay(100);while(C2==0);return '0';}
  if(C3==0){delay(100);while(C3==0);return '=';}
  if(C4==0){delay(100);while(C4==0);return '+';}
  return 0;
}

void main()
{
	char c;
  int i=0,flag=0;
  char password[4]={"1234"};
	char input[4];
  Lcd8_Init();
  while(1)
  {
    Lcd8_Set_Cursor(1,1);
    Lcd8_Write_String("Enter Password:");
    Lcd8_Set_Cursor(2,1);
		
		while(i<4 && !(input[i]=read_keypad()))
		{
			//Lcd8_Set_Cursor(2,i+1);
			//Lcd8_Write_String("*");
			i++;
		}

		for(i=0;i<4;i++)
		{
			if(password[i]!=input[i])
			{
				flag=1;
				break;
			}
		}
		delay(1000);
		Lcd8_Clear();
		Lcd8_Set_Cursor(1,1);
		if(flag==1)
		{			
			Lcd8_Write_String("Wrong Password!");
		}
		else
		{			
			Lcd8_Write_String("Correct Password");
		}	
		delay(2000);
   /* Lcd8_Write_String("Times:");
    while(!(c = read_keypad()));
    p=c;
    while(p==c)
    {
      i++;
      Lcd8_Set_Cursor(1,14);
      Lcd8_Write_Char(c);
      Lcd8_Set_Cursor(2,7);
      Lcd8_Write_Char(i+48);
      delay(100);
      while(!(c = read_keypad()));
    }
    i=0; */
		//while(!read_keypad());
    Lcd8_Clear();
   }
}