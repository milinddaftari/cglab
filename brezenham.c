#include<stdio.h> 
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include<GLUT/glut.h>

int win_width = 512;
int win_height = 512; 
int xx0, yy0;
int xx1, yy1;
int numpoints=0;
int linetype = 0;

void line1 (int x0, int y0, int x1, int y1)
{
int deltax = x1 - x0;
int deltay = y1 - y0;
float error = 0.0;
float newerr = 0.0;
float deltaerr = (float)deltay / (float)deltax;
int y = y0;
int newy = y0;
glPointSize(1.0);
glColor3f(0.0, 0.0, 1.0);
glBegin(GL_POINTS);
	for (int x = x0; x < x1; x++)
	{
		glVertex2f(x, y);
		error = error + deltaerr;
		if (fabs(error) >= 0.5)
		{
			y = y + 1;
			error = error - 1.0;
		}
	}
glEnd();
}

void swap (int x, int y)
{

	int temp = x;
	x = y;
	y = temp;
}
void line2 (int x0, int y0, int x1, int y1)
{
bool steep = abs(y1 - y0) > abs(x1 - x0);
if(steep)
{
	swap(x0, y0);
	swap(x1, y1);
}
if (x0 > x1)
{
	swap(x0, x1);
	swap(y0, y1);
}
int deltax = x1 - x0;
int deltay = abs(y1 - y0);
float error = 0.0;
float deltaerr = (float)deltay / (float)deltax;
int ystep;
int y = y0;
if (y0 < y1)
	ystep = 1;
else 
	ystep = -1;
glPointSize(1.0);
glColor3f(1.0, 0.0, 0.0);
glBegin(GL_POINTS);
for (int x=x0; x < x1; x++)
{
	if (steep)
		glVertex2f(y, x);
	else
		glVertex2f(x, y);
	error = error + deltaerr;
	if (fabs(error) >= 0.5)
	{
		y = y + ystep;
		error = error - 1.0;
	}
}
glEnd();
}

void display(void )
{
glClear(GL_COLOR_BUFFER_BIT );
if ((numpoints % 2 )== 1)
{
glPointSize(4.0);
glBegin(GL_POINTS);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(xx0, yy0);
glEnd();
}
else if ((numpoints % 2) == 0)
{
glPointSize(4.0);
glBegin(GL_POINTS);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(xx0, yy0);
	glVertex2f(xx1, yy1);
glEnd();
if (linetype != 3)
{
glPointSize(1.0); 
glBegin(GL_LINES); 
	glColor3f(1.0, 1.0, 1.0); 
	glVertex2f(xx0, yy0); 
	glVertex2f(xx1, yy1); 
glEnd();
}
if (linetype == 1)
	line1(xx0, yy0, xx1, yy1);
else if (linetype >= 2)
	line2(xx0, yy0, xx1, yy1);
}
glutSwapBuffers();
}


void reshape( int w, int h )
{
if ( h == 0 )
	h = 1;
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho( 0.0, (GLdouble)w, 0.0, (GLdouble)h, -1.0, 1.0);
glViewport( 0, 0, w, h );
win_width = w;
win_height = h;
glutPostRedisplay();
}

void keyboard( unsigned char key, int x, int y ){ 
switch(key) 
{
	break; 
	case '1': linetype=1;
			  break; 
	case '2': linetype=2;
			  break; 
	case '3': linetype=3;
			  break; 
	case '4': exit(0);
	default  : linetype=0;
			   break; 
}
}

void mouse(int button, int state, int x, int y)
{
if (state == GLUT_DOWN)
{
	if (button == GLUT_LEFT_BUTTON) 
	{
		if ((numpoints % 2 )== 0)
		{
			numpoints = 0;
			xx0 = x;
			yy0 = win_height - y;
			numpoints++;
		}
		else if ((numpoints % 2) == 1)
		{
			xx1 = x;
			yy1 = win_height - y;
			numpoints++;
     	} 
     }
}
glutPostRedisplay();
}

int main (int argc, char *argv[])
{
glutInit( &argc, argv );
glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
glutInitWindowSize( win_width, win_height );
glutCreateWindow( "Bresenham's Line Drawing" );
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutKeyboardFunc(keyboard);
glutMouseFunc(mouse);
glutMainLoop(); 
}