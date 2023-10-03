#include <stdio.h>
#include <GL/glut.h>

FILE *archivo = NULL;

void reshape_cb (int w, int h) {
	if (w==0||h==0) return;
	glViewport(0,0,w,h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D(0,w,0,h);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}

void display_cb() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,0); glLineWidth(1);
	
	float x1, y1, x2, y2;
	
	glBegin(GL_LINES);
		while(fscanf(archivo,"%f %f %f %f",&x1,&y1,&x2,&y2) == 4){
			glVertex2f(x1,y1);glVertex2f(x2,y2);
		}
		fclose(archivo);
	glEnd();
	glFlush();
	glutSwapBuffers();
}

void initialize(char *location) {
	glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize (640,480);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("Dibujado de figuras");

	archivo = fopen(location,"r");

	glutDisplayFunc (display_cb);
	glClearColor(1.f,1.f,1.f,1.f);
}

int main (int argc, char **argv) {
	glutInit (&argc, argv);
	initialize(argv[1]);
	glutMainLoop();
	return 0;
}

