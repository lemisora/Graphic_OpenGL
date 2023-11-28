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

vector<Coordinate> originalCoordinates; // Store the original coordinates
vector<Coordinate> centeredCoordinates;  // Store the centered coordinates
vector<Coordinate> coordRot;

void reshape_cb(int w, int h) {
    if (w == 0 || h == 0) return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Function to calculate the center of the drawing
Coordinate calculateCenter() {
    float sumX = 0.0f;
    float sumY = 0.0f;
    int pointCount = 0;

    for (const Coordinate& coord : originalCoordinates) {
        sumX += coord.x1 + coord.x2;
        sumY += coord.y1 + coord.y2;
        pointCount += 2;
    }

    float centerX = sumX / pointCount;
    float centerY = sumY / pointCount;

    return {centerX, centerY, centerX, centerY};
}

void display_cb() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 1);
    glLineWidth(3);

    glBegin(GL_LINES);
    for (const Coordinate& coord : coordRot) {
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
    glutCreateWindow("Centered Drawing");

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

    Coordinate center = calculateCenter();

    for (const Coordinate& origCoord : originalCoordinates) {
        float x1 = origCoord.x1 - center.x1;
        float y1 = origCoord.y1 - center.y1;
        float x2 = origCoord.x2 - center.x2;
        float y2 = origCoord.y2 - center.y2;

        centeredCoordinates.push_back({x1, y1, x2, y2});
    }

	float cosA = cos(rotationAngle);
	float sinA = sin(rotationAngle);
	
	for (const Coordinate& centCoord : centeredCoordinates) {
		float x1 = centCoord.x1 * cosA - centCoord.y1 * sinA;
		float y1 = centCoord.x1 * sinA + centCoord.y1 * cosA;
		float x2 = centCoord.x2 * cosA - centCoord.y2 * sinA;
		float y2 = centCoord.x2 * sinA + centCoord.y2 * cosA;
		
		Coordinate coordRotated = {x1, y1, x2, y2};
		coordRot.push_back(coordRotated);
	}
	
    glutDisplayFunc(display_cb);
    glClearColor(1.f, 1.f, 1.f, 1.f);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
	float rotationAngle = atof(argv[2])*M_PI/180.0;
    glutInit(&argc, argv);
    initialize(argv[1], rotationAngle);
    glutReshapeFunc(reshape_cb);
    glutMainLoop();
    return 0;
}

