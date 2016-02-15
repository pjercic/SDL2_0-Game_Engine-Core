/*! \file CApp.h
    \brief Header definitions for the core of our program.
    
    Details.
*/

/*! \var bool Running
    \brief This is our exit out of the game loop.
    
    When this is set to false, it will end the program, and in turn exit the program.
*/

/*! \fn int OnExecute()
    \brief Each iteration of the loop we do something with data, and render accordingly. Events are extra, as a means for the user to manipulate data as well. In that sense, Events aren't required to make a game, but are needed when you want the user to be able to manipulate data (such as move a NPC to the left). 
*/


/*! \fn void OnLButtonDown(int mX, int mY)
    \brief Event for left click .
    \param mX X position.
    \param mY Y position.
*/

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
 
//!  A core program class.
/*!
  A more elaborate class description.
*/
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

		//! An enum.
		/*! More detailed enum description. */
		enum {
			GRID_TYPE_NONE = 0,
			GRID_TYPE_X,
			GRID_TYPE_O
		};
 
    public:

		//! A constructor.
		/*!
		  A more elaborate description of the constructor.
		*/
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
