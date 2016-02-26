#include "CApp.h"
 
void CApp::OnRender() {

	//	Fill whole screen with solid color
	
	SDL_Rect Rect;
	Rect.x = 0;
	Rect.y = 0;
	Rect.w = SCREEN_WIDTH;
	Rect.h = SCREEN_HEIGHT;

	SDL_FillRect(Surf_Display, &Rect, 0);

	CSurface::OnDraw(Surf_Display, Surf_Background, 0, 0);	/*!< \brief Draw background. */

	bool breakBall = false;
	bool smallPaddle = false;

	/*! \brief Next, all we have to do is check the cell type, and then draw the correct surface at that cell. */
	for (int i = 0; i < 9; i++) {

		if (Effect[i] == EFF_TYPE_BREAK)
			breakBall = true;
		else if (Effect[i] == EFF_TYPE_SHORT)
			smallPaddle = true;
	}

	/*! \brief we are basically encapsulating the basic functions of a game within the Entity class? We have to call those functions now in the respective CApp functions.

	We are basically running through each Entity in our vector, and calling the OnLoop function. Simple enough! (And we're doing an error checking so we don't call any NULL pointers).*/

	for (int i = 0; i < CEntity::EntityList.size(); i++) {
		if (!CEntity::EntityList[i]) continue;

		CEntity::EntityList[i]->OnRender(Surf_Display);
	}

	//if (breakBall)
	//	CSurface::OnDraw(Surf_Display, Surf_BallBreak, 100, 100);
	//else
	//	CSurface::OnDraw(Surf_Display, Surf_Ball, 100, 100);

	//if (smallPaddle)
	//	CSurface::OnDraw(Surf_Display, Surf_PaddleSmall, 0, 0);
	//else
	//	CSurface::OnDraw(Surf_Display, Surf_Paddle, 0, 0);

	//CSurface::OnDraw(Surf_Display, Surf_Animation, 290, 220, 0, Anim_Yoshi.GetCurrentFrame() * 64, 64, 64);	/*!< \brief to make it actually animate. */
		
	//Update the surface
	/*! Notice a new function here SDL_Flip. This basically refreshes the buffer and displays Surf_Display onto the screen. This is called double buffering. It's the process of drawing everything into memory, and then finally drawing everything to the screen. If we didn't do this, we would have images flickering on the screen. Remember the SDL_DOUBLEBUF flag? This is what turns double buffering on. */
	SDL_UpdateWindowSurface( window );
}
