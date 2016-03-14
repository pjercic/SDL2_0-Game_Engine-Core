/*! \file CApp_OnEvent.cpp
    \brief Header definitions for the core of our program.
    
    Details.
	\author Petar Jerčić
*/

#include "CApp.h"

//! An event procesing delegate.
/*!
	Calling CEvent object to resolve the SDL_Event. We have the event class setup, now lets actually link events to our new class structure.
*/
void CApp::OnEvent(SDL_Event* Event) {
    CEvent::OnEvent(Event);
}

//! Mouse event.
/*!
	First, we are doing the reverse of what we did with translating to X and Y from an ID, this time we are translating to an ID. We then make sure that that cell hasn't already been taken, if it has, we return out of the function. Next, we are checking which players turn it is, set the cell appropriately, and then switch turns. 
*/
void CApp::OnLButtonDown(int mX, int mY)
{
	int ID = mX / 200;
	ID = ID + ((mY / 200) * 3);

	if (Grid[ID] != GRID_TYPE_NONE) {
		return;
	}

	if (CurrentPlayer == 0) {
		SetCell(ID, GRID_TYPE_X);
		CurrentPlayer = 1;
	}
	else {
		SetCell(ID, GRID_TYPE_O);
		CurrentPlayer = 0;
	}
}

/*	We aren't going to be controlling the camera anymore, but we'll be controlling our main Player who will dictate where the camera goes.
	If you want to control the camera, use the code bellow
void CApp::OnKeyDown(SDL_Keycode sym, SDL_Keymod mod, Uint16 unicode) {
	switch (sym) {
	case SDLK_UP:      CCamera::CameraControl.OnMove(0, 5); break;
	case SDLK_DOWN:  CCamera::CameraControl.OnMove(0, -5); break;
	case SDLK_LEFT:  CCamera::CameraControl.OnMove(5, 0); break;
	case SDLK_RIGHT: CCamera::CameraControl.OnMove(-5, 0); break;

	default: {
	}
	}
}
 */

//! Keyboard event
/*!
	To go over this quickly, we basically check if Left or Right is pressed, and set MoveLeft or MoveRight on our Entity to true.
*/
void CApp::OnKeyDown(SDL_Keysym sym, Uint16 mod, Uint16 unicode) {
	switch(sym.sym) {
        case SDLK_LEFT: {
            Player.MoveLeft = true;
			CSoundBank::SoundControl.Play(SoundA);
            break;
        }
 
        case SDLK_RIGHT: {
            Player.MoveRight = true;
			CSoundBank::SoundControl.Play(SoundB);
            break;
        }

		case SDLK_SPACE: {
			Player.Jump();
			break;
		}
 
        default: {
        }
    }
}

//! Keyboard event
/*!
	If the key is depressed, we set it to false.
*/
void CApp::OnKeyUp(SDL_Keysym sym, Uint16 mod, Uint16 unicode) {
    switch(sym.sym) {
        case SDLK_LEFT: {
            Player.MoveLeft = false;
            break;
        }
 
        case SDLK_RIGHT: {
            Player.MoveRight = false;
            break;
        }
 
        default: {
        }
    }
}

//! The OnExit function handles the SDL_QUIT events. Now that we have the prototype, lets define what it does.
/*!
	The type above we are looking for is the request to close the window (i.e., when the user clicks the X button). If that event happens to take place, we set Running to false, thus ending our program. Simple enough.
*/
void CApp::OnExit() {
    Running = false;
}