/*! \file CEvent.cpp
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

*/

#include "CEvent.h"
 
CEvent::CEvent() {
}
 
CEvent::~CEvent() {
    //Do nothing
}

//! An event procesor.
/*!
	Lots of code, but all the SDL events should be covered. What we basically are doing is taking an SDL_Event pointer, and switching through the types, and then calling the appropriate function. It just looks like a lot since they are quite a bit of events.
*/
void CEvent::OnEvent(SDL_Event* Event) {
    switch(Event->type) {
        case SDL_WINDOWEVENT: {
            switch(Event->window.event) {
                case SDL_WINDOWEVENT_ENTER: {
					OnMouseFocus();
                    break;
                }
				case SDL_WINDOWEVENT_LEAVE: {
					OnMouseBlur();
                    break;
                }
                case SDL_WINDOWEVENT_FOCUS_GAINED: {
					OnInputFocus();
                    break;
                }
				case SDL_WINDOWEVENT_FOCUS_LOST: {
					OnInputBlur();
                    break;
                }
                case SDL_WINDOWEVENT_SHOWN:    {
					OnRestore();
                    break;
                }
				case SDL_WINDOWEVENT_HIDDEN:    {
					OnMinimize();
                    break;
                }
				case SDL_WINDOWEVENT_RESIZED: {
					OnResize(Event->window.data1,Event->window.data2);
					break;
				}
 
				case SDL_WINDOWEVENT_EXPOSED: {
					OnExpose();
					break;
				}
            }
            break;
        }
 
        case SDL_KEYDOWN: {
			
			OnKeyDown(Event->key.keysym, Event->key.keysym.mod, Event->key.keysym.mod);
            break;
        }
 
        case SDL_KEYUP: {
            OnKeyUp(Event->key.keysym, Event->key.keysym.mod, Event->key.keysym.mod);
            break;
        }
 
        case SDL_MOUSEMOTION: {
            OnMouseMove(Event->motion.x,Event->motion.y,Event->motion.xrel,Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
            break;
        }
 
        case SDL_MOUSEBUTTONDOWN: {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonDown(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonDown(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonDown(Event->button.x,Event->button.y);
                    break;
                }
            }
            break;
        }
 
        case SDL_MOUSEBUTTONUP:    {
            switch(Event->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonUp(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonUp(Event->button.x,Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonUp(Event->button.x,Event->button.y);
                    break;
                }
            }
            break;
        }
 
        case SDL_JOYAXISMOTION: {
            OnJoyAxis(Event->jaxis.which,Event->jaxis.axis,Event->jaxis.value);
            break;
        }
 
        case SDL_JOYBALLMOTION: {
            OnJoyBall(Event->jball.which,Event->jball.ball,Event->jball.xrel,Event->jball.yrel);
            break;
        }
 
        case SDL_JOYHATMOTION: {
            OnJoyHat(Event->jhat.which,Event->jhat.hat,Event->jhat.value);
            break;
        }
        case SDL_JOYBUTTONDOWN: {
            OnJoyButtonDown(Event->jbutton.which,Event->jbutton.button);
            break;
        }
 
        case SDL_JOYBUTTONUP: {
            OnJoyButtonUp(Event->jbutton.which,Event->jbutton.button);
            break;
        }
 
        case SDL_QUIT: {
            OnExit();
            break;
        }
 
        case SDL_SYSWMEVENT: {
            //Ignore
            break;
        }
 
        default: {
            OnUser(Event->user.type,Event->user.code,Event->user.data1,Event->user.data2);
            break;
        }
    }
}
 
void CEvent::OnInputFocus() {
    //Pure virtual, do nothing
}
 
void CEvent::OnInputBlur() {
    //Pure virtual, do nothing
}
 
void CEvent::OnKeyDown(SDL_Keysym sym, Uint16 mod, Uint16 unicode) {
    //Pure virtual, do nothing
}
 
void CEvent::OnKeyUp(SDL_Keysym sym, Uint16 mod, Uint16 unicode) {
    //Pure virtual, do nothing
}
 
void CEvent::OnMouseFocus() {
    //Pure virtual, do nothing
}
 
void CEvent::OnMouseBlur() {
    //Pure virtual, do nothing
}
 
void CEvent::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) {
    //Pure virtual, do nothing
}
 
void CEvent::OnMouseWheel(bool Up, bool Down) {
    //Pure virtual, do nothing
}
 
void CEvent::OnLButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}
 
void CEvent::OnLButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}
 
void CEvent::OnRButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}
 
void CEvent::OnRButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}
 
void CEvent::OnMButtonDown(int mX, int mY) {
    //Pure virtual, do nothing
}
 
void CEvent::OnMButtonUp(int mX, int mY) {
    //Pure virtual, do nothing
}
 
void CEvent::OnJoyAxis(Uint8 which,Uint8 axis,Sint16 value) {
    //Pure virtual, do nothing
}
 
void CEvent::OnJoyButtonDown(Uint8 which,Uint8 button) {
    //Pure virtual, do nothing
}
 
void CEvent::OnJoyButtonUp(Uint8 which,Uint8 button) {
    //Pure virtual, do nothing
}
 
void CEvent::OnJoyHat(Uint8 which,Uint8 hat,Uint8 value) {
    //Pure virtual, do nothing
}
 
void CEvent::OnJoyBall(Uint8 which,Uint8 ball,Sint16 xrel,Sint16 yrel) {
    //Pure virtual, do nothing
}
 
void CEvent::OnMinimize() {
    //Pure virtual, do nothing
}
 
void CEvent::OnRestore() {
    //Pure virtual, do nothing
}
 
void CEvent::OnResize(int w,int h) {
    //Pure virtual, do nothing
}
 
void CEvent::OnExpose() {
    //Pure virtual, do nothing
}
 
void CEvent::OnExit() {
    //Pure virtual, do nothing
}
 
void CEvent::OnUser(Uint8 type, int code, void* data1, void* data2) {
    //Pure virtual, do nothing
}