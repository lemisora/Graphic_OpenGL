#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include <cmath>

using namespace std;

FILE *archivo = NULL;

struct Coordinate {
    float x1, y1, x2, y2;
};

vector<Coordinate> originalCoordinates; // Coordenadas originales
vector<Coordinate> rotatedCoordinates;  // Almacena las coordenadas convertidas (con rotación aplicada)

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
    glLineWidth(3);

    glBegin(GL_LINES);
    for (const Coordinate& coord : rotatedCoordinates) {
        glVertex2f(coord.x1, coord.y1);
        glVertex2f(coord.x2, coord.y2);
    }
    glEnd();

    glFlush();
    glutSwapBuffers();
}

void initialize(char *location, float rotationAngle) {
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rotated Lines");

    archivo = fopen(location, "r");
    if (archivo == NULL) {
        fprintf(stderr, "Failed to open the file.\n");
        exit(EXIT_FAILURE);
    }

    float x1, y1, x2, y2;
    while (fscanf(archivo, "%f %f %f %f", &x1, &y1, &x2, &y2) == 4) {
        Coordinate origCoord = {x1, y1, x2, y2};
        originalCoordinates.push_back(origCoord); // Store original coordinates
    }

    fclose(archivo);

    // Apply the rotation to the coordinates
    float cosA = cos(rotationAngle);
    float sinA = sin(rotationAngle);

    for (const Coordinate& origCoord : originalCoordinates) {
        float x1 = origCoord.x1 * cosA - origCoord.y1 * sinA;
        float y1 = origCoord.x1 * sinA + origCoord.y1 * cosA;
        float x2 = origCoord.x2 * cosA - origCoord.y2 * sinA;
        float y2 = origCoord.x2 * sinA + origCoord.y2 * cosA;

        Coordinate rotatedCoord = {x1, y1, x2, y2};
        rotatedCoordinates.push_back(rotatedCoord);
    }

    glutDisplayFunc(display_cb);
    glClearColor(1.f, 1.f, 1.f, 1.f);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <rotation_angle_degrees>\n", argv[0]);
        return EXIT_FAILURE;
    }

    float rotationAngle = atof(argv[2]) * M_PI / 180.0; // Convert degrees to radians
    glutInit(&argc, argv);
    initialize(argv[1], rotationAngle);
    glutReshapeFunc(reshape_cb);
    glutMainLoop();
    return 0;
}

