#include "Texturas.h"

//En esta clase guardamos los valores de x,y,z de un vertice.

Texturas::Texturas(){
	x = 0.0f;
	y = 0.0f;
}

void Texturas::print(){
	printf("\t\tX: %f Y: %f Z %f\n", x, y);
}

void Texturas::setAll(int i, int j){
	x = i;
	y = j;
}

void Texturas::setAll(string buffer){
	//Recibe un string con los valores de x,y,z y se va moviendo sobre el string obteniendo los tokens.
	size_t pos = buffer.find(" ");
	while (buffer.substr(0, pos).empty()){// Por si hubiera más de un espacio entre el identificador y "x".
		buffer.erase(0, pos + 1);
		pos = buffer.find(" ");
	}
	x = stof(buffer.substr(0, pos));
	buffer.erase(0, pos + 1);
	pos = buffer.find(" ");
	y = stof(buffer.substr(0, pos));
	buffer.erase(0, pos + 1);
	pos = buffer.find(" ");
}