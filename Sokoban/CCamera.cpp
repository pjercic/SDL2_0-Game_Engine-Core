/*! \file CCamera.cpp
	\brief code for the camera.
	
	From top to bottom, like usual, we have are static member first. We then have the constructor defaulting some variables. The OnMove function will increase the X and Y, like I said before. We then have GetX. It will check to see if we have a valid target, and if so return the targets coordinates as the camera coordinates, otherwise return the camera x. For centering mode, we take the screen width and divide by two to find the center of the screen, and then subtract it from the target coordinates. This will center the camera to the target. We then have the SetPos and SetTarget functions, which are self-explanatory.
    	
	\author Petar Jerčić
*/

#include "CCamera.h"

CCamera CCamera::CameraControl;

CCamera::CCamera() {
	X = Y = 0;

	TargetX = TargetY = NULL;

	TargetMode = TARGET_MODE_NORMAL;
}

void CCamera::OnMove(int MoveX, int MoveY) {
	X += MoveX;
	Y += MoveY;
}

int CCamera::GetX() {
	if (TargetX != NULL) {
		if (TargetMode == TARGET_MODE_CENTER) {
			return *TargetX - (SCREEN_WIDTH / 2);
		}

		return *TargetX;
	}

	return X;
}

int CCamera::GetY() {
	if (TargetY != NULL) {
		if (TargetMode == TARGET_MODE_CENTER) {
			return *TargetY - (SCREEN_HEIGHT / 2);
		}

		return *TargetY;
	}

	return Y;
}

void CCamera::SetPos(int X, int Y) {
	this->X = X;
	this->Y = Y;
}

void CCamera::SetTarget(float* X, float* Y) {
	TargetX = X;
	TargetY = Y;
}