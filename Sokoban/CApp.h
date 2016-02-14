#ifndef _CAPP_H_
    #define _CAPP_H_
 
#include <SDL.h>
#include <stdio.h>
#include "CSurface.h"
#include "CEvent.h"
#include "CAnimation.h"
#include "CEntity.h"
#include "Define.h"
#include "CArea.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CSoundBank.h"
 
class CApp : public CEvent {
    private:
        bool            Running;

		//The window we'll be rendering to
		SDL_Window* window;
        SDL_Surface*    Surf_Display;
 
		//	Test surface
        SDL_Surface*    Surf_Test;

	private:
		SDL_Surface*    Surf_Grid;

		SDL_Surface*    Surf_X;
		SDL_Surface*    Surf_O;

		CAnimation      Anim_Yoshi;

	private:
		CEntity         Entity1;
		CEntity         Entity2;

		CPlayer			Player;
		CPlayer			Player2;

		int SoundA;
        int SoundB;

	private:
		int        Grid[9];

		int CurrentPlayer;

		enum {
			GRID_TYPE_NONE = 0,
			GRID_TYPE_X,
			GRID_TYPE_O
		};
 
    public:

        CApp();
 
        int OnExecute();
 
    public:
        bool OnInit();
 
        void OnEvent(SDL_Event* Event);

		void OnLButtonDown(int mX, int mY);

		void OnKeyDown(SDL_Keysym sym, Uint16 mod, Uint16 unicode);

		void OnKeyUp(SDL_Keysym sym, Uint16 mod, Uint16 unicode);

		void OnExit(); 
 
        void OnLoop();
 
        void OnRender();
 
        void OnCleanup();

	public:
		void Reset();

		void SetCell(int ID, int Type);
};
 
#endif
