#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <cstdio>
#include <stdlib.h>

using namespace std;

char c;
FILE *archivo = NULL;
int ancho = 800;
int alto = 600;
int x = 20, y = alto - 20; // Initialize x and y coordinates

void reshape_cb(int w, int h) {
    if (w == 0 || h == 0)
        return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display_cb() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);
    glPointSize(5.0);

    glBegin(GL_POINTS);
    while ((c = fgetc(archivo)) != EOF) {
        if (c == '\n') {
            y -= 5; // Move to the next row
            x = 20; // Reset x-coordinate
        } else if (c == '1') {
            glVertex2i(x, y);
        }
        x += 5; // Move to the next column
    }
    glEnd();

    fclose(archivo);
    glFlush();
    glutSwapBuffers();
}

void initialize(char *location) {
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(ancho, alto);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Dibujado de mapa de bits");

    archivo = fopen(location, "r");

    glutDisplayFunc(display_cb);
    glutReshapeFunc(reshape_cb);

    glClearColor(1.f, 1.f, 1.f, 1.f); 
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    initialize(argv[1]);
    glutMainLoop();
    return 0;
}

