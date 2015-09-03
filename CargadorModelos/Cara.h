#pragma once
#include<queue>
class Cara
{
	public:
		std::queue<int> vertice;
		std::queue<int> textura;
		std::queue<int> normal;
		Cara();
		void getCara(char* aspe);
		int popVertice();
		int popTextura();
		int popNormal();
	
};

