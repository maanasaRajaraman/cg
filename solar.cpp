#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include<string>
using namespace std;

float xRotated = 90.0, yRotated = 0.0, zRotated = 0.0;
float xtrans=0, ytrans=0;

#define FPS 1000
#define KEY_ESC 27

//________________________________________________________________________________________________________________________________
void reshapeFunc(int x, int y)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);
}
//________________________________________________________________________________________________________________________________


void Draw_Spheres()
{
    glClearColor(0/Red Component/, 0.0/Green Component/,
                0.0/Blue Component/, 0 /Alpha component/); 
    glClear(GL_COLOR_BUFFER_BIT); 
    glMatrixMode (GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0+xtrans,0.0+ytrans,-15.0);

// SUN
    glColor4f(1.0,1.0,0.0,0.0);    //Yellow color
    glPushMatrix();
    glTranslatef(-12.5+xtrans,0.0+ytrans,0.0);
    glutSolidSphere(4.0,50,50);
    glPopMatrix();

// Mercury
    glColor3f(0.0,0.1,0.1);    //Dark Grey color
    glPushMatrix();
    glTranslatef(-7+xtrans,0.0+ytrans,0.0);
    glRotatef(60.0,1,0,0);
    glRotatef(zRotated*1.5,0,0,1);
    glutSolidSphere(0.4,15,10);
    glPopMatrix();

// Venus
    glColor4f(1.0,0.5,0.0,0.0);    //Orange Brown color
    glPushMatrix();
    glTranslatef(-5.5+xtrans,0.0+ytrans,0.0);
    glRotatef(60.0,1,0,0);
    glRotatef(zRotated,0,0,1);
    glutSolidSphere(0.7,20,20);
    glPopMatrix();
//Earth
    glColor3f(0.1,0.2,0.8);    //Blue color
    glPushMatrix();
    glTranslatef(-3.8+xtrans,0.0+ytrans,0.0);
    glRotatef(60.0,1,0,0);
    glRotatef(zRotated*3,0,0,1);
    glutSolidSphere(0.7,20,20);
    glPopMatrix();

//Mars
    glColor3f(0.8,0.2,0.1);    //Red color
    glPushMatrix();
    glTranslatef(-2.3+xtrans,0.0+ytrans,0.0);
    glRotatef(125.0,1,0,0);
    glRotatef(zRotated*4.0,0,0,1);
    glutSolidSphere(0.5,20,15);
    glPopMatrix();

//Jupiter
    glColor3f(1.0,0.5,0.0);    //Orange color
    glPushMatrix();
    glTranslatef(-0.5+xtrans,0.0+ytrans,0.0);
    glRotatef(125.0,1,0,0);
    glRotatef(zRotated*7.0,0,0,1);
    glutSolidSphere(1.0,20,40);
    glPopMatrix();


// Saturn
    glColor3f(0.0,0.5,0.5);    //Bluish Green
    glPushMatrix();
    glTranslatef(2.0+xtrans,0.0+ytrans,0.0);
    glRotatef(60.0,1,0,0);
    glRotatef(zRotated*6.5,0,0,1);
    glutSolidSphere(1.0,20,30);
    glPopMatrix();

//Uranus
    glColor3f(0.5,1.0,1.0);    //Cyan Color,
    glPushMatrix();
    glTranslatef(4.0+xtrans,0.0+ytrans,0.0);
    glRotatef(125.0,1,0,0);
    glRotatef(zRotated*5.0,0,0,1);
    glutSolidSphere(0.7,20,20);
    glPopMatrix();


//Neptune
    glColor3f(0.1,0.0,1.0);    //Purple Color,
    glPushMatrix();
    glTranslatef(6.0+xtrans,0.0+ytrans,0.0);
    glRotatef(60.0,1,0,0);
    glRotatef(zRotated*5.5,0,0,1);
    glutSolidSphere(0.7,20,20);
    glPopMatrix();

    glutSwapBuffers();
}
//________________________________________________________________________________________________________________________________

void idleFunc()
{
    zRotated+=0.1;
    glutPostRedisplay();
}

static void arrowKey(int key, int x, int y)
{
    cout << key << "pressed\n";
    switch(key)
    {
        case GLUT_KEY_LEFT:
            cout << "GLUT_KEY_LEFT" << "Pressed ";
            xtrans-=1;
            break;

        case GLUT_KEY_RIGHT:
            cout << "GLUT_KEY_RIGHT" << "Pressed ";
            xtrans+=1;
            break;

        case GLUT_KEY_UP:
            cout << "GLUT_KEY_UP" << "Pressed ";
            ytrans+=1;
            break;

       case GLUT_KEY_DOWN:
            cout << "GLUT_KEY_DOWN" << "Pressed ";
            ytrans-=1;
            break;

    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(ex, ey, ez,  0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glutPostRedisplay();
}
//________________________________________________________________________________________________________________________________

void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); 
}
//________________________________________________________________________________________________________________________________

void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC/* Escape key ASCII*/) {
        exit(1);
    }
}


//________________________________________________________________________________________________________________________________

int main(int argc, char*argv[]) {
    int width = 1300, height = 800; 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 
    glutInitWindowPosition(50, 50); 
    glutInitWindowSize(width, height);
    glutCreateWindow("Computer Graphics: 3D Solar System Scene"); 
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    SetCanvasSize(width, height);
    glutDisplayFunc(Draw_Spheres); 
    glutReshapeFunc(reshapeFunc);
    glutIdleFunc(idleFunc);
    glutKeyboardFunc(PrintableKeys);
    glutSpecialFunc(arrowKey); 
    glutMainLoop();
    return 1;
}
