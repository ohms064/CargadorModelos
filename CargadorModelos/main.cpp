#include < stdlib.h>
#include < GL/glut.h>
#include < stdio.h>
#include "Vertices.h"
#include "Cara.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define VELOCIDAD 2;
#define NUVE 30
#define NUCA 50

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

Vertices vertices[NUVE];
Cara caras[NUCA];

int cargaObjeto(){
	char linea[128];
	ifstream fe("link.obj");
	int contador_lineas = 0;
	int contador_punto = 0;//Es el que lleva el conteo del n�mero de punto que se va a dibujar
	int contador_cara = 0;
	while (fe.getline(linea, 128) && strcmp(linea, "")){
		printf("LINEA NO %d:\n\t%s\n", contador_lineas++, linea);	//printf("%s\n", linea);
		char delimitadores[] = " ";
		char*  aspe;
		char* contexto = NULL;
		aspe = strtok_s(linea, delimitadores, &contexto); //aspe = Arreglo de Separaciones Por Espacios

		int contador_separaciones = 0;
		if (!strcmp(aspe, "#")){
			//printf("COMENTARIO: ");
			aspe = strtok_s(NULL, delimitadores, &contexto);
		}
		else if (!strcmp(aspe, "mtllib") || !strcmp(aspe, "usemtl")){
			//printf("MATERIALES: ");
			aspe = strtok_s(NULL, delimitadores, &contexto);
		}
		else if (!strcmp(aspe, "v")){
			//Aqu� se guardan las variables x,y,z del objeto vertices[]
			vertices[contador_punto].setAll(aspe, delimitadores, contexto);// Cada vez que se llama a aspe retorna el token al que este apuntando y cambio su apuntador al siguiente token
			vertices[contador_punto].print();
			contador_punto++;
		}
		else if (!strcmp(aspe, "vt")){
			//printf("TEXTURAS: ");
			aspe = strtok_s(NULL, delimitadores, &contexto);
		}
		else if (!strcmp(aspe, "vn")){
			//printf("NORMALES: ");
			aspe = strtok_s(NULL, delimitadores, &contexto);
		}
		else if (!strcmp(aspe, "f")){
			//CARAS
			aspe = strtok_s(NULL, delimitadores, &contexto);
			while (aspe != NULL){
				caras[contador_cara].setCara(aspe);
				aspe = strtok_s(NULL, delimitadores, &contexto);
			}
			contador_cara++;
		}
		else{
			//printf("OTROS     : ");
			aspe = strtok_s(NULL, delimitadores, &contexto);
		}
		printf("\n");
	}
	return 0;
}
void dibujaObjeto(){
	//Es llamado dentro de display
	int contadorCARAS = 0;
	int contadorVERTICES = 0;
	for (contadorCARAS = 0; contadorCARAS < NUCA; contadorCARAS++){
		glBegin(GL_POLYGON);
		//Se empieza a dibujar los vertices con los datos guarado en la cola de vertices obtenida en cargaObjeto
		for (contadorVERTICES = 0; contadorVERTICES < caras[contadorCARAS].vertice.size(); contadorVERTICES++){
			glVertex3f(vertices[caras[contadorCARAS].vertice.front()].x, vertices[caras[contadorCARAS].vertice.front()].y, vertices[caras[contadorCARAS].vertice.front()].z);
			caras[contadorCARAS].popVertice();
		}
		glEnd();
	}
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
// funci�n que muestra por pantalla la escena.
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
	//PISO
	glPushMatrix();
	glTranslatef(0.0f, -2.0f, 0.0f);
	dibujoPiso();
	glPopMatrix();
	//REFERENCIA IZQUIERDA
	glPushMatrix();
	glTranslatef(-5.0f, 0.0f, 0.0f);
	dibujaReferencia();
	glPopMatrix();
	//REFERENCIA DERECHA
	glPushMatrix();
	glTranslatef(5.0f, 0.0f, 0.0f);
	dibujaReferencia();
	glPopMatrix();
	//CUBO
	glPushMatrix();
	switch (color){
	case 1:glColor3f(0.3f, 0.3f, 1.0f); break;
	case 2:glColor3f(0.3f, 1.0f, 0.3f); break;
	case 3:glColor3f(1.0f, 0.3f, 0.3f); break;
	case 4:glColor3f(1.0f, 1.0f, 0.3f); break;
	case 5:glColor3f(1.0f, 0.3f, 1.0f); break;

	case 11:glColor3f(0.3f, 0.3f, 0.3f); break;
	case 12:glColor3f(0.4f, 0.4f, 0.4f); break;
	case 13:glColor3f(0.5f, 0.5f, 0.5f); break;
	case 14:glColor3f(0.6f, 0.6f, 0.6f); break;
	case 15:glColor3f(0.7f, 0.7f, 0.7f); break;
	default:glColor3f(0.8f, 0.8f, 0.8f); break;
	}
	dibujaObjeto();
	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}
void init() {
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	//CARGAR OBJ
	cargaObjeto();
	//CARGAR OBJ
}

// funci�n que permite interactuar con la escena mediante el teclado
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
		case '1':color = 1; display(); break;
		case '2':color = 2; display(); break;
		case '3':color = 3; display(); break;
		case '4':color = 4; display(); break;
		case '5':color = 5; display(); break;
		case 27:exit(0); break;
		}
	}
}

// funci�n que permite interactuar con la escena mediante el teclado
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
	glutCreateWindow("Cubo");
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