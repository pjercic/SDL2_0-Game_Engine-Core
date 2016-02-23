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

	if (breakBall)
		CSurface::OnDraw(Surf_Display, Surf_BallBreak, 100, 100);
	else
		CSurface::OnDraw(Surf_Display, Surf_Ball, 100, 100);

	if (smallPaddle)
		CSurface::OnDraw(Surf_Display, Surf_PaddleSmall, 0, 0);
	else
		CSurface::OnDraw(Surf_Display, Surf_Paddle, 0, 0);
		
	//Update the surface
	/*! Notice a new function here SDL_Flip. This basically refreshes the buffer and displays Surf_Display onto the screen. This is called double buffering. It's the process of drawing everything into memory, and then finally drawing everything to the screen. If we didn't do this, we would have images flickering on the screen. Remember the SDL_DOUBLEBUF flag? This is what turns double buffering on. */
	SDL_UpdateWindowSurface( window );
}
