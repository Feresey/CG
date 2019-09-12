#include <GL/glut.h>
#include <cmath>
#include <vector>

int width = 800,
    height = 800;

double a = 5, b = 20;

template <class Func, class Iter>
std::vector<double> calculate(Func&& f, Iter first, Iter last)
{
    std::vector<double> res;
    for (Iter it = first; it != last; ++it)
        res.push_back(f(*it));
    return res;
}

void Psinus()
{
    std::vector<double> phi;
    for (double i = -2 * M_PI; i < 2 * M_PI; i += 0.01f)
        phi.push_back(i);

    std::vector<double> y = calculate([](double var) { return a * var + b * sin(var); }, phi.begin(), phi.end()),
                        x = calculate([](double var) { return a - b * cos(var); }, phi.begin(), phi.end());
    size_t size = phi.size();
    double scale = 5.0;

    glBegin(GL_LINE_STRIP);

    for (size_t i = 0; i + 1 < size; i += 1) {
        glVertex2d(scale * y[i], scale * x[i]);
        // glVertex2d(scale * x[i + 1], scale * y[i + 1]);
    }
    glEnd();
}

void DrawGrid()
{
    // //     void DrawGrid()
    // // {
    //      for (int y = -10; y < 10; y += 1)
    //      {
    //      for (int x = -10; x < 10; x += 1)
    //      {
    //          glPointSize (1);
    //          glBegin (GL_POINTS);
    //              glColor3d(1, 1, 1);
    //              glVertex2d(x, y);
    //          glEnd();
    //      }
    //      };
    // // }
    glPushMatrix();
    glColor3d(1, 1, 1);

    glBegin(GL_LINES);
    for (double i = -width / 2; i <= width / 2; i += 20) {
        glVertex2d(i, -height / 2);
        glVertex2d(i, height / 2);
    }
    for (double i = -height / 2; i <= height / 2; i += 20) {
        glVertex2d(-width / 2, i);
        glVertex2d(width / 2, i);
    }
    glEnd();
    glPopMatrix();
}

void DrawFunc()
{
    glClear(GL_COLOR_BUFFER_BIT);
    // glColor3d(1, 0, 0);

    // glPointSize(10);
    Psinus();
    // DrawGrid();

    glutSwapBuffers();
    // glFlush();
}

void Initialize()
{

    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width / 2, width / 2, -height / 2, height / 2, -200, 200);
    glMatrixMode(GL_MODELVIEW);
    glScaled(0.8, 0.8, 1);
    // glTranslated(50,50,50);
}

void Timer(int)
{
    glRotated(1, 0, 0, 1);
    glutPostRedisplay();
    glutTimerFunc(50, Timer, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(534, 157);

    glutCreateWindow("MyOpenGL");
    // glutWindowClass();
    glutDisplayFunc(&DrawFunc);
    // glutTimerFunc(50, Timer, 0);
    Initialize();
    glutMainLoop();
    return 0;
}
