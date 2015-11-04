#pragma once
#include < GL/glut.h>
class Camera
{
public:
	GLfloat anguloCamaraY;
	GLfloat anguloCamaraX;
	GLfloat anguloCamaraZ;

	float miradaAPieY;
	float posCamPieX;
	float posCamPieY;
	float posCamPieZ;

	float viewCamPieX;
	float viewCamPieY;
	float viewCamPieZ;

	float upCamPieX;
	float upCamPieY;
	float upCamPieZ;

	Camera();
	~Camera();
};

