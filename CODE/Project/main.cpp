#include <iostream>
#include <vector>
#include <cmath>
#include <GL/glut.h>
using namespace std;
struct Point
{
    float x, y;
};
vector<Point> original;
vector<Point> transformed;

void drawPolygon(const std::vector<Point>& vertices) {
    glBegin(GL_POLYGON);
    for (const auto& vertex : vertices) {
        glVertex2f(vertex.x, vertex.y);
    }
    glEnd();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    drawPolygon(original);
    glColor3f(0.0, 1.0, 0.0);
    drawPolygon(transformed);
    glFlush();
}

void initialize()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(-100, 100, -100, 100);
}

void applyTranslation(float tx, float ty)
{
    transformed.clear();
    for (const auto& pt : original)
    {
        Point newPt;
        newPt.x = pt.x + tx;
        newPt.y = pt.y + ty;
        transformed.push_back(newPt);
    }
}
void applyScaling(float sx, float sy, float fx, float fy)
{
    transformed.clear();
    for (const auto& pt : original)
    {
        Point newPt;
        newPt.x = (pt.x - fx) * sx + fx;
        newPt.y = (pt.y - fy) * sy + fy;
        transformed.push_back(newPt);
    }
}

void applyRotation(float angle, int pivotX, int pivotY)
{
    transformed.clear();
    float radianAngle = (angle * 3.1416) / 180.0;
    for (const auto& p : original)
    {

        float translateX = p.x - pivotX;
        float translateY = p.y - pivotY;

        float rotationX = translateX * cos(radianAngle) - translateY * sin(radianAngle);
        float rotationY = translateX * sin(radianAngle) + translateY * cos(radianAngle);
        Point newPoint;
        newPoint.x = rotationX + pivotX;
        newPoint.y = rotationY + pivotY;
        transformed.push_back(newPoint);
    }
}
void applyReflection(char option)
{
     transformed.clear();
    for (const auto& p : original)
    {
        Point newPoint;
        if(option == 'a')
        {
            newPoint.x = p.x;
            newPoint.y = -p.y;

        }
        else if(option == 'b')
        {
           newPoint.x = -p.x;
           newPoint.y = p.y;
        }
        else if(option == 'c')
        {
           newPoint.x = p.y;
           newPoint.y = p.x;
        }
        else
        {
          newPoint.x = -p.x;
          newPoint.y = -p.y;
        }

        transformed.push_back(newPoint);

    }

}
void applyShearing(float sh, char option)
{
    transformed.clear();
    for (const auto& p : original)
    {

        Point newPoint;
        if(option == 'X')
        {
            newPoint.x = p.x + (sh * p.y);
            newPoint.y = p.y;
        }
        else
        {
          newPoint.x = p.x;
          newPoint.y = p.y + (sh * p.x);
        }

        transformed.push_back(newPoint);
    }

}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Polygon Transformation");
    initialize();
    glutDisplayFunc(display);
    glutMainLoop();

    int option=1;
    while(option==1 || option==2 || option==3 || option==4 || option==5){
        cout << "2D Geometric Transformation" << endl;
        cout << "........................................" << endl;
        cout << "1 -> Translation " << endl;
        cout << "2 -> Scaling (Fixed Point)" << endl;
        cout << "3 -> Rotation (Rotation / Pivot Point)" << endl;
        cout << "4 -> Reflection " << endl;
        cout << "5 -> Shearing" << endl;
        cout << "6 -> Quit" << endl;
        cout << "Enter your option: ";
        cin >> option;

        switch (option)
        {
            case 1:
                {
                cout << "================Translation================" << endl;
                int n;
                cout << "Enter the number of vertices: ";
                cin >> n;

                original.resize(n);
                cout << "Enter the coordinates of each vertex (x,y): " <<endl;
                for (int i = 0; i < n; ++i) {
                    cout<<i+1<<" -> ";
                    cin >> original[i].x >> original[i].y;
                }

                float tx, ty;
                cout << "Enter translation factors (tx,ty): ";
                cin >> tx >> ty;
                applyTranslation(tx, ty);
                display();
                break;
            }
             case 2:
              {
                cout << "================Scaling================" << endl;
                int n;
                cout << "Enter the number of edges of the polygon: ";
                cin >> n;

                original.resize(n);
                cout << "Enter the coordinates of each vertex (x y): "<< endl;
                for (int i = 0; i < n; ++i) {
                    cout<<i+1<<" -> ";
                    cin >> original[i].x >> original[i].y;
                }

                float sx, sy, fx, fy;
                cout << "Enter the value of Scaling factor (SX,SY) :" << endl;
                cin >> sx >> sy;
                cout<<"Fixed point ( 1-Yes & 0-No ): ";
                int fixedPoint;
                cin>>fixedPoint;
                cout << "Enter the fixed point (fX,fY): " << endl;
                cin >> fx >> fx;
                applyScaling(sx, sy, fx, fy);
                break;
            }

            case 3:
             {
                cout << "================Rotation================" << endl;
                int n;
                cout << "Enter the number of edges of the polygon: ";
                cin >> n;

                original.resize(n);
                cout << "Enter the coordinates of each vertex (x,y): "<< endl;
                for (int i = 0; i < n; ++i) {
                    cout<<i+1<<" -> ";
                    cin >> original[i].x >> original[i].y;
                }

                float angle, xr, yr;
                cout << "Enter the value of the Theta (Angle) for Rotation (Degree):" << endl;
                cin >> angle;
                cout << "Enter the Pivot/Rotation point (xr,yr): " << endl;
                cin >> xr >> yr;
                applyRotation(angle, xr, yr);
                break;
            }
            case 4:
            {
                cout << "================Reflection================" << endl;
                int n;
                cout << "Enter the number of edges of the polygon: ";
                cin >> n;

                original.resize(n);
                cout << "Enter the coordinates of each vertex (x,y): " <<endl;
                for (int i = 0; i < n; ++i) {
                    cout<<i+1<<" -> ";
                    cin >> original[i].x >> original[i].y;
                }
                char axis;
                cout << "Enter the axis of reflection (a -> X-axis, b -> Y-axis, c -> Origin, d -> X=Y axis): ";
                cin >> axis;

                applyReflection(axis);
                break;
            }
            case 5:
            {
                cout << "================Shearing================" << endl;
                int n;
                cout << "Enter the number of edges of the polygon: ";
                cin >> n;

                original.resize(n);
                cout << "Enter the coordinates of each vertex (x,y): "<< endl;
                for (int i = 0; i < n; ++i) {
                    cout<<i+1<<" -> ";
                    cin >> original[i].x >> original[i].y;
                }
                float sh;
                char axis;
                cout << "Enter the shearing factors (X for x-axis, Y for y-axis): ";
                cin >> axis;
                cout << "Enter the Shearing value : " << endl;
                cin >> sh;
                applyShearing(sh, axis);
                break;
            }
            default:
                cout << "Quit" << endl;
                break;
        }

    }




    return 0;
}
