#include "Material.h"


Material::Material(){
	/*Opengl recibe estos valores como RGBA y por default como (0,0,0,1) por eso se inicializan así, 
		aunque nunca volvemos a usar alfa en el programa*/
	Ka[0] = 0.0f;
	Ka[1] = 0.0f;
	Ka[2] = 0.0f;
	Ka[3] = 1.0f;
	Ks[0] = 0.0f;
	Ks[1] = 0.0f;
	Ks[2] = 0.0f;
	Ks[3] = 1.0f;
	Kd[0] = 0.8f;
	Kd[1] = 0.8f;
	Kd[2] = 0.8f;
	Kd[3] = 1.0f;
}

Material::~Material(){
}

void Material::setKa(string buffer){
	size_t pos = buffer.find(" ");
	Ka[0] = stof(buffer.substr(0, pos));
	buffer.erase(0, pos + 1);
	pos = buffer.find(" ");
	Ka[1] = stof(buffer.substr(0, pos));
	buffer.erase(0, pos + 1);
	pos = buffer.find(" ");
	Ka[2] = stof(buffer.substr(0, pos));
	buffer.erase(0, pos + 1);
}

void Material::setKd(string buffer){
	size_t pos = buffer.find(" ");
	Kd[0] = stof(buffer.substr(0, pos));
	buffer.erase(0, pos + 1);
	pos = buffer.find(" ");
	Kd[1] = stof(buffer.substr(0, pos));
	buffer.erase(0, pos + 1);
	pos = buffer.find(" ");
	Kd[2] = stof(buffer.substr(0, pos));
	buffer.erase(0, pos + 1);
}

void Material::setKs(string buffer){
	size_t pos = buffer.find(" ");
	Ks[0] = stof(buffer.substr(0, pos));
	buffer.erase(0, pos + 1);
	pos = buffer.find(" ");
	Ks[1] = stof(buffer.substr(0, pos));
	buffer.erase(0, pos + 1);
	pos = buffer.find(" ");
	Ks[2] = stof(buffer.substr(0, pos));
	buffer.erase(0, pos + 1);
}
