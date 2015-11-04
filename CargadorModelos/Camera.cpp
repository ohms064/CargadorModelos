#include "Camera.h"


Camera::Camera(){
	anguloCamaraY = 0.0f;
	anguloCamaraX = 0.0f;
	anguloCamaraZ = 0.0f;

	miradaAPieY = 0.0f;
	posCamPieX = 0.0f;
	posCamPieY = 0.0f;
	posCamPieZ = 20.0f;

	viewCamPieX = 0.0f;
	viewCamPieY = 0.0f;
	viewCamPieZ = 0.0f;

	upCamPieX = 0.0f;
	upCamPieY = 1.0f;
	upCamPieZ = 0.0f;
}


Camera::~Camera(){
}
