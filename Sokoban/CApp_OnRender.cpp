#include "CApp.h"
 
void CApp::OnRender() {

	//	Test surfaces - delete
    //CSurface::OnDraw(Surf_Display, Surf_Test, 0, 0);
	//CSurface::OnDraw(Surf_Display, Surf_Test, 100, 100, 0, 0, 50, 50);

	//	Fill whole screen with solid color
	
	SDL_Rect Rect;
	Rect.x = 0;
	Rect.y = 0;
	Rect.w = WWIDTH;
	Rect.h = WHEIGHT;

	SDL_FillRect(Surf_Display, &Rect, 0);
	
	CSurface::OnDraw(Surf_Display, Surf_Grid, 0, 0);	/*!< \brief lets actually draw the image. */

	for (int i = 0; i < 9; i++) {
		int X = (i % 3) * 200;
		int Y = (i / 3) * 200;

		if (Grid[i] == GRID_TYPE_X) {
			CSurface::OnDraw(Surf_Display, Surf_X, X, Y);
		}
		else if (Grid[i] == GRID_TYPE_O) {
			CSurface::OnDraw(Surf_Display, Surf_O, X, Y);
		}
	}

	CSurface::OnDraw(Surf_Display, Surf_Test, 290, 220, 0, Anim_Yoshi.GetCurrentFrame() * 64, 64, 64);

	for (int i = 0; i < CEntity::EntityList.size(); i++) {
		if (!CEntity::EntityList[i]) continue;

		CEntity::EntityList[i]->OnRender(Surf_Display);
	}

	CArea::AreaControl.OnRender(Surf_Display, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());
 
	// Something fixing flip
	/*
	SDL_Renderer* renderer;
	// We must call SDL_CreateRenderer in order for draw calls to affect this window.
    renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_RenderPresent(renderer);
	*/

	//Update the surface
	/*! Notice a new function here SDL_Flip. This basically refreshes the buffer and displays Surf_Display onto the screen. This is called double buffering. It's the process of drawing everything into memory, and then finally drawing everything to the screen. If we didn't do this, we would have images flickering on the screen. Remember the SDL_DOUBLEBUF flag? This is what turns double buffering on. */
	SDL_UpdateWindowSurface( window );
}
