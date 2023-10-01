#include <GL/glut.h>
#include <stdio.h>

/*int x1, y1, x2, y2;*/

void myInit() {
	
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
}

void draw_pixel(int x, int y) {
	/*glColor3f(1.0f,0.0f,1.0f);*/
	glPointSize(1);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void draw_line(int x1, int y1, int x2, int y2) {
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x,y;
	
	dx = x2-x1;
	dy = y2-y1;
	
	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (x2 < x1) incx = -1;
	incy = 1;
	if (y2 < y1) incy = -1;
	x = x1; y = y1;
	if (dx > dy) {
		draw_pixel(x, y);
		e = 2 * dy-dx;
		inc1 = 2*(dy-dx);
		inc2 = 2*dy;
		for (i=0; i<dx; i++) {
			if (e >= 0) {
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			draw_pixel(x, y);
		}
		
	} else {
		draw_pixel(x, y);
		e = 2*dx-dy;
		inc1 = 2*(dx-dy);
		inc2 = 2*dx;
		for (i=0; i<dy; i++) {
			if (e >= 0) {
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			draw_pixel(x, y);
		}
	}
}

void myDisplay() {
	
	//Se dibuja un triángulo
	glColor3f(1.0f,0.0f,0.0f);
	draw_line(100, 100, 150, 100);
	draw_line(150,100,125,150);
	draw_line(125,150,100,100);
	
	//Se dibuja un cuadrado
	glColor3f(0.0f,1.0f,0.0f);
	draw_line(200,100,250,100);
	draw_line(250,100,250,150);
	draw_line(250,150,200,150);
	draw_line(200,150,200,100);
	
	//Se dibuja un pentágono
	glColor3f(0.0f,0.0f,1.0f);
	draw_line(300,100,350,100);
	draw_line(350,100,375,150);
	draw_line(375,150,325,200);
	draw_line(325,200,275,150);
	draw_line(275,150,300,100);
	
	//Se dibuja un hexágono
	draw_line(100,300,150,300);
	draw_line(150,300,175,350);
	draw_line(175,350,150,400);
	draw_line(150,400,100,400);
	draw_line(100,400,50,350);
	draw_line(50,350,100,300);
	
	glFlush();
}

int main(int argc, char **argv) {
	
	//	printf( "Enter (x1, y1, x2, y2)\n");
	//	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Línea de Bressenham");
	myInit();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	
	//1. Coordenadas (se hace el dibujado de las figuras con las coordenadas preingresadas en el código fuente de la ejecución)
	//2. Guardar las coordenadas en un archivo
	//3. Abrir un archivo que contiene las coordenadas y dibujar a partir de lo contenido ahí
}
