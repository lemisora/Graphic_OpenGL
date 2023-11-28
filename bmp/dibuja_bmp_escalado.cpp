#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

char c;
FILE *archivo = NULL;
int ancho = 800;
int alto = 600;
int deltaX, delta = 5;
int x = 20, y = alto; // Initialize x and y coordinates

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
    glPointSize(1.0);

    glBegin(GL_POINTS);
    while ((c = fgetc(archivo)) != EOF) {
        if (c == '\n') {
            y -= delta; // Move to the next row
            x = 20; // Reset x-coordinate
        } else if (c == '1') {
            glVertex2i(x, y);
        }
        x += delta; // Move to the next column
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
    delta = stoi(string(1, argv[2][0]));
    glutMainLoop();
    return 0;
}

