#pragma once
#include <string>
#include <iostream>
using namespace std;
class Vertices
{
	public:
		float x;
		float y;
		float z;
		//Funciones
		Vertices();
		void print();
		void setAll(int i, int j, int k);
		void setAll(string buffer);
};

