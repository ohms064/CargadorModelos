#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include < stdlib.h>
#include < GL/glut.h>
#include < stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "ModeloObj.h"

using namespace std;

#define VELOCIDAD 5;

// Poner aquí el nombre del archivo sin el .obj, es muy importante que el archivo exista
#define NOMBRE_ARCHIVO "link"
//---------------------------------


GLfloat posObjeto = -5.0f;
GLfloat anguloCamaraY = 0.0f;
GLfloat anguloCamaraX = 0.0f;
GLfloat anguloCamaraZ = 0.0f;
GLfloat anguloCamara2Z = 0.0f;

bool gira = true;
int color = 0;
float anguloRotacionObjeto = 0;
float velocidadRotacion = 1;

float miradaAPieY = 0.0f;
float posCamPieX = 0.0f;
float posCamPieY = 0.0f;
float posCamPieZ = 20.0f;

float viewCamPieX = 0;
float viewCamPieY = miradaAPieY;
float viewCamPieZ = 0;

float upCamPieX = 0;
float upCamPieY = 1;
float upCamPieZ = 0;

bool banderaTextura = false;
bool banderaNormal = false;
bool banderaMtl = false;

ModeloObj modelo;

int cargarObjs(){
	modelo = { NOMBRE_ARCHIVO".obj" };
	return modelo.cargaObjeto();
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (height == 0)							// Para que no se presente una division por cero
	{
		height = 1;							// la altura se iguala a 1
	}
	// Calcula el radio de aspecto o proporcion de medidas de la ventana
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 2000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void dibujaReferencia(){
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCube(1);
}
void dibujoPiso(){
	glColor3f(0.3f, 0.3f, 1.0f);
	glScalef(5.0f, 0.2f, 5.0f);
	glutSolidCube(1);
}
void animation(){
	if (gira){
		if (anguloRotacionObjeto<360){
			anguloRotacionObjeto += velocidadRotacion;
		}
		else{
			anguloRotacionObjeto = 0;
		}
	}
	glutPostRedisplay();
}
// función que muestra por pantalla la escena.
void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(posCamPieX, posCamPieY, posCamPieZ, viewCamPieX, viewCamPieY, viewCamPieZ, upCamPieX, upCamPieY, upCamPieZ);
	////////////////////////////////////////////
	// movimiento y posicionamiento de la camara.
	////////////////////////////////////////////
	glPushMatrix();
	// eje horizontal.
	glRotatef(anguloCamaraY, 0.0f, 1.0f, 0.0f);
	// eje vertical.
	glRotatef(anguloCamaraX, 1.0f, 0.0f, 0.0f);
	
	//CUBO
	glPushMatrix();
	switch (color){
	case 1:glColor3f(0.2f, 0.2f, 0.2f); break;
	case 2:glColor3f(1.0f, 1.0f, 1.0f); break;
	default:glColor3f(0.8f, 0.8f, 0.8f); break;
	}
	//dibujaObjeto();
	modelo.dibujaObjeto(banderaTextura, banderaNormal);
	
	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}
void init() {
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);
	
	//CARGAR OBJ
	cargarObjs();
	//CARGAR OBJ
}

// función que permite interactuar con la escena mediante el teclado
void keyboard(unsigned char key, int x, int y){

	int mod = glutGetModifiers();
	if (mod != 0){
		switch (mod)
		{
		case 2://CTRL  
			switch (key) {
			case 1:color = 11; display(); break;
			case 2:color = 12; display(); break;
			case 3:color = 13; display(); break;
			case 4:color = 14; display(); break;
			case 6:color = 15; display(); break;
			}
			break;
		}
	}
	else{
		switch (key) {
		case '+':posCamPieZ--; display(); break;
		case '-':posCamPieZ++; display(); break;
		case '1':
			banderaTextura = !banderaTextura; 
			cout << "Textura: " << banderaTextura << endl;
			display();
			break;
		case '2':
			banderaNormal = !banderaNormal;
			cout << "Normal: " << banderaNormal << endl;
			display(); 
			break;
		/*case '3':
			banderaMtl = !banderaMtl, display();
			cout << "Mtl: " << banderaMtl << endl;
			display();
			break;*/
		case '4':color = 1; display(); break;
		case '5':color = 2; display(); break;
		case '6':color = 3; display(); break;
		case 27:exit(0); break;
		}
	}
}

// función que permite interactuar con la escena mediante el teclado
void specialKeys(int key, int x, int y) {
	switch (key) {
		// ROTAR CAMARA LA DERECHA
	case GLUT_KEY_RIGHT:
		anguloCamaraY += VELOCIDAD;
		display();
		break;
		// ROTAR CAMARA LA IZQUIERDA
	case GLUT_KEY_LEFT:
		anguloCamaraY -= VELOCIDAD;
		display();
		break;
		// ROTAR CAMARA HACIA ARRIBA
	case GLUT_KEY_UP:
		anguloCamaraX += VELOCIDAD;
		display();
		break;
		// ROTAR CAMARA HACIA ABAJO
	case GLUT_KEY_DOWN:
		anguloCamaraX -= VELOCIDAD;
		display();
		break;
	case GLUT_KEY_F1:
		velocidadRotacion += 0.5;
		break;
	case GLUT_KEY_F2:
		velocidadRotacion -= 0.5;
		break;
	}
}

void mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		gira = (gira ? false : true);
	}
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow(NOMBRE_ARCHIVO);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutIdleFunc(animation);
	glutSpecialFunc(specialKeys);
	glutMainLoop();
	return 0;
}