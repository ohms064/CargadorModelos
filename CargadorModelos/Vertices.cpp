#include "Vertices.h"
#include <iostream>


Vertices::Vertices(){
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

void Vertices::print(){
	printf("X: %f Y: %f Z %f\n", x, y, z);
}

void Vertices::setAll(int i, int j, int k){
	x = i;
	y = j;
	z = k;
}

void Vertices::setAll(char* buffer, char delimitadores[], char* contexto){
	//Recibe una lista de tokens con los valores de x,y,z y se moviendo sobre la lista.
	buffer = strtok_s(NULL, delimitadores, &contexto);
	x = atof(buffer);
	buffer = strtok_s(NULL, delimitadores, &contexto);
	y = atof(buffer);
	buffer = strtok_s(NULL, delimitadores, &contexto);
	z = atof(buffer);
}