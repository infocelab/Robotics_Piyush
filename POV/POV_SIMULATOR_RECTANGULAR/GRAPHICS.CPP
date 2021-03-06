#include<stdio.h>
#include<process.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>

#define ROWS 16
#define HEX_ROWS ROWS/4
#define COLS 360
#define CELL_SIZE 10

union REGS in,out;
int INITX=100;
int INITY=200;
int data_arr[ROWS][COLS];
char hexa_arr[HEX_ROWS][COLS];
FILE *f;

int callmouse()                   // To initialise the MOUSE
{
 in.x.ax=1;
 int86(51,&in,&out);
 return 1;
}

void board()
{
 int i,j;
 int selected_row,selected_col,top_x,top_y,bottom_x,bottom_y;

 for(i=0;i<=ROWS;i++)
 {
  line(INITX,INITY+(i*CELL_SIZE),INITX+(COLS*CELL_SIZE),INITY+(i*CELL_SIZE));
 }
 for(i=0;i<=COLS;i++)
 {
 /* if(i%2==0)
   outtextxy(INITX+(i*CELL_SIZE)+2,INITY+1,".");
  else
   outtextxy(INITX+(i*CELL_SIZE)+2,INITY+1,"-"); */
  line(INITX+(i*CELL_SIZE),INITY,INITX+(i*CELL_SIZE),INITY+(ROWS*CELL_SIZE));
 }
 for(i=0;i<ROWS;i++)
 {
  for(j=0;j<COLS;j++)
  {
   top_x=INITX+(j*CELL_SIZE);
   top_y=INITY+(i*CELL_SIZE);
   bottom_x=INITX+((j+1)*CELL_SIZE);
   bottom_y=INITY+((i+1)*CELL_SIZE);
   if(data_arr[i][j]==1)
   {
	setfillstyle(SOLID_FILL,YELLOW);
	//data_arr[selected_row][selected_col]=1;
   }
   else
   {
	setfillstyle(SOLID_FILL,BLACK);
   }
	int offset=2;
	bar(top_x+offset,top_y+offset,bottom_x-offset,bottom_y-offset);
  }
 }
}

void pos(int &x,int &y,int &cl)
{
	  in.x.ax=3;
	  int86(51,&in,&out);
	  cl=out.x.bx;
	  x=out.x.cx;
	  y=out.x.dx;
}

void bintohexa()
{
 int temp_hexa[HEX_ROWS][COLS];
 int temp_arr[ROWS][COLS];
 int i,j;
 int k=ROWS/4,m;

  for(i=0;i<ROWS;i++)
  {
   for(j=0;j<COLS;j++)
   {
	if(data_arr[i][j]==1)
	{
	 temp_arr[i][j]=0;
	}
	else
	{
	 temp_arr[i][j]=1;
	}

   }
  }
  for(i=0;i<COLS;i++)
  {
  for(j=0;j<2;j++)
  {
   m=k*j;
   temp_hexa[j][i]=1*temp_arr[m][i]+2*temp_arr[m+1][i]+4*temp_arr[m+2][i]+8*temp_arr[m+3][i];
   if(temp_hexa[j][i]<=9)   temp_hexa[j][i]=temp_hexa[j][i]+48;
	else   		  temp_hexa[j][i]=temp_hexa[j][i]+55;
  }
   for(j=2;j<4;j++)
  {
   m=k*j;
   temp_hexa[j][i]=8*temp_arr[m][i]+4*temp_arr[m+1][i]+2*temp_arr[m+2][i]+1*temp_arr[m+3][i];
   if(temp_hexa[j][i]<=9)   temp_hexa[j][i]=temp_hexa[j][i]+48;
	else   		  temp_hexa[j][i]=temp_hexa[j][i]+55;
  }
 }
 for(i=0;i<COLS;i++)
 {
  hexa_arr[0][i]=temp_hexa[1][i];
 }
 for(i=0;i<COLS;i++)
 {
  hexa_arr[1][i]=temp_hexa[0][i];
 }
 for(i=0;i<COLS;i++)
 {
  hexa_arr[2][i]=temp_hexa[2][i];
 }
 for(i=0;i<COLS;i++)
 {
  hexa_arr[3][i]=temp_hexa[3][i];
 }
}

void make(int x, int y, int click)
{
 int selected_row,selected_col;
 int top_x,top_y,bottom_x,bottom_y;
 int i,j;
 if(click==1)
 {
  selected_row=((y-INITY)/CELL_SIZE);
  selected_col=((x-INITX)/CELL_SIZE);
 // printf("\n\tSelected row:%d\t col:%d\t",selected_row,selected_col);
  if(x<INITX||y<INITY)
   return;
  if(selected_row<0||selected_col<0)
   return;
  if(selected_row>=ROWS||selected_col>=COLS)
   return;
  top_x=INITX+(selected_col*CELL_SIZE);
  top_y=INITY+(selected_row*CELL_SIZE);
  bottom_x=INITX+((selected_col+1)*CELL_SIZE);
  bottom_y=INITY+((selected_row+1)*CELL_SIZE);
  if(data_arr[selected_row][selected_col]==0)
  {
	  data_arr[selected_row][selected_col]=1;
  }
  else if(data_arr[selected_row][selected_col]==1)
  {
		data_arr[selected_row][selected_col]=0;
  }

  board();
 }

 if(click==2)
 {
/*  printf("\n\n\n\n\n");
  for(i=0;i<ROWS;i++)
  {
   for(j=0;j<COLS;j++)
   {
	printf("%d",data_arr[i][j]);
   }
   printf("\n");
  } */
  bintohexa();
  //Writing Hexadecimal values to the FILE
  f=fopen("hex.txt","w");

  for(i=0;i<COLS;i++)
  {
   fprintf(f,"{0x");
   for(j=0;j<ROWS/4;j++)
   {
	fprintf(f,"%c",hexa_arr[j][i]);
	if(j==1)
	{
	 fprintf(f,",0x");
	}
   }
   if(i==COLS-1)
   fprintf(f,"}\n");
   else
	fprintf(f,"},\n");
  }
 }
}

void clear()
{
 int i,j;
 for(i=0;i<ROWS;i++)
	{
		for(j=0;j<COLS;j++)
		{
			data_arr[i][j]=0;
		}
	}
}

void main()
{
	int xpos,ypos,click;
	int driver=DETECT,mode;
	int i,j;
	int key;
	initgraph(&driver,&mode,"\\tc\\bgi");
	setfillstyle(SOLID_FILL,YELLOW);
	board();
	callmouse();
	clear();

	while(1)
	{

		pos(xpos,ypos,click);
		if(kbhit())
		{
			key=getch();
			if(key==13||key==27)       // ENTER & ESC
				exit(1);
			if(key==77)
			{
				INITX-=CELL_SIZE;
				clearviewport();
				board();
			}
			if(key==75)
			{
				INITX+=CELL_SIZE;
				clearviewport();
				board();
			}
			if(key==99)                 // C
			{
				clearviewport();
				clear();
				board();
			}
			if(key==112)                 // P
			{
				for(i=0;i<COLS;i++)
				{
					printf("{'0x");
					for(j=0;j<ROWS/4;j++)
					{
						printf("%c",hexa_arr[j][i]);
						if(j==1)
						{
							 printf("','0x");
						}
					}
			   if(i==COLS-1)
					printf("'}\n");
			   else
					printf("'},\n");
				 }
			}
		}
	gotoxy(1,1);
	printf("Mouse Position: %d,%d",xpos,ypos);
	printf("\n\t Click:%d",click);
	printf("\n\t%d\t",key);
	make(xpos,ypos,click);
	// board();
	//INITX-=CELL_SIZE;
	//cleardevice();
	}
}