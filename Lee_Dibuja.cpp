#include <stdio.h>
#include <GL/glut.h>
#include <vector>

FILE *archivo = NULL;
float x1, y1, x2, y2;

struct Coordinate {
	float x1, y1, x2, y2;
};

std::vector<Coordinate> coordinates; // Store the coordinates

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
	glLineWidth(1);
	
	glBegin(GL_LINES);
//		glVertex2f(x1,y1);glVertex2f(x2,y2);
	for (const Coordinate& coord : coordinates) {
		glVertex2f(coord.x1, coord.y1);
		glVertex2f(coord.x2, coord.y2);
	}
	glEnd();
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		fprintf(stderr, "OpenGL error: %s\n", gluErrorString(error));
	}
	
	glFlush();
	glutSwapBuffers();
}

void initialize(char *location) {
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Dibujado de figuras");
	
	archivo = fopen(location, "r");
	if (archivo == NULL) {
		fprintf(stderr, "Failed to open the file.\n");
		exit(EXIT_FAILURE);
	}
	
	float x1, y1, x2, y2;
//	if (fscanf(archivo, "%f %f %f %f", &x1, &y1, &x2, &y2) == 4){
//		printf("\nSe han leído las primeras coordenadas\n");
//	}
	while (fscanf(archivo, "%f %f %f %f", &x1, &y1, &x2, &y2) == 4) {
		
		Coordinate coord = { x1, y1, x2, y2 };
		coordinates.push_back(coord); // Store coordinates in the vector
	}
	
	fclose(archivo);
	
	glutDisplayFunc(display_cb);
	printf("\nSe terminó de dibujar\n");
	glClearColor(1.f, 1.f, 1.f, 1.f);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	initialize(argv[1]);
	glutMainLoop();
	return 0;
}
