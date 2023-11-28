#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <chrono>

using namespace std;

char c;
FILE *archivo = NULL;
int ancho = 800;
int alto = 600;
int x = 20, y = alto;

vector<pair<int,int>> puntos;
vector<pair<int, int>> puntosTrasl;

float trasladoX, trasladoY;

chrono::time_point<chrono::high_resolution_clock> startTime;
float animationDuration = 1.5f;

void updateTranslation() {
	// Calculate the elapsed time since the start of the animation
	auto currentTime = chrono::high_resolution_clock::now();
	float elapsedTime = chrono::duration<float>(currentTime - startTime).count();
	
	// Calculate the progress of the animation (0.0 to 1.0)
	float progress = elapsedTime / animationDuration;
	trasladoX = 0.0f + ancho/2 * progress; // Adjust the factor to control the speed
	trasladoY = 0.0f + alto * progress;   // Adjust the factor to control the speed
	
	// If the animation is not complete, request a redisplay
	if (progress < 1.0f) {
		glutPostRedisplay();
	}
}

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

    glPushMatrix();
    glTranslatef(trasladoX, trasladoY, 0.0f);

    glBegin(GL_POINTS);
    for(const auto &point : puntos) {
      glVertex2i(point.first, point.second);
    }
    glEnd();
    glPopMatrix();

    //fclose(archivo);
    glFlush();
    updateTranslation();
    glutSwapBuffers();
}

void initialize(char *location) {
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(ancho, alto);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Dibujado de mapa de bits");

    archivo = fopen(location, "r");

     while((c = fgetc(archivo)) != EOF){
      if(c == '\n'){
        y -= 1;
        x = 20;
      }else if(c == '1'){
        puntos.push_back({x,y});
      }
      x += 1;
    }
    fclose(archivo);

    glutDisplayFunc(display_cb);
    glutReshapeFunc(reshape_cb);

    glClearColor(1.f, 1.f, 1.f, 1.f);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    initialize(argv[1]);
    glutReshapeFunc(reshape_cb);
    glutMainLoop();
    return 0;
}

