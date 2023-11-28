#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>

void reshape_cb(int w, int h) {
    if (w == 0 || h == 0) return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display_cb() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 1);
    glPointSize(5.0);  // Increase point size for better visibility

    glBegin(GL_POINTS);
    glVertex2f(20, 40);  // Change the point position (x, y) here
    glEnd();

    glFlush();
    glutSwapBuffers();
}

void initialize(char *location) {
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rotación de un punto");

    glutDisplayFunc(display_cb);
    glClearColor(1.f, 1.f, 1.f, 1.f);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    initialize(argv[1]);
    glutReshapeFunc(reshape_cb);
    glutMainLoop();
    return 0;
}

