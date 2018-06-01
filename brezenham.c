#include<stdio.h>
#include<GLUT/glut.h>

int x1, y1, x2, y2;
void draw_pixel(int x, int y)
{
	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void draw_line2(int x1, int y1, int x2, int y2)
{
	int dx, dy, i, d_p;
	int incx, incy, inc0, inc1;
	int x, y;
	
	dx = x2 - x1;
	dy = y2 - y1;
	if(dx < 0) 
		dx = -dx;
	if(dy < 0) 
		dy = -dy;

	if(x2 < x1)
		incx = -1;
	else
		incx = 1;
	if(y2 < y1)
		incy = -1;
	else
		incy = 1;

	x = x1;
	y = y1;
	
	if(dx > dy)			//gentle slope
	{
		draw_pixel(x, y);
		d_p = 2 * dy - dx;
		inc0 = 2 * dy - 2 * dx;
		inc1 = 2 * dy;
		while(x != x2)
		{
			if(d_p>=0)
			{
				y += incy;
				d_p += inc0;
			}
			else
				d_p += inc1;
			x += incx;
			draw_pixel(x, y);
		}	
	}
	else				//steep slope
	{
		draw_pixel(x, y);
		d_p = 2 * dx - dy;
		inc0 = 2 * dx - 2 * dy;
		inc1 = 2 * dx;
		while(y != y2)
		{
			if(d_p>=0)
			{
				x += incx;
				d_p += inc0;
			}
			else
				d_p += inc1;
			y += incy;
			draw_pixel(x, y);
		}
	}
}
void myinit()
{
	glClearColor(1,1,1,1);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	draw_line2(x1, y1, x2, y2);
	glFlush();
}

void main(int argc, char ** argv)
{
	printf("Enter x1,y1\n");
	scanf("%d %d",&x1, &y1);
	printf("Enter x2,y2\n");
	scanf("%d %d",&x2, &y2);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Bressenham");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
}
