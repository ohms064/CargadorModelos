#include "Material.h"


Material::Material()
{
}

Material::~Material()
{
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
