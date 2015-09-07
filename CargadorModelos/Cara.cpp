#include "Cara.h"
/*
	Se trabaja con una cola circular, para que en todo momento tengamos los n vertices, por eso se tiene las propias funciones pop por que 
	se deben poner de vuelta los valores que les hagamos pop.
*/
Cara::Cara(){
}

void Cara::setCara(const string input){
	//El formato de las caras es: v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ....
	string item = input;
	size_t pos = item.find("/");
	if (pos == string::npos)
		vertice.push(stoi(item) - 1);
	else{
		int temp = stoi(item.substr(0, pos)) - 1;
		cout << "temp: "<< temp;
		vertice.push(temp);
		item.erase(0, pos + 1);
		pos = item.find("/");
		if (pos != string::npos){// Si no encuentra otra "/" entonces termina
			std::string temp = item.substr(0, pos);
			if (!temp.empty()) //Checamos que no esté vacío por si llegara a ser que fuera v1//vn1
				textura.push(stoi(temp));
			item.erase(0, pos + 1);
			pos = item.find("/");
			if (pos != string::npos){//Checamos si exite vn
				normal.push(stoi(item.substr(0, pos)));
				item.erase(0, pos + 1);
			}
		}
	}
}

//Esto se maneja como una cola circular, el HEAD estaría apuntando al principio, cuando le haceoms pop lo reingresamos a la cola.
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