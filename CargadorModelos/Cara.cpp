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
			if (c != NULL){//Si tambi�n contiene la normal
				normal.push(atoi(c));
			}
		}
	}
	else{
		printf("Ve: %d ", atoi(aspe) - 1);
		vertice.push(atoi(aspe) - 1);
	}

}

void Cara::popVertice(){
	vertice.push(vertice.front());
	vertice.pop();
}

void Cara::popTextura(){
	textura.push(textura.front());
	textura.pop();
}

void Cara::popNormal(){
	normal.push(normal.front());
	normal.pop();
}

void Cara::printVertice(){
	for (int i = 0; i < vertice.size(); i++){
		printf("%d ", vertice.front());
		popVertice();
	}
	printf("\n");
}