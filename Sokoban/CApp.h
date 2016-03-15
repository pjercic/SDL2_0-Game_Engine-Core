/*! \file CApp.h
    \brief Header definitions for the core of our program.
    
    Details.
*/

/*! \var bool Running
    \brief This is our exit out of the game loop.
    
    When this is set to false, it will end the program, and in turn exit the program.
*/

/*! \var SDL_Window* window
    \brief Holds the handler to our window (main)
    
    When we need data about the window our game is running in (currently main), we ue this variable.
*/

/*! \var SDL_Surface* Surf_Display;
    \brief An SDL Surface is anything that can be drawn, or drawn to. 
	
	Say we have a blank piece of paper, a pencil, and some stickers; this paper could be called our display "surface." We can draw to it, put stickers on it, or whatever. The stickers we have are also surfaces; we can draw on them and put other stickers on them as well. So, Surf_Display is simply our "piece of blank paper" that we will draw all our stuff on.
*/

/*! \fn CApp()
    \brief A contructor in HEAD.
	
	Elaborate details for construxctor in HEAD.
*/

/*! \fn int OnExecute()
    \brief It's important to understand that games are one gigantic loop. Within this loop we find events, update data, and render pictures.
	
	Each iteration of the loop we do something with data, and render accordingly. Events are extra, as a means for the user to manipulate data as well. In that sense, Events aren't required to make a game, but are needed when you want the user to be able to manipulate data (such as move a NPC to the left).
*/

/*! \fn int bool OnInit()
    \brief Initialize our game
*/

/*! \fn void OnEvent(SDL_Event* Event)
    \brief Process events
	
	The SDL event structure is broken down into types. These types can range from keypresses, to mouse movements; what we simply are doing here is checking the event type.
*/

/*! \fn void OnLButtonDown(int mX, int mY)
	\brief mouse events.

	Now that we have our surfaces drawing, we'll need a way to communicate from the user to the computer. We'll use mouse events for this. When the users clicks a cell it will set the cell appropriately. We are going to need to overload one of the CEvent functions for this.
*/

/*! \fn void OnKeyDown(SDL_Keysym sym, Uint16 mod, Uint16 unicode)
	\brief Keyboard event

	Key press down.
*/

/*! \fn void OnLButtonDown(int mX, int mY)
	\brief Keyboard event

	Key release up.
*/

/*! \fn void OnExit()
    \brief Process exit event
	
	We're passing the Event structure to our class now, it will take care of the correct function calls. Now when we want to check for an event, we override the function. Since we got rid of checking for the SDL_QUIT event, lets use the function instead.
*/

/*! \fn int OnCleanup()
    \brief Clean up object and quit SDL
*/

/*! \fn void OnLButtonDown(int mX, int mY)
    \brief Event for left click .
    \param mX X position.
    \param mY Y position.
*/

/*! \fn void Reset()
	\brief a way to reset the board.
*/

/*! \fn void SetCell(int ID, int Type)
	\brief So far so good. The next thing we are going to have to do is make the ability to place effect on the screen. Lets create a new function that will handle this.
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
	
        bool            Running;	//	This is our exit out of the game loop. When this is set to false, it will end the program, and in turn exit the program.

		//The window we'll be rendering to
		SDL_Window* window;
        SDL_Surface*    Surf_Display;
 
		//	Test surface
        SDL_Surface*    Surf_Test;

	private:
		SDL_Surface*    Surf_Grid;

		SDL_Surface*    Surf_X;
		SDL_Surface*    Surf_O;

		CAnimation      Anim_Yoshi;	/*!< \brief Create a new CAnimation object. */

	private:
		CEntity         Entity1;
		CEntity         Entity2;

		CPlayer			Player;
		CPlayer			Player2;

		int SoundA;	/*!< \brief Sound ID. */
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
		  A more elaborate description of the constructor in H.
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
