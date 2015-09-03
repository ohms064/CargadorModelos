#pragma once
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
		void setAll(char* buffer, char delimitadores[], char* contexto);
};

