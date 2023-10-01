#include<GL/glut.h>
#include<math.h>

void LineDDA(int x1, int y1, int x2, int y2){
	int dm = 0;
	if (abs(x2-x1)>= abs(y2-y1)) // abs es una funci�n para valor absoluto
		dm = abs (x2-x1); // x es la direcci�n de la longitud
	else
		dm = abs (y2-y1); // y es la direcci�n de la longitud
	
	float dx = (float)(x2 - x1) / dm;
	float dy = (float)(y2 - y1) / dm;
	
	// Redondea las coordenadas actuales
	float x = x1 + 0.5;
	float y = y1 + 0.5;
	
	glColor3f (0.0f, 0.0f, 1.0f); // azul
	glPointSize(1);
	for (int i = 0; i < dm; i++)
	{
		glBegin(GL_POINTS);
		glVertex2i((int)x, (int)y);
		
		glEnd();
		x += dx;
		y += dy;
	}
}

void myDisplay()
{
	glClearColor (1.0, 1.0, 1.0, 1.0); // Color claro, blanco
	glClear (GL_COLOR_BUFFER_BIT); // Elimina el b�fer, usa el color claro anterior para eliminar

	glEnd();
	
	LineDDA(0, 100, 200, 100);
	glFlush();
	LineDDA(200, 84, 10, 45);
	glFlush();
	LineDDA(500, 0, 500, 100);
	glFlush (); // Actualizaci�n forzada
}

void Reshape(int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); // Definir el tama�o de la ventana gr�fica
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (0.0, (GLdouble) w, 0.0, (GLdouble) h); // Hacer que las coordenadas de la esquina inferior izquierda sean (0, 0) y las coordenadas de la esquina superior derecha sean (w, h)
}

int main(int argc, char* argv[])
{
	glutInit (& argc, argv); // Inicializar GLUT
	glutInitDisplayMode (GLUT_RGB | GLUT_SINGLE); // Modo de visualizaci�n
	glutInitWindowPosition (100, 100); // Posici�n de la ventana, las coordenadas de la esquina superior izquierda de la ventana en la pantalla
	glutInitWindowSize (600, 600); // Tama�o de la ventana
	glutCreateWindow ("DDA"); // Crea una ventana, el par�metro es el t�tulo de la ventana
	glutDisplayFunc (myDisplay); // D�gale a GLUT qu� funci�n es responsable del dibujo, es decir, registre una funci�n de dibujo myDisplay
	glutReshapeFunc (Reshape); // Cuando la ventana cambia, que funci�n se usa para redibujar
	glutMainLoop (); // Maneja la monitorizaci�n del bucle sin fin
}
