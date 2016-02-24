#include "CAnimation.h"

CAnimation::CAnimation() {
	CurrentFrame = 0;
	MaxFrames = 0;
	FrameInc = 1;

	FrameRate = 100; //Milliseconds
	OldTime = 0;

	Oscillate = false;
}

//! An animation loop.
/*!
	By taking the Old Time in milliseconds plus the desired frame rate, we can check it against how long the SDL has been running. So, for example, we just started our program. SDL_GetTicks is 0, and OldTime is 0. Our desired frame rate is 1 frame per second. So FrameRate = 1000 (milliseconds). So, is 0 + 1000 greater than 0? Yes, thus we will skip over the function and wait. But once 0 + 1000 is less than SDL_GetTicks, that must mean 1 second has passed. So we increment the frame, and then reset OldTime to the current time, and start over.
	
	We already know what the OldTime and such do, but what about the rest? For now, look at the else statement of the Oscillate if statement. You'll notice we're simply checking if the CurrentFrame has exceeded the Max Frames. If it has, reset back to 0. Pretty simple. Then below that, outside of the block, we increase to the next frame.

	Now, the more confusing part is the Oscillate if statement. This is where the FrameInc variable comes in. Basically, the FrameInc is set to 1 or -1, depending on how we are increasing or decreasing the frames. Remember, Oscillating causes the frames to go from 0 to 9 back to 0. So if the FrameInc is greater than 0, we are increasing the frames, otherwise we are decreasing frames. The innermost if statements basically inverse the FrameInc if we reached the end of 0, or MaxFrames.
*/
void CAnimation::OnAnimate() {
	if (OldTime + FrameRate > SDL_GetTicks()) {
		return;
	}

	OldTime = SDL_GetTicks();

	CurrentFrame += FrameInc;

	if (Oscillate) {
		if (FrameInc > 0) {
			if (CurrentFrame >= MaxFrames-1) {
				FrameInc = -FrameInc;
			}
		}
		else {
			if (CurrentFrame <= 0) {
				FrameInc = -FrameInc;
			}
		}
	}
	else {
		if (CurrentFrame >= MaxFrames) {
			CurrentFrame = 0;
		}
	}
}

void CAnimation::SetFrameRate(int Rate) {
	FrameRate = Rate;
}

void CAnimation::SetCurrentFrame(int Frame) {
	if (Frame < 0 || Frame >= MaxFrames) return;

	CurrentFrame = Frame;
}

int CAnimation::GetCurrentFrame() {
	return CurrentFrame;
}