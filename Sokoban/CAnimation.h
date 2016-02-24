/*! \file CAnimation.h
    \brief Header definitions for the animation part.
    
    Details.
	\author Petar Jerčić
*/

/*! \var int CurrentFrame
    \brief So the first variable I want you to see is CurrentFrame.
    
    This is the current frame of the animation that we are going to draw on the screen. Whatever value it has, will determine what part of the surface we will draw to the screen.
	
	When the CurrentFrame increases by 1, we jump down 64 pixels (the height of Yoshi's frame), and draw that frame.
*/

/*! \var int MaxFrames
    \brief The other part of this class is that we need to know how many frames this animation is, thus the MaxFrames.
    
    Details
*/

/*! \var long OldTime
    \brief The last vital part to know is how many frames per second, or rather, how fast this animation is going to display.
    
    By taking the Old Time in milliseconds plus the desired frame rate, we can check it against how long the SDL has been running. So, for example, we just started our program. SDL_GetTicks is 0, and OldTime is 0. Our desired frame rate is 1 frame per second. So FrameRate = 1000 (milliseconds). So, is 0 + 1000 greater than 0? Yes, thus we will skip over the function and wait. But once 0 + 1000 is less than SDL_GetTicks, that must mean 1 second has passed. So we increment the frame, and then reset OldTime to the current time, and start over.
*/

/*! \var int FrameRate
    \brief The last vital part to know is how many frames per second, or rather, how fast this animation is going to display.
    
    By taking the Old Time in milliseconds plus the desired frame rate, we can check it against how long the SDL has been running. So, for example, we just started our program. SDL_GetTicks is 0, and OldTime is 0. Our desired frame rate is 1 frame per second. So FrameRate = 1000 (milliseconds). So, is 0 + 1000 greater than 0? Yes, thus we will skip over the function and wait. But once 0 + 1000 is less than SDL_GetTicks, that must mean 1 second has passed. So we increment the frame, and then reset OldTime to the current time, and start over.
*/

/*! \var bool Oscillate
    \brief Brief.
    
    The next interesting tid bit is Oscillate and FrameInc. Not that I wanted to confuse anyone by adding this, but I feel it's necessary for certain things later on. Basically, when the Oscillate flag is true, the animation will increase frames, and then decrease frames. If we had an animation with 10 frames, it would do something like this:

	0 1 2 3 4 5 6 7 8 9 8 7 6 5 4 3 2 1 2 ...

	You see, it goes up to 9, and then decreases back down to 0, and so on.
*/

/*! \var int FrameInc
    \brief Brief.
    
    The next interesting tid bit is Oscillate and FrameInc. Not that I wanted to confuse anyone by adding this, but I feel it's necessary for certain things later on. Basically, when the Oscillate flag is true, the animation will increase frames, and then decrease frames. If we had an animation with 10 frames, it would do something like this:

	0 1 2 3 4 5 6 7 8 9 8 7 6 5 4 3 2 1 2 ...

	You see, it goes up to 9, and then decreases back down to 0, and so on.
*/

/*! \fn void OnAnimate()
    \brief Animation loop.

	The next interesting tid bit is Oscillate and FrameInc. Not that I wanted to confuse anyone by adding this, but I feel it's necessary for certain things later on. Basically, when the Oscillate flag is true, the animation will increase frames, and then decrease frames. If we had an animation with 10 frames, it would do something like this:

	0 1 2 3 4 5 6 7 8 9 8 7 6 5 4 3 2 1 2 ...

	You see, it goes up to 9, and then decreases back down to 0, and so on. There are some interesting uses for this, but we'll get into that in other lessons.
*/

#ifndef _CANIMATION_H_
#define _CANIMATION_H_

#include <SDL.h>

//!  A SDL Animation class.
/*!
	We'll be creating a new class to handle Animation, and in the next tutorial we will create a class to handle Entities. Please keep in mind that these two things are seperate, and while I know they could be one class, I don't wish to take that approach. So please hold back your criticism.
	
	Some explanation on what this class is all about now. There is one basic element of animation that we need to handle, that is the current frame of the animation. Take the Yoshi image below for example (we'll be using him in this tutorial). You'll notice we have 8 frames of Yoshi on one image. Each frame would then be labeled 0, 1, 2 from Top to Bottom.
	
	Remember the second tutorial where we create a function to draw part of an image? Well, if we take that function in conjunction with the frame of the animation, voila!
*/
class CAnimation {
private:
	int    CurrentFrame;

	int     FrameInc;

private:
	int     FrameRate; //Milliseconds

	long    OldTime;

public:
	int    MaxFrames;

	bool    Oscillate;

public:
	CAnimation();

	void OnAnimate();

public:
	void SetFrameRate(int Rate);

	void SetCurrentFrame(int Frame);

	int GetCurrentFrame();
};

#endif