#pragma once
#include<queue>
class Cara
{
	public:
		std::queue<int> vertice;
		std::queue<int> textura;
		std::queue<int> normal;
		int verticeFront;
		int texturaFront;
		int normalFront;
		Cara();
		void setCara(char* aspe);
		void popVertice();
		void popTextura();
		void popNormal();
		void printVertice();
		void printTextura();
		void printNormal();
};

