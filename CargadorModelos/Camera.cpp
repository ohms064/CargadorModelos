#include "Camera.h"


Camera::Camera(){
	anguloCamaraY = 0.0f;
	anguloCamaraX = 0.0f;
	anguloCamaraZ = 0.0f;

	miradaAPieY = 0.0f;
	posCamPieX = 0.0f;
	posCamPieY = 0.0f;
	posCamPieZ = 10.0f;

	viewCamPieX = 0.0f;
	viewCamPieY = 0.0f;
	viewCamPieZ = 0.0f;

	upCamPieX = 0.0f;
	upCamPieY = 1.0f;
	upCamPieZ = 0.0f;
}

void Camera::MoveX(float speed) {
	float x = viewCamPieX - posCamPieX;
	float z = viewCamPieZ - posCamPieZ;

	posCamPieX += x*speed;
	posCamPieZ += z*speed;

}

void Camera::MoveY(float speed) {
	posCamPieY += 10 * speed;
	viewCamPieY += 10 * speed;

}

void Camera::MoveZ(float speed) {
	float x = viewCamPieX - posCamPieX;
	float z = viewCamPieZ - posCamPieZ;

	posCamPieX += z*speed*-1;
	posCamPieZ += x*speed;
	viewCamPieX += z*speed*-1;
	viewCamPieZ += x*speed;

}

Camera::~Camera(){
}
