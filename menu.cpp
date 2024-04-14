#include <iostream>
#include <GL/glut.h>
#include <math.h>

int n=0, flag=0, pX[100], pY[100];

struct GLColor {
	GLfloat red;
	GLfloat green;
	GLfloat blue;
};

GLColor colors[6] = {
{0.0f, 0.0f, 0.0f}, // Black
{1.0f, 0.0f, 0.0f}, // Red
{0.0f, 1.0f, 0.0f}, // Green
{0.0f, 0.0f, 1.0f}, // Blue
{1.0f, 1.0f, 0.0f}, // Yellow
{1.0f, 0.0f, 1.0f} // Purple
};

GLColor color = colors[0]; // Default: Black

void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(color.red, color.green, color.blue);
	glPointSize(1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void display(void) {

}

void drawPixel(int x,int y){
    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
    glFlush();
}

void drawPolygon(){
	//glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);

    glBegin(GL_LINES);
    for(int i=0;i<n;i++)
    {
        int k=(i+1)%n;
        glVertex2f(pX[i], pY[i]);
        glVertex2f(pX[k], pY[k]);
    }
    glEnd();
    glFlush();
}


void boundaryFill(int x, int y, float* fillColor, float* bc)
{
    float color[3];
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);
    
    if((color[0]!=bc[0] || color[1]!=bc[1] || color[2]!=bc[2])&&(
     color[0]!=fillColor[0] || color[1]!=fillColor[1] || color[2]!=fillColor[2]))
    {
        glColor3f(fillColor[0],fillColor[1],fillColor[2]);
        glBegin(GL_POINTS);
            glVertex2i(x,y);
        glEnd();
        glFlush();
        boundaryFill(x+1,y,fillColor,bc);
        boundaryFill(x-1,y,fillColor,bc);
        boundaryFill(x,y+1,fillColor,bc);
        boundaryFill(x,y-1,fillColor,bc);
    }
}


void floodFill(int x,int y,int R,int G,int B){
    if(x<0 || x>=640 || y<0 || y>=480){
        return ;
    }

    int redPix, greenPix, bluePix;
    unsigned char pixel[4];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    redPix=(int)pixel[0];
    greenPix=(int)pixel[1];
    bluePix=(int)pixel[2];

    if(redPix!=R || greenPix!=G || bluePix!=B){
        return ;
    }

    drawPixel(x,y);
    floodFill(x+1, y, redPix, greenPix, bluePix);
    floodFill(x, y+1, redPix, greenPix, bluePix);
    floodFill(x-1, y, redPix, greenPix, bluePix);
    floodFill(x, y-1, redPix, greenPix, bluePix);

    return ;
}


void mouseFn(int button, int state, int x, int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        pX[n]=x;
        pY[n]=480-y;
        n++;
    }
}

void key(unsigned char key_t, int x, int y)
{
	if(key_t=='d')
	{
		drawPolygon();
		glutMouseFunc(mouseFn);
	}
}

void mouseFnBF(int button,int state,int x,int y)
{
	    
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        float bCol[] = {1,0,0};
        float col[]={color.red, color.green, color.blue};
        //glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,intCol);
        boundaryFill(x,480-y,col,bCol);
        flag=0;
        n=0;
        glutMouseFunc(mouseFn);
    }
}

void mouseFnFF(int button,int state,int x,int y)
{
	
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        unsigned char pixel[4];
        glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
        int R,G,B;
        R=(int)pixel[0];
        G=(int)pixel[1];
        B=(int)pixel[2];
        floodFill(x,480-y,R,G,B);
        n=0;
        flag=0;
        glutMouseFunc(mouseFn);
    }
}



void mainMenuHandler(int choice) {
	switch(choice) {
		case 0://draw poly
			n=0;
			glutMouseFunc(mouseFn);
		break;
	
		case 1: // Boundary Fill
			glutMouseFunc(mouseFnBF);
		break;

		case 2: // Flood Fill
			glutMouseFunc(mouseFnFF);
		break;

		case 3: // Scan Line (YX)
			exit(0);
		break;

		case 4: // Exit
			exit(0);
		break;
	}
}

void subMenuHandler(int choice) {
	color = colors[choice];
	//glColor3f(color);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(640, 480);
	glutCreateWindow("OpenGL Fill Algorithms ");
	glutDisplayFunc(display);
	init();
	glutKeyboardFunc(key);

	int subMenu = glutCreateMenu(subMenuHandler);
	glutAddMenuEntry("Default", 0);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Yellow", 4);
	glutAddMenuEntry("Purple", 5);

	glutCreateMenu(mainMenuHandler);
	glutAddSubMenu("Change Color", subMenu);
	glutAddMenuEntry("Draw Poly", 0);
	glutAddMenuEntry("Boundary Fill", 1);
	glutAddMenuEntry("FloodFill", 2);
	glutAddMenuEntry("Scan Line (YX)", 3);
	glutAddMenuEntry("Exit", 4);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();

	return 0;
}
