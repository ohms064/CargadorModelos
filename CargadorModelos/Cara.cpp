#include "Cara.h"
/*
	Se trabaja con una cola circular, para que en todo momento tengamos los n vertices, por eso se tiene las propias funciones pop por que 
	se deben poner de vuelta los valores que les hagamos pop.
*/
Cara::Cara(){
}

void Cara::setCara(char* aspe){
	//El formato de las caras es: v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ....
	//Verifica como recibe el formato, ya sea v1, v1/vt1, v1/vt1/vn1 o v1//vn1
	char* contexto = NULL;
	printf("aspe: %s ", aspe);
	if (strstr(aspe, "//")){ //Si solo contiene el vertice y la normal
		char delimitador[] = "//";
		char* c = strtok_s(aspe, delimitador, &contexto);
		vertice.push(atoi(c) - 1);
		c = strtok_s(NULL, delimitador, &contexto);
		if (c != NULL)
			normal.push(atoi(c));
	}
	else if (strstr(aspe, "/")){//Por lo menos tiene la textura
		char delimitador[] = "/";
		char* c = strtok_s(aspe, delimitador, &contexto);
		printf("C: %c", c);
		vertice.push(atoi(c) - 1);
		c = strtok_s(NULL, delimitador, &contexto);
		if (c != NULL){//Si tambien contiene la textura
			textura.push(atoi(c));
			c = strtok_s(NULL, delimitador, &contexto);
			if (c != NULL){//Si también contiene la normal
				normal.push(atoi(c));
			}
		}
	}
	else{
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

void Cara::printTextura(){
	for (int i = 0; i < textura.size(); i++){
		printf("%d ", textura.front());
		popTextura();
	}
	printf("\n");
}

void Cara::printNormal(){
	for (int i = 0; i < normal.size(); i++){
		printf("%d ", normal.front());
		popNormal();
	}
	printf("\n");
}