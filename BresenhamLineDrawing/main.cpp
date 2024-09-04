/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include <bits/stdc++.h>
#ifdef __APPLE__

#else
#include <GL/glut.h>
#endif
#include <GL/glut.h>

#include <stdlib.h>
using namespace std;


int x_0, y_0, x_1, y_1;

void bresenhamLineDraw(){
    int dx = abs(x_1 - x_0);
    int dy = abs(y_1 - y_0);
    int dx_0 = x_1 - x_0;
    int dy_0 = y_1 - y_0;
    int x, y, x_end, y_end, x_increment, y_increment;

    float m = abs(dy / dx);

    if( m < 1 ){
        int p = 2 * dy - dx;
        int two_dy = 2 * dy;
        int two_dy_dx = 2 * (dy - dx);
        y_increment = 1;
        if(dx_0 < 0 && dy_0 < 0){
            dy_0 = 1;
            dx_0 = 1;
        }
        if(dx_0 < 0 || dy_0 < 0){
            y_increment = -1;
        }

        if (x_0 > x_1){
            x = x_1;
            y = y_1;
            x_end = x_0;
        }
        else{
            x = x_0;
            y = y_0;
            x_end = x_1;
        }
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        while (x < x_end){
            x++;
            if (p < 0) {
                p += two_dy;
            }
            else {
                y += y_increment;
                p += two_dy_dx;
            }
            glVertex2i(x, y);
            cout << x << " " << y << endl;
        }
        glEnd();
    }
    else{
        int p = 2 * dx - dy;
        int twoDx = 2 * dx;
        int twoDxDy = 2 * (dx - dy);
        x_increment = 1;
        if(dx_0 < 0 && dy_0 < 0){
            dy_0 = 1;
            dx_0 = 1;
        }
        if(dx_0 < 0 || dy_0 < 0){
            x_increment = -1;
        }
        if (y_0 > y_1){
            x = x_1;
            y = y_1;
            y_end = y_0;
        }
        else{
            x = x_0;
            y = y_0;
            y_end = y_1;
        }
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        while (y < y_end){
            y++;
            if (p < 0) {
                p += twoDx;
            } else {
                x += x_increment;
                p += twoDxDy;
            }
            glVertex2i(x, y);
            cout << x << " " << y << endl;
        }
        glEnd();
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2.0);
    glColor3f(1.0, 1.0, 1.0);
    bresenhamLineDraw();
    glFlush();
}

void init(int windowWidth, int windowHeight){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
}

int main(int argc, char *argv[]){
    cout << "Enter the values of x_0 and y_0: ";
    cin >> x_0 >> y_0;
    cout << "Enter the values of x_1 and y_1: ";
    cin >> x_1 >> y_1;

    glutInit(&argc, argv);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Bresenham Line Drawing Algorithm");
    init(640, 480);
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS;
}
