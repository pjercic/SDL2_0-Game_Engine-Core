/*! \file CFPS.h
    \brief Header definitions for the frame rate of our program.
    
    But before we get into that, we're going to need a standard for movement. You see, when we play our games on old Pentium 2 as opposed to a quad core, there are apparent differences in speed. So, if we did a simple X++; on the older machine, the entity would move slower than the newer machine. So the idea is simple, figure out the frame rate of the machine, and base our movements off of the frame rate. I call that the speed factor. Now, in order for this to work, we have to have a base frame rate. I usually pick 32, as that is a good number. So if our machine had a frame rate of 32, our speed factor would be 1. If our frame rate was 64, our speed factor would be 0.5. We move twice as slower on the faster machine, that way speeds are consistent across different machines.
	
	\author Petar Jerčić
*/

/*! \var static CFPS FPSControl
    \brief First, we have a single control for accessing our speed facor, and frame rate. Again, a singleton object that we should be used to using by now.
    
    Details.
*/

/*! \var int OldTime
    \brief we have OldTime, which is used to calculate the Frames per second
    
    Details.
*/

/*! \var int LastTime
    \brief we have LastTime, which is used to calculate the speed factor.
    
    Details.
*/

/*! \var float     SpeedFactor
    \brief SpeedFactor is the current speed factor of the game (of course)
    
    Details.
*/

/*! \var int    NumFrames
    \brief NumFrames is the games current FPS
    
    Details.
*/

/*! \var int     Frames
    \brief Frames is the frame count when calculating the frames per second
    
    Details.
*/

/*! \fn CFPS()
    \brief A contructor in HEAD.
	
	Elaborate details for construxctor in HEAD.
*/

/*! \fn void    OnLoop()
    \brief an OnLoop function to calculate everything.
	
	Elaborate details in HEAD.
*/

/*! \fn int     GetFPS()
    \brief access our FPS.
	
	Notice that all of them are private members, so to access our FPS and SpeedFactor we have two get functions. We don't need anyone messing with those variables directly.
*/

/*! \fn float   GetSpeedFactor()
    \brief access our SpeedFactor.
	
	Notice that all of them are private members, so to access our FPS and SpeedFactor we have two get functions. We don't need anyone messing with those variables directly.
*/

#ifndef _CFPS_H_
#define _CFPS_H_

#include <SDL.h>

class CFPS {
public:
	static CFPS FPSControl;

private:
	int     OldTime;
	int     LastTime;

	float     SpeedFactor;

	int    NumFrames;
	int     Frames;

public:
	CFPS();

	void    OnLoop();

public:
	int     GetFPS();

	float   GetSpeedFactor();
};

#endif