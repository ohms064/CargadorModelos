#include < GL/glut.h>
#include <map>
#include "ModeloObj.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

#pragma once
class ModelosWorld
{
public:

	map<string, string> modelos;
	map<string, ModeloObj> escenas;
	map<string, ModeloObj> objetos;
	map<string, ModeloObj> personajes;

	ModelosWorld();
	ModelosWorld(string nombreWorld);
	~ModelosWorld();
	void dibujaWorld(bool banderaTextura, bool banderaNormal);
};

