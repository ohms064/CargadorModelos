#pragma once
#include <string>
#include <iostream>
using namespace std;
class Vertice
{
	public:
		float x;
		float y;
		float z;
		//Funciones
		Vertice();
		void print();
		void setAll(int i, int j, int k);
		void setAll(string buffer);
};

