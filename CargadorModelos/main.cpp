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
#include <map>

using namespace std;
#define VELOCIDAD 5;
// Poner aquí el nombre del archivo sin el .obj, es muy importante que el archivo exista
#define NOMBRE_ARCHIVO "archivo"
//---------------------------------
map<string, string> modelos;
map<string, ModeloObj> escenas;
map<string, ModeloObj> objetos;
map<string, ModeloObj> personajes;

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

/*
void cargarObjs(string nombre_archivo){
	modelo = { nombre_archivo };
	modelo.cargaObjeto();
}
*/
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
		glPushMatrix();
			switch (color){
			case 1:glColor3f(0.2f, 0.2f, 0.2f); break;
			case 2:glColor3f(1.0f, 1.0f, 1.0f); break;
			default:glColor3f(0.8f, 0.8f, 0.8f); break;
			}
			//dibujaObjeto();

			map<string, ModeloObj>::const_iterator itr;
			//Mostrar escenas guardadas
			for (itr = escenas.begin(); itr != escenas.end(); ++itr){
				//cout << "ESCENA: Key: " << (*itr).first << " Value: " << (*itr).second.fileName << endl;
			}
			//Mostrar objetos guardados
			for (itr = objetos.begin(); itr != objetos.end(); ++itr){
				//cout << "OBJETO: Key: " << (*itr).first << " Value: " << (*itr).second.fileName << endl;
			}
			//Mostrar objetos guardados
			for (itr = personajes.begin(); itr != personajes.end(); ++itr){
				//cout << "PERSONAJE: Key: " << (*itr).first << " Value: " << (*itr).second.fileName << endl;
			}

			for (itr = escenas.begin(); itr != escenas.end(); ++itr){
				glPushMatrix();
				glTranslatef((*itr).second.pX, (*itr).second.pY, (*itr).second.pZ);
				glRotatef((*itr).second.rX, 1, 0, 0);
				glRotatef((*itr).second.rY, 0, 1, 0);
				glRotatef((*itr).second.rZ, 0, 0, 1);
				glScalef((*itr).second.sX, (*itr).second.sY, (*itr).second.sZ);
				escenas[(*itr).first].dibujaObjeto(banderaTextura, banderaNormal);
				glPopMatrix();
			}
			for (itr = objetos.begin(); itr != objetos.end(); ++itr){
				glPushMatrix();
				glTranslatef((*itr).second.pX, (*itr).second.pY, (*itr).second.pZ);
				glRotatef((*itr).second.rX, 1, 0, 0);
				glRotatef((*itr).second.rY, 0, 1, 0);
				glRotatef((*itr).second.rZ, 0, 0, 1);
				glScalef((*itr).second.sX, (*itr).second.sY, (*itr).second.sZ);
				objetos[(*itr).first].dibujaObjeto(banderaTextura, banderaNormal);
				glPopMatrix();
			}
			for (itr = personajes.begin(); itr != personajes.end(); ++itr){
				glPushMatrix();
				glTranslatef((*itr).second.pX, (*itr).second.pY, (*itr).second.pZ);
				glRotatef((*itr).second.rX, 1, 0, 0);
				glRotatef((*itr).second.rY, 0, 1, 0);
				glRotatef((*itr).second.rZ, 0, 0, 1);
				glScalef((*itr).second.sX, (*itr).second.sY, (*itr).second.sZ);
				personajes[(*itr).first].dibujaObjeto(banderaTextura, banderaNormal);
				glPopMatrix();
			}
		glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}
void init() {
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
//WRL
	string linea;
	ifstream fe(NOMBRE_ARCHIVO".wrl");


	size_t espacio;
	string id;
	
	while (!fe.eof()){
		std::getline(fe, linea);	
		if (!linea.empty()){
			if (linea[0] == '<' && linea[linea.length() - 1] == '>'){ //si es una instruccion <instruccion > 
				linea = linea.substr(1, linea.length() - 2);
				espacio = linea.find(" ");
				id = linea.substr(0, espacio); //Aquí tenemos el inicio de cada linea que nos indicará que hacer
				if (id == "modelo"){
					string nombre_modelo;
					string ruta_modelo;

					nombre_modelo = linea.substr(linea.find(" ") + 1);
					ruta_modelo = nombre_modelo.substr(nombre_modelo.find(" ") + 1);
					cout << "Obteniendo modelo " << nombre_modelo << endl;
					
					//Creo es innecesario esta parte, sólo falta no sumarle 1 en las instrucciones anteriores
					nombre_modelo = nombre_modelo.substr(0, nombre_modelo.find(" "));
					ruta_modelo = ruta_modelo.substr(0, ruta_modelo.find(" "));

					modelos[nombre_modelo] = ruta_modelo;
				}
				else if (id == "escena" || id == "objeto" || id == "personaje"){
					string nombre_modelo;
					string nombre_instancia;
					
					nombre_modelo = linea.substr(linea.find(" ") + 1);
					nombre_instancia = nombre_modelo.substr(nombre_modelo.find(" ") + 1);

					cout << "Creando instancia del modelo: " << nombre_modelo << " " << nombre_instancia << endl;

					//Creo es innecesario esta parte, sólo falta no sumarle 1 en las instrucciones anteriores
					nombre_modelo = nombre_modelo.substr(0, nombre_modelo.find(" "));
					nombre_instancia = nombre_instancia.substr(0, nombre_instancia.find(" "));

					ModeloObj modelo;

					if (modelos[nombre_modelo]!=""){
						modelo = { modelos[nombre_modelo] }; //Construimos el modelo
						if (id == "escena"){
							escenas[nombre_instancia] = modelo;
							escenas[nombre_instancia].cargaObjeto();
						}
						else if (id == "objeto"){
							objetos[nombre_instancia] = modelo;
							objetos[nombre_instancia].cargaObjeto();
						}
						else if (id == "personaje"){
							personajes[nombre_instancia] = modelo;
							personajes[nombre_instancia].cargaObjeto();
						}
					}
					else{
						cerr << "No existe ese tipo de modelo" << endl; //Error
					}
				}
				else if (id == "posicion" || id == "rotacion" || id == "escalamiento"){
					cout << "Estableciendo transformaciones: " << id << endl;
					string nombre_instancia;
					string p1, p2, p3; //Parámetro 1, parámetro 2, parámetro 3, 
					//faltaría comprobar que existieran todos los parámetros
					nombre_instancia = linea.substr(linea.find(" ") + 1);
					p1 = nombre_instancia.substr(nombre_instancia.find(" ") + 1);
					p2 = p1.substr(p1.find(" ") + 1);
					p3 = p2.substr(p2.find(" ") + 1);

					nombre_instancia = nombre_instancia.substr(0, nombre_instancia.find(" "));
					p1 = p1.substr(0, p1.find(" "));
					p2 = p2.substr(0, p2.find(" "));
					p3 = p3.substr(0, p3.find(" "));

					std::string::size_type sz;
					float f1, f2, f3;
					f1 = stof(p1, &sz);
					f2 = stof(p2, &sz);
					f3 = stof(p3, &sz);

					//El objeto ModeloObj no puede guardar los valores de rotación porque entonces sólo se podría
					//crear una instancia de cada modelo o que todos los modelos compartan transformaciones
					if (escenas.find(nombre_instancia) != escenas.end()){
						cout << "2 entré aquí por: " << linea << endl;
						if(id=="posicion"){
							escenas[nombre_instancia].pX = f1;
							escenas[nombre_instancia].pY = f2;
							escenas[nombre_instancia].pZ = f3;
						}
						else if (id == "rotacion"){
							escenas[nombre_instancia].rX = f1;
							escenas[nombre_instancia].rY = f2;
							escenas[nombre_instancia].rZ = f3;
						}
						else if (id == "escalamiento"){
							escenas[nombre_instancia].sX = f1;
							escenas[nombre_instancia].sY = f2;
							escenas[nombre_instancia].sZ = f3;
						}
					}
					else if (objetos.find(nombre_instancia) != objetos.end()){
						if (id == "posicion"){
							objetos[nombre_instancia].pX = f1;
							objetos[nombre_instancia].pY = f2;
							objetos[nombre_instancia].pZ = f3;
						}
						else if (id == "rotacion"){
							objetos[nombre_instancia].rX = f1;
							objetos[nombre_instancia].rY = f2;
							objetos[nombre_instancia].rZ = f3;
						}
						else if (id == "escalamiento"){
							objetos[nombre_instancia].sX = f1;
							objetos[nombre_instancia].sY = f2;
							objetos[nombre_instancia].sZ = f3;
						}
					}
					else if (objetos.find(nombre_instancia) != objetos.end()){
						if (id == "posicion"){
							personajes[nombre_instancia].pX = f1;
							personajes[nombre_instancia].pY = f2;
							personajes[nombre_instancia].pZ = f3;
						}
						else if (id == "rotacion"){
							personajes[nombre_instancia].rX = f1;
							personajes[nombre_instancia].rY = f2;
							personajes[nombre_instancia].rZ = f3;
						}
						else if (id == "escalamiento"){
							personajes[nombre_instancia].sX = f1;
							personajes[nombre_instancia].sY = f2;
							personajes[nombre_instancia].sZ = f3;
						}
					}
					else{
						cerr << "No hay instancia con ese nombre, de ningún tipo" << endl;
					}
				}
			}
			else if (linea[0]=='#'){
				//cout << "COMENTARIO: " << linea << endl;
			}
		}
	}
//WRL
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