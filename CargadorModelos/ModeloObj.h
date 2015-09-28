#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string>
#include <fstream>
#include < GL/glut.h>
#include "texture.h"
#include "Vertice.h"
#include "Texturas.h"
#include "Normal.h"
#include "Grupo.h"
#include "Cara.h"

using namespace std;
class ModeloObj
{
public:
	Vertice* vertices; //Guardamos los valores x,y,z de cada vertice (v x y z)
	Texturas* texturas;  //Guardamos los valores x,y de cada vertice (vt x y)
	Normal* normales;  //Guardamos los valores x,y de cada vertice (vn x y z)
	Cara* caras; //Guardamos los valores de vertices, textura y normal de cada cara, textura y normal son opcionales (f v/vt/vn)
	Grupo* grupos;

	CTexture tCubo;

	int numVertices = 0;
	int numCaras = 0;
	int numNormales = 0;
	int numTexturas = 0;
	int numGrupos = 0;
	int numMtl = 0;
	string fileName = "";
	bool banderaFile = true;

	ModeloObj();
	ModeloObj(string fileName);
	~ModeloObj();

	int ModeloObj::cargaObjeto();
	void ModeloObj::dibujaObjeto(bool banderaTextura, bool banderaNormal);
};

