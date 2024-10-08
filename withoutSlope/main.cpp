// without m
#include<iostream>
#include<GL/glut.h>
#include<windows.h>
using namespace std;

const int window_width = 300;
const int window_height = 300;

int x_0, y_0, x_1, y_1;

void draw_line(){
    float dx = x_1 - x_0;
    float dy = y_1 - y_0;

    int steps;
    if( abs(dx) > abs(dy) )
        steps=abs(dx);
    else
        steps=abs(dy);

    float x_increment = dx / steps;
    float y_increment = dy / steps;

    float x = x_0;
    float y = y_0;

    glBegin(GL_POINTS);
    for(int i=0; i<=steps; i++){
        glVertex2i(x, y);
        x += x_increment;
        y += y_increment;
    }
    glEnd();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(2.0);
    draw_line();
    glFlush();
}
void init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, window_width, 0, window_height);

}

int main(int argc, char** argv){
    cout << "Enter the value of x_0 and y_0: ";
    cin >> x_0 >> y_0;
    cout << "Enter the value of x_1 and y_1: ";
    cin >> x_1 >> y_1;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("DDA Line Drawing Algorithm without slope");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
