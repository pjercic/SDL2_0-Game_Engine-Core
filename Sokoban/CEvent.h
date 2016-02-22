/*! \file CEvent.h
    \brief Header definitions for the core of our program.
    
    Details.
	\author Petar Jerčić
*/

/*! \fn CEvent()
    \brief A contructor.
	
	Elaborate details for construxctor in HEAD.
*/

#ifndef _CEVENT_H_
    #define _CEVENT_H_
 
#include <SDL.h>

//! An event class.
/*!
	Alongside the basics of game development is something called Events. All videogames, from pong to the highly complex PC games and console titles, use events to interact with the player. These events can come from keyboards, mice, joysticks, gamepads, and so on, or events from our operating system. It's important to understand how events work if we are to appropriately interact a user with a game. We've already been using events, but only for closing our window, now we'll look at how to receive events from the user.
*/
class CEvent {
    public:
        CEvent();
 
        virtual ~CEvent();
 
        virtual void OnEvent(SDL_Event* Event);
 
        virtual void OnInputFocus();
 
        virtual void OnInputBlur();
 
		virtual void OnKeyDown(SDL_Keysym sym, Uint16 mod, Uint16 unicode);
 
		virtual void OnKeyUp(SDL_Keysym sym, Uint16 mod, Uint16 unicode);
 
        virtual void OnMouseFocus();
 
        virtual void OnMouseBlur();
 
        virtual void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
 
        virtual void OnMouseWheel(bool Up, bool Down);    //Not implemented
 
        virtual void OnLButtonDown(int mX, int mY);
 
        virtual void OnLButtonUp(int mX, int mY);
 
        virtual void OnRButtonDown(int mX, int mY);
 
        virtual void OnRButtonUp(int mX, int mY);
 
        virtual void OnMButtonDown(int mX, int mY);
 
        virtual void OnMButtonUp(int mX, int mY);
 
        virtual void OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value);
 
        virtual void OnJoyButtonDown(Uint8 which, Uint8 button);
 
        virtual void OnJoyButtonUp(Uint8 which, Uint8 button);
 
        virtual void OnJoyHat(Uint8 which, Uint8 hat, Uint8 value);
 
        virtual void OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);
 
        virtual void OnMinimize();
 
        virtual void OnRestore();
 
        virtual void OnResize(int w,int h);
 
        virtual void OnExpose();
 
        virtual void OnExit();
 
        virtual void OnUser(Uint8 type, int code, void* data1, void* data2);
};
 
#endif