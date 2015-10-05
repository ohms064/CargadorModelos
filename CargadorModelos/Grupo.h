#pragma once
#include<string>


using namespace std;
class Grupo
{
public:
	string id;
	int inicio;
	string tex;

	Grupo();
	void createTexture(string filename);
};

