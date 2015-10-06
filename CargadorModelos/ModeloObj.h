#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string>
#include <fstream>
#include "texture.h"
#include "Vertice.h"
#include "Texturas.h"
#include "Normal.h"
#include "Grupo.h"
#include "Cara.h"
#include "Material.h"
#include <map>

using namespace std;
class ModeloObj
{
public:
	Vertice* vertices; //Guardamos los valores x,y,z de cada vertice (v x y z)
	Texturas* texturas;  //Guardamos los valores x,y de cada vertice (vt x y)
	Normal* normales;  //Guardamos los valores x,y de cada vertice (vn x y z)
	Cara* caras; //Guardamos los valores de vertices, textura y normal de cada cara, textura y normal son opcionales (f v/vt/vn)
	map<string, Material> materiales;
	Grupo* grupos;
	Grupo* objetos;

	CTexture tCubo;

	/* diego 30/09/15 */
	float pX = 0; //Posición en x
	float pY = 0; //Posición en y
	float pZ = 0; //Posición en z

	float rX = 0; //Rotación en X
	float rY = 0; //Rotación en Y
	float rZ = 0; //Rotación en Z

	float sX = 1; //Escalamiento en X
	float sY = 1; //Escalamiento en Y
	float sZ = 1; //Escalamiento en Z
	/* diego 30/09/15 */

	int numVertices = 0; // v
	int numCaras = 0; // f
	int numNormales = 0; // vn
	int numTexturas = 0; // vt
	int numGrupos = 0; // g
	int numMtl = 0; // usemtl
	int numObjetos = 0; // o
	string fileName = "";
	bool banderaFile = true;
	bool banderaDibujo = true;

	ModeloObj();
	ModeloObj(string fileName);
	~ModeloObj();

	int ModeloObj::cargaObjeto();
	void ModeloObj::cargaMaterial(string matName);
};

