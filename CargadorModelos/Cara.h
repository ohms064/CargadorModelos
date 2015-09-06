#pragma once
#include<queue>
#include<string>
#include <iostream>
using namespace std;
class Cara
{
	public:
		queue<int> vertice;
		queue<int> textura;
		queue<int> normal;
		int verticeFront;
		int texturaFront;
		int normalFront;
		Cara();
		void setCara(string input);
		void popVertice();
		void popTextura();
		void popNormal();
		void printVertice();
		void printTextura();
		void printNormal();
};

