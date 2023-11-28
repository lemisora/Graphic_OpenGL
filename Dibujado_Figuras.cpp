#include <GL/glut.h>

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
	glColor3f(0,1,0); glLineWidth(1);
	glBegin(GL_LINES);
		//Figuras geométricas 
		//-Triángulo-
		glVertex2f(50,100);glVertex2f(100,100);
		glVertex2f(100,100);glVertex2f(75,150);
		glVertex2f(75,150);glVertex2f(50,100);

		glColor3f(0,0,1);	/*Cambio de color a azul*/
		
		//Cuadrado
		glVertex2f(150,100);glVertex2f(200,100);
		glVertex2f(200,100);glVertex2f(200,150);
		glVertex2f(200,150);glVertex2f(150,150);
		glVertex2f(150,150);glVertex2f(150,100);
	
		glColor3f(1,0,0);	/*Cambio de color a rojo*/
		
		//Pentágono
		glVertex2f(250,100);glVertex2f(300,100);
		glVertex2f(300,100);glVertex2f(325,150);
		glVertex2f(325,150);glVertex2f(275,187.5);
		glVertex2f(275,187.5);glVertex2f(225,150);
		glVertex2f(225,150);glVertex2f(250,100);
		
		glColor3f(0.3,0.8,0.1);
		
		//Hexágono
		glVertex2f(400,100);glVertex2f(450,100);
		glVertex2f(450,100);glVertex2f(487.5,150);
		glVertex2f(487.5,150);glVertex2f(450,200);
		glVertex2f(400,200);glVertex2f(350,200);
//		glVertex2f(350,200);glVertex2f(325,150);
		
	glEnd();
//	glBegin(GL_LINES);
//		glVertex2i( 70,100); glVertex2i(110,100);
//	glEnd();
	glutSwapBuffers();
}

void initialize() {
	glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize (640,480);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("Dibujado de figuras");
	glutDisplayFunc (display_cb);
	glutReshapeFunc (reshape_cb);
	glClearColor(1.f,1.f,1.f,1.f);
}

int main (int argc, char **argv) {
	glutInit (&argc, argv);
	initialize();
	glutMainLoop();
	return 0;
}

