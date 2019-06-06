#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
void showmouseptr();
void
set();
void restrict();
void detect();
void hidemouse();
int detectbutton();
union REGS i,o;
int xc,yc,flag;

int main()
{
  int gd=DETECT,gm,i,h,c,posx,posy;
  int score=0;
  char str[50],str1[50],str2[50],str3[50],str4[50];
  int start_t,end_t,life=10,time=40;
  int x[]={50,80,110,140,170,200,230,260,290,320,350,380,410,440};
  int y[]={50,80,110,140,170,200,230,260,290,320,350,380,410,440};
  int color[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14};
  char driver[]="C:\\TURBOC3\\BGI";
  initgraph(&gd,&gm,driver);


  set();
  restrict();
  for(c=0;1;c++){
  cleardevice();


  sprintf(str,"Score=%d",score);
  outtextxy(60,10,str);

sprintf(str2,"Life remaining:");
  outtextxy(170,10,str2);
  
  for(i=0;i<life;i++){
  if(life<4)
  setcolor(4);
  else
  setcolor(2);
  sprintf(str4,"I");
  outtextxy(300+7*i,10,str4);
  }
  setcolor(3);
  sprintf(str3,"Created by Sourav,Avadhoot,Shreyans,Mahek");
  outtextxy(60,30,str3);
  setcolor(15);
  rectangle(50,50,470,470);

  for(i=1;i<=14;i++)  //vertical
  {
  line(50+30*i,50,50+30*i,470);
  }
  for(i=1;i<=14;i++)   //horizontal
  {
   line(50,50+30*i,470,50+30*i);
  }
  showmouseptr();
  posx=x[rand()%14];
  posy=y[rand()%14];
  i=rand()%14;//
  setfillstyle(1,color[i]);
  rectangle(posx,posy,posx+30,posy+30);
  floodfill(posx+5,posy+5,WHITE);
  start_t=clock();
flag=0 ;
  do{
	end_t=clock();
	h=detectbutton();
	if(h==1)
		{
		detect();
		if(xc>posx && xc<(posx+30) && yc>(posy) && yc<(posy+30))
		{
		flag=1 ;
		score++;
		break;
		}

		}


   }while(end_t-start_t<=time);
   if(score%20==0)
   time=time-3;
   if(flag==0)
   life--;
   if(life==0)
   break;

  hidemouse();

}
  cleardevice();
  sprintf(str1,"Your final score is %d",score);
  outtextxy(200,200,str1);
  getch();
  closegraph();
    return 0;

}
void set()
{
	i.x.ax=4;
	i.x.cx=600;
	i.x.dx=600;
	int86(0X33,&i,&o);
}
void restrict ()
{
	i.x.ax = 7;
	i.x.cx = 50;
	i.x.dx = 600;
	int86 (0X33,&i,&o);
	i.x.ax = 8;
	i.x.cx = 50;
	i.x.dx = 600;
	int86 (0X33,&i,&o);
}
void detect ()
{

		i.x.ax = 3;
		int86 (0X33,&i,&o);
		if (o.x.bx == 1)
		{
			xc = o.x.cx;
			yc = o.x.dx;

		}

}
int detectbutton()
{
	i.x.ax=3;
	int86(0X33,&i,&o);
	return (o.x.bx&7);
}
void hidemouse()
{
	i.x.ax=2;
	int86(0x33,&i,&o);
}
void showmouseptr()
{
	i.x.ax=1;
	int86(0x33,&i,&o);
}

