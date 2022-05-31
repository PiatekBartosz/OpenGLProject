#include <iostream>
#include "glut.h"
#include "GLU.h"
#include "GL.h"


// NOTE: use 'q'/'e' to change draw mode

// screen size
size_t width = 1024;
size_t height = 768;

// camera movemetnt
double cameraSpeed = 0.2;
double xRotation = 0.1;
double xTranslate = 0.0;
double zTranslate = 0.0;

void OnReshape(int w, int h);
void OnRender(void);
void OnSpecialKeypress(int key, int x, int y);
void OnKeypress(unsigned char key, int x, int y);
void DrawHUD();


int main(int argc, char** argv) {

	// setup
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(50, 50);
	int winIndex = glutCreateWindow("OpenGL Program");
	std::cout << "Window index: " << winIndex << std::endl;

	// callback functions
	glutDisplayFunc(OnRender);
	glutIdleFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutSpecialFunc(OnSpecialKeypress);
	glutKeyboardFunc(OnKeypress);

	

	glutMainLoop();
	return 0;
}

void OnSpecialKeypress(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		zTranslate += 0.3;
		break;
	case GLUT_KEY_DOWN:
		zTranslate -= 0.3;
		break;
	case GLUT_KEY_LEFT:
		xTranslate += 0.3;
		break;
	case GLUT_KEY_RIGHT:
		xTranslate -= 0.3;
		break;
	}
}

void OnKeypress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		zTranslate += 0.3;
		break;
	case 's':
		zTranslate -= 0.3;
		break;
	case 'a':
		xTranslate += 0.3;
		break;
	case 'd':
		xTranslate -= 0.3;
		break;

	case 'q':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'e':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void DrawHUD()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
}



void OnReshape(int w, int h) {
	width = w;
	height = h;

	// viewport update
	glViewport(0, 0, w, h);

	// matrix update
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// "render space"
	gluPerspective(60, GLdouble(width) / height, 0, 100);
}

void OnRender(void) {

	// clear frame
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// set defult viewmode
	glMatrixMode(GL_MODELVIEW);
	// replaces current matrix width identity matrix
	glLoadIdentity();

	// redraw frame
	gluLookAt(xTranslate, 0, zTranslate, 0, 0, 100, 0, 1, 0);
	{
		glTranslatef(0, 0, 10);
		xRotation += 0.1;
		glRotatef(xRotation, 1, 1, 1);
		glColor3f(0.0f, 0.0f, 1.0f);

		// TODO check if is drawn correctly - CCW
		// draw a piramid
		glBegin(GL_TRIANGLES);

		// Front
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		// Right
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		// Back
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		// Left
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		// Bottom 1
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		// Bottom 2
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glEnd();
	}

	// execute GL commands in finite time
	glFlush();
	// swap buffers
	glutSwapBuffers();
}