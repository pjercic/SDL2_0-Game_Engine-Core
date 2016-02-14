#include "CApp.h"
 
void CApp::OnEvent(SDL_Event* Event) {
    CEvent::OnEvent(Event);
}

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

/*	If you want to control the camera
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

void CApp::OnExit() {
    Running = false;
}