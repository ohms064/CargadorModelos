#pragma once
#include<string>
#include<vector>
using namespace std;
class Material
{
public:
	string textura, mapKd;
	float Ns, Ni, d;
	float Ka[3], Kd[3], Ks[3];

	Material();
	~Material();
};

