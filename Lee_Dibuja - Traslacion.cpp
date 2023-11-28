#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <vector>
#include <chrono>
FILE *archivo = NULL;

struct Coordinate {
	float x1, y1, x2, y2;
};

std::vector<Coordinate> coordinates; //vector para guardar las coordenadas

float trasladoX = 0, trasladoY = 0;

std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
float animationDuration = 1.5f; // Duration of the translation animation in seconds

void updateTranslation() {
	// Calculate the elapsed time since the start of the animation
	auto currentTime = std::chrono::high_resolution_clock::now();
	float elapsedTime = std::chrono::duration<float>(currentTime - startTime).count();
	
	// Calculate the progress of the animation (0.0 to 1.0)
	float progress = elapsedTime / animationDuration;
	trasladoX = 0.0f + 400.0f * progress; // Adjust the factor to control the speed
	trasladoY = 0.0f + 260.0f * progress;   // Adjust the factor to control the speed
	
	// If the animation is not complete, request a redisplay
	if (progress < 1.0f) {
		glutPostRedisplay();
	}
}

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
	
	glPushMatrix();
	glTranslatef(trasladoX,trasladoY,0.0f);
	
	glBegin(GL_LINES);
	for (const Coordinate& coord : coordinates) {
		glVertex2f(coord.x1, coord.y1);
		glVertex2f(coord.x2, coord.y2);
	}
	glEnd();
	
	glPopMatrix();
	glFlush();
	updateTranslation();
	glutSwapBuffers();
}

void initialize(char *location) {
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Dibujado de figuras");
	startTime = std::chrono::high_resolution_clock::now();
	
	archivo = fopen(location, "r");
	if (archivo == NULL) {
		fprintf(stderr, "Failed to open the file.\n");
		exit(EXIT_FAILURE);
	}
	
	float x1, y1, x2, y2;
	while (fscanf(archivo, "%f %f %f %f", &x1, &y1, &x2, &y2) == 4) {
		Coordinate coord = { x1, y1, x2, y2};
		coordinates.push_back(coord); // Store coordinates in the vector
	}
	
	fclose(archivo);
	
	glutDisplayFunc(display_cb);
	glClearColor(1.f, 1.f, 1.f, 1.f);
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	glutInit(&argc, argv);
	initialize(argv[1]);
	glutReshapeFunc(reshape_cb);
	glutMainLoop();
	return 0;
}
