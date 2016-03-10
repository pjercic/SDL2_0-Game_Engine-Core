/*! \file CFPS.cpp
    \brief The core of our program.
    
	The CApp class is setting the stage for our entire program. Let me step aside to take special note of how games are typically setup. Most games consist of 5 functions that handle how the game processes. These processes are typically:

	Initialize
	This function handles all the loading of data, whether it be textures, maps, NPCs, or whatever.

	Event
	This function handles all input events from the mouse, keyboard, joysticks, or other devices.

	Loop
	This function handles all the data updates, such as a NPCs moving across the screen, decreasing your health bar, or whatever

	Render
	This function handles all the rendering of anything that shows up on the screen. It does NOT handle data manipulation, as this is what the Loop function is supposed to handle.

	Cleanup
	This function simply cleans up any resources loaded, and insures a peaceful quitting of the game.

	It's important to understand that games are one gigantic loop. Within this loop we find events, update data, and render pictures.

	\author Petar Jerčić
*/

#include "CFPS.h"

CFPS CFPS::FPSControl;	/*!< whenever you make a variable of a class static, you also need to declare it elsewhere. Notice I have CFPS::FPSControl at the top. If you fail to do this, you'll get an undeclared error. */

//! A constructor.
/*!
	Set everything to 0.
*/
CFPS::CFPS() {
	OldTime = 0;
	LastTime = 0;

	SpeedFactor = 0;

	Frames = 0;
	NumFrames = 0;
}

//! we have our OnLoop function where all the magic happens.
/*!
	The first calculation we do, is finding the Frames per Second of the game. This is where SDL_GetTicks comes in. SDL_GetTicks returns the number of milliseconds that have passed since we have called SDL_Init. So, effectively, 1000 milliseconds equals 1 second. Now, notice the condition I am checking. I am checking if the OldTime (which is currently set to 0) + 1000, is less than the current tick count. Think about it, if OldTime is 0 + 1000, and 1001 milliseconds have passed, that means at least 1 second has passed. Why is that important? That tells use to restart the FPS counter.

	Notice inside the if statement we then set OldTime to SDL_GetTicks, set NumFrames to the Frames count, and reset our Frames counter. So, going with the example above, OldTime now becomes 1001. Now, 1001 + 1000, is the next calculation, so another second must pass. Concurrent with this, is the Frames++ at the bottom of that function. This continuelly counts up, until the OldTime resets it. I hope that is easy to understand.

	Next, we have the actual calculation for the SpeedFactor. Like I mentioned earlier, the SpeedFactor determines how fast to move objects. Now, for a better explanation. Say we are on a really slow computer that gets 1 FPS per second. That's a really bad computer by the way. We have the base movement rate set at 32 (our made up number). So, ideally, any computer will move objects 32 pixels per second. So this 1 FPS computer will move the object 32 pixels every second. Now, jump to a 10 FPS computer. We still want to move 32 pixels per second. So, that's 1/10 of 32 right? So, for each calculation we move 3.2 pixels, and after 1 second, we'll have moved 32 pixels.

	To calculate this, we base it on how fast the computer is currently going. This is what LastTime is for. LastTime holds the time it took for the last loop in the game. So, in the constructor it's currently 0. Now, say we have an FPS of 10. That means we have 10 loops in the game every second. How many milliseconds is that? That's 100 milliseconds. So, 100 / 1000 (for 1 second), is 1/10. The same number we got above. Now multiply this by our desired movement rate, and we have our Speed Factor! I'll be showing you how to use this later on, just try to understand how we calculated it.
*/
void CFPS::OnLoop() {
	if (OldTime + 1000 < SDL_GetTicks()) {
		OldTime = SDL_GetTicks();

		NumFrames = Frames;

		Frames = 0;
	}

	SpeedFactor = ((SDL_GetTicks() - LastTime) / 1000.0f) * 32.0f;

	LastTime = SDL_GetTicks();

	Frames++;
}

//! Get FPS.
/*!
	we have our two get functions that return NumFrames (FPS), and the SpeedFactor.
*/
int CFPS::GetFPS() {
	return NumFrames;
}

//! Get Speed Factor.
/*!
	we have our two get functions that return NumFrames (FPS), and the SpeedFactor.
*/
float CFPS::GetSpeedFactor() {
	return SpeedFactor;
}
