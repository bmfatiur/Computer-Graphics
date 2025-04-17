#include <GL/glut.h>
#include <iostream>

using namespace std;

// Define the clipping window (20, 80, 20, 80)
double xmin = 20, ymin = 20, xmax = 80, ymax = 80;

// Define region codes
const int INSIDE = 0;  // 0000
const int LEFT = 1;    // 0001
const int RIGHT = 2;   // 0010
const int BOTTOM = 4;  // 0100
const int TOP = 8;     // 1000

// Global variables to store user input for the line coordinates
double x1, y1, x2, y2;

// Function to compute the region code for a point (x, y)
int computeCode(double x, double y) {
    int code = INSIDE;

    if (x < xmin)       code |= LEFT;
    else if (x > xmax)  code |= RIGHT;
    if (y < ymin)       code |= BOTTOM;
    else if (y > ymax)  code |= TOP;

    return code;
}

// Cohen-Sutherland clipping algorithm
void cohenSutherlandClip(double x1, double y1, double x2, double y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;

    while (true) {
        if (!(code1 | code2)) {  // Both points inside
            accept = true;
            break;
        } else if (code1 & code2) {  // Both points share an outside region, trivial reject
            break;
        } else {
            // Some segment of the line is within the clip window
            double x, y;
            int codeOut = code1 ? code1 : code2;

            if (codeOut & TOP) {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            } else if (codeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            } else if (codeOut & RIGHT) {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            } else if (codeOut & LEFT) {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            // Replace point outside the window
            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        // Draw the original line outside the clipping window
        glColor3f(0.0, 1.0, 0.0);  // Green
        glBegin(GL_LINES);
        glPointSize(5.0);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
        glEnd();

        // Draw the clipped line inside the clipping window
        glColor3f(0.0, 1.0, 0.0);  // Red
        glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
        glEnd();
    }
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Set up the coordinate system
    gluOrtho2D(0, 100, 0, 100);
    glMatrixMode(GL_MODELVIEW);
    // Draw the clipping rectangle (20, 20, 80, 80)
    glColor3f(1.0, 1.0, 0.0);  // yellow
    glBegin(GL_LINE_LOOP);
    glVertex2d(xmin, ymin);
    glVertex2d(xmax, ymin);
    glVertex2d(xmax, ymax);
    glVertex2d(xmin, ymax);
    glEnd();

    // Draw the initial line before clipping
    glColor3f(1.0, 0.0, 0.0);  // Red
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();

    // Perform clipping and draw the clipped part in red
    cohenSutherlandClip(x1, y1, x2, y2);

    glFlush();
}

int main(int argc, char** argv) {

    cout << "Enter the coordinates of the line (x1, y1, x2, y2): ";
    cin >> x1 >> y1 >> x2 >> y2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cohen-Sutherland Line Clipping Algorithm");

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
