#pragma once
#include<string>
#include<vector>
using namespace std;
class Material
{
public:
	string mapKd; //Guarda el valor de la imagen que se usará
	float Ns, Ni, d; //Los valores respectivos
	float Ka[3], Kd[3], Ks[3];
	int illum;

	Material();
	~Material();
	//Ka, Kd, Ks como son arreglos tienen su propio método para recibir el string y guardarlo donde debe
	void setKa(string buffer);
	void setKd(string buffer);
	void setKs(string buffer);

};

