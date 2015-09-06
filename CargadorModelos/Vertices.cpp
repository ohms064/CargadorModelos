#include "Vertices.h"


Vertices::Vertices(){
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

void Vertices::print(){
	printf("\t\tX: %f Y: %f Z %f\n", x, y, z);
}

void Vertices::setAll(int i, int j, int k){
	x = i;
	y = j;
	z = k;
}

void Vertices::setAll(string buffer){
	//Recibe una lista de tokens con los valores de x,y,z y se moviendo sobre la lista.
	size_t pos = buffer.find(" ");
	while (buffer.substr(0, pos).empty()){
		buffer.erase(0, pos + 1);
		pos = buffer.find(" ");
	}
	x = stof(buffer.substr(0, pos));
	buffer.erase(0, pos + 1);
	pos = buffer.find(" ");
	y = stof(buffer.substr(0, pos));
	buffer.erase(0, pos + 1);
	pos = buffer.find(" ");
	z = stof(buffer.substr(0, pos));
	buffer.erase(0, pos + 1);
}