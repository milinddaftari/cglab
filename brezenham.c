#include<stdio.h> 
#include<stdlib.h>
#include<GLUT/glut.h>

int x1,y1,x2,y2;

void drawpixel(int x,int y)
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
}

void bresenham(int x1,int y1,int x2,int y2)
{
	int dx=x2-x1;
	int dy=y2-y1;
	int m=dy/dx;

	if(m<1)
	{
		int dp=2*dy-dx;
		int x=x1;
		int y=y1;
		if(dx<0)
		{
			x=x2;
			y=y2;
			x2=x1;
		}
	drawpixel(x,y);
	while(x<x2)
	{
		if(dp>=0)
		{
			x++;
			y++;
			dp=dp+2*dy-2*dx*(y+1-y);
		}
		else
		{
			x++;
			y=y;
			dp=dp+2*dy-2*dx*(y-y);
		}
		drawpixel(x,y);
	}
	}
	else if(m>1)
	{
		int dp=2*dx-dy;
		int x=x1;
		int y=y1;
		if(dy<0)
		{
			x=x2;
			y=y2;
			y2=y1;
		}
		drawpixel(x,y);
		while(y<y2)
		{
			if(dp>=0)
			{
				x++;
				y++;
				dp=dp+2*dx-2*dy*(x+1-x);
			}
			else
			{
				y++;
				x=x;
				dp=dp+2*dx-2*dy*(x-x);
			}
			drawpixel(x,y);
		}
	}
	else if(m==1)
	{
		int x=x1;
		int y=y1;
		drawpixel(x,y);
		while(x<x2)
		{
			x=x+1;
			y=y+1;
			drawpixel(x,y);
		}
	}
}

void myinit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	bresenham(x1,y1,x2,y2);
	glFlush();
}

int main(int argc,char** argv)
{
	printf("Enter Scan Points (x1,y1) ");
	scanf("%d %d",&x1,&y1);
	printf("Enter Scan Points (x2,y2) ");
	scanf("%d %d",&x2,&y2);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(50,50);
	glutCreateWindow("Brezenham");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}

