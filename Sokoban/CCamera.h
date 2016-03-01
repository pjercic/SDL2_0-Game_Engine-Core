/*! \file CCamera.h
	\brief Header definitions for the camera.
    	
	First, we have a control member object, just like area. Then we have the coordinates of where the camera is. An extra thing I threw in, was the ability to target something. For example, in a Megaman game the camera would target Megaman himself. That way, when Megaman moves the camera would automatically update. So we have two pointers for X and Y coordinates. If these are null, the camera will automatically revert to the cameras position. Next, we have a target mode, which, for now, is either normal (the camera will position to the top left of the target) or center (will center the camera to the target). Pretty simply I think.

	We then have a few functions, the first is the OnMove, which will increase the X and Y of the camera by MoveX and MoveY. So OnMove(-1, 0) would move the camera to the left one pixel. We then have Get functions for the coordinates, and the ability to set the coordinates and set a target.

	\author Petar Jerčić
*/

#ifndef _CCAMERA_H_
#define _CCAMERA_H_

#include <SDL.h>

#include "Define.h"

enum {
	TARGET_MODE_NORMAL = 0,
	TARGET_MODE_CENTER
};

class CCamera {
public:
	static CCamera CameraControl;

private:
	int X;
	int Y;

	float* TargetX;
	float* TargetY;

public:
	int TargetMode;

public:
	CCamera();

public:
	void OnMove(int MoveX, int MoveY);

public:
	int GetX();
	int GetY();

public:
	void SetPos(int X, int Y);

	void SetTarget(float* X, float* Y);
};

#endif