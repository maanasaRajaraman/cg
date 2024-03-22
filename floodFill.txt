#include <GL/glut.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;

int n=0, flag=0, pX[100], pY[100];

void init(){
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void drawPixel(int x,int y){
    glColor3d(1,0,1);
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
    glFlush();
}

void drawPolygon(){
    glColor3d(0,1,1);

    glBegin(GL_LINES);
    for(int i=0;i<n;i++){
        int k=(i+1)%n;
        glVertex2f(pX[i], pY[i]);
        glVertex2f(pX[k], pY[k]);
    }
    glEnd();

    glFlush();
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
    floodFill(x-1, y, redPix, greenPix, bluePix);
    floodFill(x, y+1, redPix, greenPix, bluePix);
    floodFill(x, y-1, redPix, greenPix, bluePix);

    return ;
}

void mouseFn(int button,int state,int x,int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        pX[n]=x;
        pY[n]=480-y;
        n++;
    }
    if(flag==0 && button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        drawPolygon();
        n=0;
        flag=1;
    }
    else if(flag==1 && button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
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
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("Flood Fill");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseFn);
    glutMainLoop();

    return EXIT_SUCCESS;
}
