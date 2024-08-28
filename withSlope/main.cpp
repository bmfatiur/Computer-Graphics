//Line Drawing using Slope
#include <bits/stdc++.h>
#include <GL/glut.h>
#include <windows.h>
using namespace std;

int x_0, y_0, x_1, y_1;
const int window_width = 300;
const int window_height = 300;

void draw_line(){
    float dx = x_1 - x_0;
    float dy = y_1 - y_0;

    int steps;
    if( abs(dx) >= abs(dy) )
        steps=abs(dx);
    else
        steps=abs(dy);

    float m = dy / dx;

    float m_abs = abs(m);
    float x_increment, y_increment;

    //case 1
    if(m >= 0 && m <= 1 && dx >= 0 && dy >= 0){
        x_increment = 1;
        y_increment = m_abs;
    }
    //case 2
    else if(m >= 0 && m <= 1 && dx < 0 && dy < 0){
        x_increment = -1;
        y_increment = -m_abs;
    }
    //case 3
    else if(m >= -1 && m < 0 && dx > 0 && dy < 0){
        x_increment = 1;
        y_increment = -m_abs;
    }
    //case 4
    else if(m >= -1 && m < 0 && dx < 0 && dy > 0){
        x_increment = -1;
        y_increment = m_abs;
    }
    //case 5
    else if(m > 1 && dx > 0 && dy > 0){
        x_increment = 1 / m_abs;
        y_increment = 1;
    }
    //case 6
    else if(m > 1 && dx < 0 && dy < 0){
        x_increment = -(1 / m_abs);
        y_increment = -1;
    }
    //case 7
    else if(m < -1 && dx > 0 && dy < 0){
        x_increment = 1 / m_abs;
        y_increment = -1;
    }
    //case 8
    else if(m < -1 && dx < 0 && dy  > 0){
        x_increment = -(1 / m_abs);
        y_increment = 1;
    }
    glBegin(GL_POINTS);
    float x = x_0;
    float y = y_0;
    for(int i = 0; i <= steps; i++){
        glVertex2i(x, y);
        cout << x << " " << y << endl;
        x += x_increment;
        y += y_increment;
    }
    glEnd();
}

void display(){
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
    cout << "Enter the values of x_0 & y_0: ";
    cin >> x_0 >> y_0;
    cout << "Enter the values of x_1 & y_1: ";
    cin >> x_1 >> y_1;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("DDA Line Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
