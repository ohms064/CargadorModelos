#pragma once
#include <string>
#include <iostream>
using namespace std;
class Texturas
{
	public:
		float x;
		float y;
		//Funciones
		Texturas();
		void print();
		void setAll(int i, int j);
		void setAll(string buffer);
};

