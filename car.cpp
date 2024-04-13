#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

GLfloat ex = 0.0, ey = 0.0, ez = -3.0;

void init()
{
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-4.0, 4.0, -4.0, 4.0, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(ex, ey, ez,  0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

GLfloat vertices[8][3] = {
    {-1.0, -1.0, 1.0}, {-1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}, {1.0, -1.0, 1.0},
    {-1.0, -1.0, -1.0}, {-1.0, 1.0, -1.0}, {1.0, 1.0, -1.0}, {1.0, -1.0, -1.0}
};

GLfloat colors[8][3] = {
    {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 1.0}, {0.0, 1.0, 1.0}
};

void quad(int a, int b, int c, int d)
{
    glBegin(GL_QUADS);
    glVertex3fv(vertices[a]);
    glVertex3fv(vertices[b]);
    glVertex3fv(vertices[c]);
    glVertex3fv(vertices[d]);
    glEnd();
}

void drawCar()
{
    // Body
    glColor3f(1.0, 0.0, 0.0); // Red color for the body
    glPushMatrix();
    glTranslatef(0.0, -1.0, 0.0);
    glScalef(2.0, 1.0, 1.0); // Width, Height, Depth
    glutWireCube(1.0);
    glPopMatrix();

    // Roof
    glColor3f(0.0, 0.0, 1.0); // Blue color for the roof
    glPushMatrix();
    glTranslatef(0.0, -0.3, 0.0);
    glScalef(1.5, 0.8, 1.0); // Width, Height, Depth
    glutWireCube(1.0);
    glPopMatrix();

    // Wheels
    glColor3f(0.0, 1.0, 0.0); // Green color for the wheels
    glPushMatrix();
    glTranslatef(-0.75, -1.5, 0.6); // Front left wheel
    glutWireSphere(0.25, 20, 20);
    glTranslatef(1.5, 0.0, 0.0); // Front right wheel
    glutWireSphere(0.25, 20, 20);
    glTranslatef(0.0, 0.0, -1.2); // Rear right wheel
    glutWireSphere(0.25, 20, 20);
    glTranslatef(-1.5, 0.0, 0.0); // Rear left wheel
    glutWireSphere(0.25, 20, 20);
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(ex, ey, ez,  0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    drawCar();
    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            ez += 1.0;
            break;

        case '-':
            ez -= 1.0;
            break;
    }
    glutPostRedisplay();
}

static void arrowKey(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
            ex -= 0.1;
            break;

        case GLUT_KEY_RIGHT:
            ex += 0.1;
            break;

        case GLUT_KEY_UP:
            ey += 0.1;
            break;

        case GLUT_KEY_DOWN:
            ey -= 0.1;
            break;
    }
    glutPostRedisplay();
}

void resize(int width, int height)
{
    glViewport(0, 0, width, height);
    double aspect = (double) width / (double) height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (aspect < 1.0)
        glOrtho(-4., 4., -4. / aspect, 4. / aspect, 1., 100.);
    else
        glOrtho(-4. * aspect, 4. * aspect, -4., 4., 1., 100.);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0., 0., 5., 0., 0., 0., 0., 1., 0.);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("3D Car");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(arrowKey);

    init();

    glutMainLoop();

    return EXIT_SUCCESS;
}
