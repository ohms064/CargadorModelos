#pragma once
#include<string>
#include<vector>
using namespace std;
class Material
{
public:
	string mapKd, mapKa, mapKs; //Guarda el valor de la imagen que se usará
	float Ns = 0, Ni = 0, d; //Los valores respectivos
	float Ka[4], Kd[4], Ks[4];
	int illum;

	Material();
	~Material();
	//Ka, Kd, Ks como son arreglos tienen su propio método para recibir el string y guardarlo donde debe
	void setKa(string buffer);
	void setKd(string buffer);
	void setKs(string buffer);

};

