#include "CApp.h"
 
void CApp::OnRender() {

	//	Fill whole screen with solid color
	
	SDL_Rect Rect;
	Rect.x = 0;
	Rect.y = 0;
	Rect.w = SCREEN_WIDTH;
	Rect.h = SCREEN_HEIGHT;

	SDL_FillRect(Surf_Display, &Rect, 0);

	//	Test surfaces - delete
    CSurface::OnDraw(Surf_Display, Surf_Test, 0, 0);
	CSurface::OnDraw(Surf_Display, Surf_Test_BG, 100, 100, 0, 0, 50, 50);
		
	//Update the surface
	/*! Notice a new function here SDL_Flip. This basically refreshes the buffer and displays Surf_Display onto the screen. This is called double buffering. It's the process of drawing everything into memory, and then finally drawing everything to the screen. If we didn't do this, we would have images flickering on the screen. Remember the SDL_DOUBLEBUF flag? This is what turns double buffering on. */
	SDL_UpdateWindowSurface( window );
}
