#ifndef _MAIN_H
#define _MAIN_H

#include <windows.h>		// Archivo de cabecera para Windows
#include <math.h>			// Archivo de cabecera para Funciones Matem�ticas
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdlib.h>			// Header File For Standard Library
#include <fstream>
#include <vector>
#include <crtdbg.h>
#include "GL/gl.h"				// Archivo de cabecera para la libreria OpenGL32
#include "GL/glu.h"			// Archivo de cabecera para la libreria GLu32
#include "GL/glaux.h"			// Archivo de cabecera para la libreria Glaux
#include "GL/glext.h"			// Archivo de cabecera para la libreria Glext
#include "Vector.h"

#define GL_CLAMP_TO_EDGE	0x812F	//Usado para skybox

int  ManejaTeclado();

struct paramObj
{
	CVector PosicionObj;	//La posici�n (x,y,z) del objeto
	CVector PosicionObjAnt;	//La posici�n anterior (x,y,z) del objeto
	CVector Direccion;		//La direcci�n en que se dirige el objeto en forma de vector=(x,y,z)
	CVector DireccionCam;   //La direcci�n que define la posici�n de la c�mara respecto al personaje
	CVector PosicionCam;    //La posici�n de la c�mara que sigue al objeto
	CVector ObjetivoCam;	//El punto (x,y,z) que est� viendo la c�mara; en este caso al objeto

	float VelocidadObj;		//La velocidad a la que se mueve el objeto
	float DistanciaCam;		//La distancia que la c�mara est� separada del objeto
	float AngDir;			//Se usa para llevar control del angulo para el c�lculo del vector de direcci�n
	float AngDirCam;		//Se usa para llevar control del angulo para el c�lculo de posici�n de la c�mara
	float AngObj;			//Se usa para llevar control del �ngulo de rotaci�n para el modelo del objeto

	float CamaraPosAlt;		//Se usa para definir y cambiar si es necesario la altura de la c�mara
	float CamaraObjAlt;		//Se usa para definir y cambiar si es necesario la altura del objetivo de la c�mara

	float escalaX;
	float escalaY;
	float escalaZ;

	int   dir;
	int   contAuxAnim;

	bool visible;
	bool caminando;
	bool saltando;
	bool kick;

};

struct paramCam
{
	CVector DireccionCam;   //La direcci�n que define la posici�n de la c�mara respecto al personaje
	CVector PosicionCam;    //La posici�n de la c�mara que sigue al objeto
	CVector ObjetivoCam;	//El punto (x,y,z) que est� viendo la c�mara; en este caso al objeto

	float DistanciaCam;		//La distancia que la c�mara est� separada del objeto
	float deltaAngDirCam;	//Se usa para llevar control del angulo para el c�lculo de posici�n de la c�mara
	float AngDirCam;		//Se usa para llevar control del angulo para el c�lculo de posici�n de la c�mara

	float CamaraPosAlt;		//Se usa para definir y cambiar si es necesario la altura de la c�mara
	float CamaraObjAlt;		//Se usa para definir y cambiar si es necesario la altura del objetivo de la c�mara

	float VariacionCam;
	float VariacionDist;

	float FactorCam;

	float VariacionDespDist;
	float VariacionDespCam;

};

struct FRAME
{
	float Angt1;
	float Angt2;
	float Angc1;
	float Angc2;
	float Angbi1;
	float Angbi2;
	float Angbib;
	float Angbd1;
	float Angbd2;
	float Angbdb;
	float Angpizq;
	float Angpder;
	float Angpi;
	float Angpd;

	float Xtor;
	float Ytor;
	float Ztor;

	float incAngt1;
	float incAngt2;
	float incAngc1;
	float incAngc2;
	float incAngbi1;
	float incAngbi2;
	float incAngbib;
	float incAngbd1;
	float incAngbd2;
	float incAngbdb;
	float incAngpizq;
	float incAngpder;
	float incAngpi;
	float incAngpd;

	float incXtor;
	float incYtor;
	float incZtor;

};

struct vertice
{
	CVector vert;
	float s;
	float t;
};

struct plano
{
	int numVert;
	CVector color;
	CVector normal;
	vertice *datVert;
};

struct objeto
{
	int numPlanos;
	int bandText;
	int idText;
	int bandIlum;
	plano *datPlano;
};

struct modelo
{
	int numObjetos;
	objeto *datObj;
};

//Version 2
struct vertice2
{
	CVector vert;
	float s;
	float t;
};

struct plano2
{
	int numVert;
	CVector color;
	CVector normal;

	int *listaIdVert;
	vertice2 *datVert;
};

struct objeto2
{
	int numPlanos;
	int bandText;
	int idText;
	int bandIlum;
	int numVert;

	CVector *vert;
	plano2 *datPlano;
};

struct modelo2
{
	int numObjetos;
	objeto2 *datObj;
};

#endif 