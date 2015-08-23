#include<reg51.h>
//#include<reg52.h> //including sfr registers for ports of the controller
#include<lcd.h>
#include<stdlib.h>

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
//End LCD Connections

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

char card_id[12];			// stores the 12 digit ID
int lock=0;								// to lock the door after the teacher enters
char teacher[12]={"FE005F734290"};
char attendance[3];
char student[3][12]=	{
		{'F','E','0','0','5','F','4','9','C','2','2','A'},
		{'1','3','0','0','4','0','B','C','B','E','5','1'},
		{'1','3','0','0','4','A','0','4','A','B','F','6'}
	};
//unsigned char password[4];

/******************* Function to generate delay in microseconds********************/
  void delay(int x)				
   {
    int i,j;
    for(i=0;i<x;i++)
        for(j=0;j<100;j++);
	 }
/********************Function to recieve data serially from RS232******************/	 
   void recieve()     		 
   {
		 unsigned char k;			 
     for(k=0;k<12;k++)
     { 
       while(RI==0); 				
			 card_id[k] = SBUF;
			 RI=0;
		 }
	 }		
/************* Function to print the default message at idle state*****************/
		void default_msg()		
		{
			Lcd8_Clear();
	    Lcd8_Set_Cursor(1,1);
	    Lcd8_Write_String("Show Your RFID");
	    Lcd8_Set_Cursor(2,6);
      Lcd8_Write_String("Card");		
		}
/********************************Function to Close the Door******************************/
		void close_door()
		{
			Lcd8_Clear();
			Lcd8_Set_Cursor(2,1);
			Lcd8_Write_String("Closing Door..");
			delay(1000);
		}
/********************************Function to Open Door******************************/
		void open_door()
		{
			
			Lcd8_Set_Cursor(2,1);
			Lcd8_Write_String("Opening Door..");
			delay(2000);
			close_door();
		}

	/*	char Read_Keypad()
{
  C1=1;
  C2=1;
  C3=1;
  C4=1;
  R1=0;
  R2=1;
  R3=1;
  R4=1;
  if(C1==0){delay(100);while(C1==0);return '1';}
  if(C2==0){delay(100);while(C2==0);return '2';}
  if(C3==0){delay(100);while(C3==0);return '3';}
  if(C4==0){delay(100);while(C4==0);return 'A';}
  R1=1;
  R2=0;
  R3=1;
  R4=1;
  if(C1==0){delay(100);while(C1==0);return '4';}
  if(C2==0){delay(100);while(C2==0);return '5';}
  if(C3==0){delay(100);while(C3==0);return '6';}
  if(C4==0){delay(100);while(C4==0);return 'B';}
  R1=1;
  R2=1;
  R3=0;
  R4=1;
  if(C1==0){delay(100);while(C1==0);return '7';}
  if(C2==0){delay(100);while(C2==0);return '8';}
  if(C3==0){delay(100);while(C3==0);return '9';}
  if(C4==0){delay(100);while(C4==0);return 'C';}
  R1=1;
  R2=1;
  R3=1;
  R4=0;
  if(C1==0){delay(100);while(C1==0);return '*';}
  if(C2==0){delay(100);while(C2==0);return '0';}
  if(C3==0){delay(100);while(C3==0);return '#';}
  if(C4==0){delay(100);while(C4==0);return 'D';}
  return 0;
}
		*/
/***********************Function to input & check Password from Keypad*****************/
/*		int check_password(int std)
		{
			int i;
			char c;
			char temp[4];
			Lcd8_Clear();
			Lcd8_Set_Cursor(1,1);
			Lcd8_Write_String("Enter Password:");
			i=0;
			while(i!=4)
			{
				while(!(c = Read_Keypad()));
				temp[i]=c;
				i++;
			}
			for(i=0;i<4;i++)
			{
				if(temp[i]!=1)
					return 0;
			}	
			return 1;
		}
	*/	
		/****************** Function to check whose ID has been shown**********************/		
		void check()					
		{
			int i,j;
			int student_flag=0,teacher_flag=0;
			
			for(i=0;i<12;i++)
			{
				if(card_id[i] != teacher[i])
				{	
					student_flag=1;
					break;
				}	
				else
				teacher_flag=1;
			}
			
			if(student_flag==1 && lock==0)	// if ID is of students' & door is unlocked
			{
				for(i=0;i<3;i++)
				{
					for(j=0;j<12;j++)
					{
						if(card_id[j] != student[i][j])
							break;
						if(j==11)
						{
							Lcd8_Clear();
							Lcd8_Set_Cursor(1,4);
							Lcd8_Write_String("Student");
							Lcd8_Write_Char(i+1+48);
							attendance[i]=1;
							delay(1000);
							Lcd8_Set_Cursor(1,1);							
					/*		if(check_password(i)==1)
							{
								Lcd8_Write_String("Access Granted..");
								open_door();
							}
							else							
							{
								Lcd8_Set_Cursor(1,1);
								Lcd8_Write_String("Password NOT");
								Lcd8_Set_Cursor(2,1);
								Lcd8_Write_String("Matched!");
							}*/
						}
					}
				}
			}
			else if(student_flag==1 && lock==1)	// if ID is of students' but the door is Locked!
			{
				Lcd8_Clear();
				Lcd8_Set_Cursor(1,2);
				Lcd8_Write_String("The Door is");
				Lcd8_Set_Cursor(2,4);
				Lcd8_Write_String("LOCKED!");
			}
			else if(teacher_flag==1 && lock==1)	// if teacher wants to go outside the class
			{
				Lcd8_Clear();
				Lcd8_Set_Cursor(1,4);
				Lcd8_Write_String("TEACHER");
				open_door();			
				lock=0;		// Unlock the door
				for(i=0;i<3;i++)			
					attendance[i]=0;			// after teacher exits, put all attendances to 0
			}
			else if(teacher_flag==1 && lock==0)		// teacher enters the classroom. The
			{																			//	door is now locked!
				Lcd8_Clear();
				Lcd8_Set_Cursor(1,4);
				Lcd8_Write_String("TEACHER");	
				delay(500);
				open_door();
				Lcd8_Clear();
				Lcd8_Set_Cursor(1,1);
				Lcd8_Write_String("Locking Door..");
				delay(2000);
				lock=1;		// Lock the door. No student can now enter the classroom!
				for(i=0;i<3;i++)
				{
					if(attendance[i] == 0)
					{
						Lcd8_Clear();
						Lcd8_Set_Cursor(1,1);
						Lcd8_Write_String("Absent Students:");
						Lcd8_Set_Cursor(2,3);
						Lcd8_Write_String("Student");
						Lcd8_Write_Char(i+1+48);
						delay(1000);
					}
				}
			}
			else
			{
				Lcd8_Clear();
				Lcd8_Set_Cursor(1,1);
				Lcd8_Write_String("WOOPS..!!");
				delay(2000);
			}
		}
/**************************** Begin main function**********************************/			
    void main()								
    { 
			int len;
			char *welcome="WELCOME";
			TMOD=0x20; //Enable Timer 1
      TH1=0XFD;
      SCON=0x50;
      TR1=1; 
	    Lcd8_init();
		  Lcd8_Set_Cursor(1,1);
			//welcome = (char *) malloc(sizeof(char));
			//welcome="WELCOME";
			delay(200);
			Lcd8_Set_Cursor(1,3);
			Lcd8_Write_String(welcome);
	    delay(2000);
			default_msg();
	      		
    while(1)
    {
        recieve();
     		Lcd8_Clear();
				//check();
				delay(1000);
				default_msg();
	  }
			
			
}