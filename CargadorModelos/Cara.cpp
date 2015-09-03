#include "Cara.h"
Cara::Cara(){
}

void Cara::setCara(char* aspe){
	//El formato de las caras es: v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ....
	
	char* contexto = NULL;
	if (strstr(aspe, "//")){ //Si solo contiene el vertice y la normal
		char delimitador[] = "//";
		char* c = strtok_s(aspe, delimitador, &contexto);
		vertice.push(atoi(c) - 1);
		c = strtok_s(NULL, delimitador, &contexto);
		if (c != NULL)
			normal.push(atoi(c));
	}
	else if (strstr(aspe, "/")){
		char delimitador[] = "/";
		char* c = strtok_s(aspe, delimitador, &contexto);
		vertice.push(atoi(c) - 1);
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
	else{
		printf("Vertice: %d ", atoi(aspe) - 1);
		vertice.push(atoi(aspe) - 1);
	}
}

void Cara::popVertice(){
	vertice.pop();
	vertice.push(vertice.front());
	verticeFront = vertice.front();
	//printf("%d", vertice.front());
}

void Cara::popTextura(){
	textura.pop();
	textura.push(textura.front());
	texturaFront = textura.front();
}

void Cara::popNormal(){
	normal.pop();
	normal.push(normal.front());
	normalFront = normal.front();
}

void Cara::printVertice(){
	popVertice();
	printf("Caras: %d,", verticeFront);
	popVertice();
	printf("%d,", verticeFront);
	popVertice();
	printf("%d,", verticeFront);
	popVertice();
	printf("%d\n", verticeFront);
}