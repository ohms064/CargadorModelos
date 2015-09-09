#pragma once
#include <string>
#include <iostream>
using namespace std;
class Normal
{
public:
	float x;
	float y;
	float z;
	//Funciones
	Normal();
	void print();
	void setAll(int i, int j, int k);
	void setAll(string buffer);
};

