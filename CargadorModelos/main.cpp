#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#define _USE_MATH_DEFINES
#include < stdlib.h>
#include < GL/glut.h>
#include < stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "ModeloObj.h"
#include "ModelosWorld.h"
#include <map>


using namespace std;
#define VELOCIDAD 5;
// Poner aquí el nombre del archivo sin el .obj, es muy importante que el archivo exista
#define NOMBRE_ARCHIVO "archivo"
//---------------------------------
ModelosWorld mundo;

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

bool banderaTextura = true;
bool banderaNormal = true;
bool banderaMtl = true;


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


void dibujaObjeto(ModeloObj objeto){
	/*
	Recibe un ModeloObj y lo dibujará en escena
	*/
	int iterCaras = 0;
	int iterVertices = 0;
	int iterGrupos = 0;
	char* temp; //Utilicé un char* porque CTexture recibe valores de este tipo
	string id;
	for (iterCaras = 0; iterCaras < objeto.numCaras; iterCaras++){
		if (banderaTextura && iterCaras == objeto.grupos[iterGrupos].inicio && iterGrupos < objeto.numGrupos){
			id = objeto.materiales[objeto.grupos[iterGrupos].tex].mapKd; //Obtenemos la textura
			temp = new char[id.size()]; //Obtenemos el tamaño del nombre de la textura
			strcpy(temp, id.c_str()); //Debemos copiar el c_str porque c_str retorna un apuntador
			size_t pos = id.find(".");
			if (id.substr(pos + 1, id.length()) == "tga") {
				objeto.tCubo.LoadTGA(temp);
			}
			else if (id.substr(pos + 1, id.length()) == "bmp") {
				objeto.tCubo.LoadBMP(temp);
			}
			objeto.tCubo.BuildGLTexture();
			objeto.tCubo.ReleaseImage(); 
			glMaterialfv(GL_FRONT, GL_AMBIENT, objeto.materiales[objeto.grupos[iterGrupos].tex].Ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto.materiales[objeto.grupos[iterGrupos].tex].Kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, objeto.materiales[objeto.grupos[iterGrupos].tex].Ks);
			//glMaterialfv(GL_FRONT, GL_SHININESS, objeto.materiales[objeto.grupos[iterGrupos].tex].Ns);
			iterGrupos++;
		}
		glBegin(GL_POLYGON);

		//Se empieza a dibujar las caras con los datos guarado en el arreglo "vertices" obtenida en cargaObjeto
		for (iterVertices = 0; iterVertices < objeto.caras[iterCaras].vertice.size(); iterVertices++){
			if (banderaNormal && !objeto.caras[iterCaras].normal.empty()){
				glNormal3f(objeto.normales[objeto.caras[iterCaras].normal.front()].x, objeto.normales[objeto.caras[iterCaras].normal.front()].y, objeto.normales[objeto.caras[iterCaras].normal.front()].z);
				objeto.caras[iterCaras].popNormal();
			}
			if (banderaTextura && !objeto.caras[iterCaras].textura.empty()){
				glTexCoord2f(objeto.texturas[objeto.caras[iterCaras].textura.front() - 1].x, objeto.texturas[objeto.caras[iterCaras].textura.front() - 1].y);
				objeto.caras[iterCaras].popTextura();
			}
			glVertex3f(objeto.vertices[objeto.caras[iterCaras].vertice.front()].x, objeto.vertices[objeto.caras[iterCaras].vertice.front()].y, objeto.vertices[objeto.caras[iterCaras].vertice.front()].z);
			objeto.caras[iterCaras].popVertice();
		}
		glEnd();
	}
}

void dibujaWorld(){
	/*
	Aquí se manda a llamar al objeto mundo para dibujarse.
	Obtiene los objetos para dibujarlos posteriormente con la función dibujaObjeto.
	*/
	map<string, ModeloObj>::const_iterator itr;

	for (itr = mundo.escenas.begin(); itr != mundo.escenas.end(); ++itr){//Se transforman y dibuan escenas.
		glPushMatrix();
		glTranslatef((*itr).second.pX, (*itr).second.pY, (*itr).second.pZ);
		glRotatef((*itr).second.rX, 1, 0, 0);
		glRotatef((*itr).second.rY, 0, 1, 0);
		glRotatef((*itr).second.rZ, 0, 0, 1);
		glScalef((*itr).second.sX, (*itr).second.sY, (*itr).second.sZ);
		dibujaObjeto(mundo.escenas[(*itr).first]);
		glPopMatrix();
	}
	for (itr = mundo.objetos.begin(); itr != mundo.objetos.end(); ++itr){//Se transforman y dibujan los objetos.
		glPushMatrix();
		glTranslatef((*itr).second.pX, (*itr).second.pY, (*itr).second.pZ);
		glRotatef((*itr).second.rX * 180 / M_PI, 1, 0, 0);
		glRotatef((*itr).second.rY * 180 / M_PI, 0, 1, 0);
		glRotatef((*itr).second.rZ * 180 / M_PI, 0, 0, 1);
		glScalef((*itr).second.sX, (*itr).second.sY, (*itr).second.sZ);
		dibujaObjeto(mundo.objetos[(*itr).first]);
		glPopMatrix();
	}
	for (itr = mundo.personajes.begin(); itr != mundo.personajes.end(); ++itr){//Se transforman y dibujan los personajes.
		glPushMatrix();
		glTranslatef((*itr).second.pX, (*itr).second.pY, (*itr).second.pZ);
		glRotatef((*itr).second.rX, 1, 0, 0);
		glRotatef((*itr).second.rY, 0, 1, 0);
		glRotatef((*itr).second.rZ, 0, 0, 1);
		glScalef((*itr).second.sX, (*itr).second.sY, (*itr).second.sZ);
		dibujaObjeto(mundo.personajes[(*itr).first]);
		glPopMatrix();
	}
	glPopMatrix();
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
		glPushMatrix();
			switch (color){
			case 1:glColor3f(0.2f, 0.2f, 0.2f); break;
			case 2:glColor3f(1.0f, 1.0f, 1.0f); break;
			default:glColor3f(0.8f, 0.8f, 0.8f); break;
			}
			dibujaWorld();
			
	glPopMatrix();
	glutSwapBuffers();
}
void init() {
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	mundo = { NOMBRE_ARCHIVO".wrl" };
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
		/*case '3': //Todavía no se usa
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

