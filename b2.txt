#include<GL/glut.h>
#include<iostream>
#include <math.h>
#include <vector>

using namespace std;

int i = 0;

vector<int>pX;
vector<int>pY;

void init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,640,0,480);
	glFlush();
}

void drawPixel(int x,int y)
{
    glColor3d(1,0,0);
    glPointSize(3.0);
    glBegin(GL_POINTS);
        glVertex2d(x,y);
    glEnd();
    glFlush();
}
void drawCurve()
{
	float u,x,y;
	drawPixel(pX[0],pY[0]);
	drawPixel(pX[3],pY[3]);
	for (u=0.001;u<1;u=u+0.001)
	{
		x=(1-u)*(1-u)*(1-u)*pX[0]+3*(1-u)*(1-u)*u*pX[1]+3*u*u*(1-u)*pX[2]+u*u*u*pX[3];
		y=(1-u)*(1-u)*(1-u)*pY[0]+3*(1-u)*(1-u)*u*pY[1]+3*u*u*(1-u)*pY[2]+u*u*u*pY[3];
		drawPixel(x,y);
	}

}

void display()
{
	//glFlush();
}

void mouseFn(int button, int state, int x, int y)
{
	if(i<4)
	{
		y = 480 - y;
		if(button == GLUT_DOWN && state == GLUT_DOWN)
		{
			pX.push_back(x);
			pY.push_back(y);
			i++;
			drawPixel(x, y);
			cout<<"Control point "<<i<<" : "<<x<<" "<<y<<endl;
		}
	}
	else
	{
		drawCurve();
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Bezier Curve");
    glutDisplayFunc(display);
    init();
    
    glutMouseFunc(mouseFn);
    glutMainLoop();

    return 0;
}

//--------------------------
    include<windows.h>
#include<iostream>
#include<GL/glut.h>
#include<vector>
#include<cmath>
#define SCREEN_HEIGHT 480

using namespace std;
int countt=0;

class Point
{
    public:
        float x;
        float y;
};

bool flag=0;
vector<Point> control;
vector<Point> inter_pt;


void init()
{
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    glFlush();
}

Point calculate_pt(float u)
{
    Point pn;
    float x0=control[countt-4].x;
    float x1=control[countt-3].x;
    float x2=control[countt-2].x;
    float x3=control[countt-1].x;
    float y0=control[countt-4].y;
    float y1=control[countt-3].y;
    float y2=control[countt-2].y;
    float y3=control[countt-1].y;

    pn.x=((x0*pow((1-u),3))+(x1*3*u*pow((1-u),2))+(x2*3*pow(u,2)*(1-u))+(x3*pow(u,3)));
    pn.y=((y0*pow((1-u),3))+(y1*3*u*pow((1-u),2))+(y2*3*pow(u,2)*(1-u))+(y3*pow(u,3)));
    return pn;

}

void bezier()
{
    float i=0;
    while(i<1)
    {
        cout<<i<<endl;
        Point p;
        p=calculate_pt(i);
        inter_pt.push_back(p);
        i+=0.001;
    }
    int j;
    glPointSize(1);
    glColor3f(1,0,1);
    glBegin(GL_POINTS);
        for(j=0;j<inter_pt.size();j++){
            glVertex2f(inter_pt[j].x,inter_pt[j].y);
        }
    glEnd();
    glFlush();
}

void boundary_fill(float x,float y, float *b_col,float *f_col)
{
    float curr[3];
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,curr);

    if((curr[0]!=b_col[0] || curr[1]!=b_col[1] || curr[2]!=b_col[2]) && (curr[0]!=f_col[0] || curr[1]!=f_col[1] || curr[2]!=f_col[2])){
        glColor3f(f_col[0],f_col[1],f_col[2]);
        glBegin(GL_POINTS);
            glVertex2f(x,y);
        glEnd();
        glFlush();

        boundary_fill(x+1,y,b_col,f_col);
        boundary_fill(x-1,y,b_col,f_col);
        boundary_fill(x,y+1,b_col,f_col);
        boundary_fill(x,y-1,b_col,f_col);
    }
}
void mouse(int btn,int state,int x,int y)
{
    y=SCREEN_HEIGHT-y;
    Point p;
    p.x=x;
    p.y=y;

    if(btn==GLUT_LEFT && state==GLUT_DOWN)
    {
        countt++;
        control.push_back(p);
        if(countt%4==0 && countt!=0)
        {
            bezier();
        }

    }
    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        float f_col[]={1,1,0};
        float b_col[]={1,0,1};
        boundary_fill(x,y,b_col,f_col);
    }

}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100,200);
    glutInitWindowSize(640,480);
    glutCreateWindow("GLUT");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
}
