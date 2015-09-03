#include "Cara.h"
Cara::Cara(){
}

void Cara::getCara(char* aspe){
	//El formato de las caras es: v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ....
	char* contexto = NULL;
	if (strstr(aspe, "//")){ //Si solo contiene el vertice y la normal
		char delimitador[] = "//";
		char* c = strtok_s(aspe, delimitador, &contexto);
		vertice.push(atoi(c));
		c = strtok_s(NULL, delimitador, &contexto);
		if (c != NULL)
			normal.push(atoi(c));
	}
	else{
		char delimitador[] = "/";
		char* c = strtok_s(aspe, delimitador, &contexto);
		vertice.push(atoi(c));
		c = strtok_s(NULL, delimitador, &contexto);
		if (c != NULL){//Si tambien contiene la textura
			textura.push(atoi(c));
			c = strtok_s(NULL, delimitador, &contexto);
			if (c != NULL){//Si también contiene la normal
				normal.push(atoi(c));
				c = strtok_s(NULL, delimitador, &contexto);
			}
		}
	}
}

int Cara::popVertice(){
	vertice.pop();
	vertice.push(vertice.front());
	return vertice.front();
}

int Cara::popTextura(){
	textura.pop();
	textura.push(textura.front());
	return textura.front();
}

int Cara::popNormal(){
	normal.pop();
	normal.push(normal.front());
	return normal.front();
}