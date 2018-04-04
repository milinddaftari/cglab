#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>
int fillFlag=0;
float x1,x2,x3,x4,y1,y2,y3,y4,x5,y5,x6,y6;
void edgedetect(float x1,float y1,float x2,float y2,int *le,int *re)
{
	float mx,x,temp;
	int i;
	if((y2-y1)<0)
	{
		temp=y1;y1=y2;y2=temp;
		temp=x1;x1=x2;x2=temp;
	}
	if((y2-y1)!=0)
		mx=(x2-x1)/(y2-y1);
	else
	mx=x2-x1;
    x=x1;
	for(i=y1;i<=y2;i++)
	{
		if(x<(float)le[i])
			le[i]=(int)x;
		if(x>(float)re[i])
			re[i]=(int)x;
		x+=mx;
	}
}
void draw_pixels(int x,int y)
{
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}
void scanfill(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4,float x5,float y5,float x6,float y6)
{
	int le[1500],re[1500];
	int i,y;
	for(i=0;i<1500;i++)
	{
		le[i]=1500;
		re[i]=0;
	}
	edgedetect(x1,y1,x2,y2,le,re);
	edgedetect(x2,y2,x3,y3,le,re);
	edgedetect(x3,y3,x4,y4,le,re);
	edgedetect(x4,y4,x5,y5,le,re);
	edgedetect(x5,y5,x6,y6,le,re);
	edgedetect(x6,y6,x1,y1,le,re);
	for(y=0;y<1500;y++)
	{
		if(le[y]<re[y])
			for(i=(int)le[y];i<(int)re[y];i++)
				draw_pixels(i,y);
	}
}
void display()
{
	x1=20.0;y1=30.0;x2=70.0;y2=10.0;x3=130.0;y3=50.0;x4=130.0;y4=110.0;x5=70;y5=70;x6=20;y6=90;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glVertex2f(x3,y3);
	glVertex2f(x4,y4);
	glVertex2f(x5,y5);
	glVertex2f(x6,y6);
	glEnd();
	if(fillFlag==1)
	scanfill(x1,y1,x2,y2,x3,y3,x4,y4,x5,x5,x6,y6);
	glFlush();
}
void fillMenu(int option)
{
	if(option==1)
		fillFlag=1;
	if(option==2)
		fillFlag=2;
	display();
}
void myinit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,499.0,0.0,499.0);
}
void main(int argc,char**argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("filling a polygon using scanline ");
	glutDisplayFunc(display);
	glutCreateMenu(fillMenu);
	glutAddMenuEntry("Fill Polygon",1);
	glutAddMenuEntry("Empty Polygon",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	myinit();
	glutMainLoop();
}