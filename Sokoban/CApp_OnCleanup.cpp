#include "CApp.h"

//! An game destructor.
/*!
	We basically quit out of SDL. You should take note that in this function is where you would free other surfaces as well. This keeps all your code centralized to the function its performing.
*/
void CApp::OnCleanup() {
	SDL_FreeSurface(Surf_Grid);	/*!< \brief Free the surfaces. */
	SDL_FreeSurface(Surf_X);
	SDL_FreeSurface(Surf_O);
    SDL_FreeSurface(Surf_Test);
    SDL_FreeSurface(Surf_Display);	/*!< \brief To keep things tidy, lets also set the Surf_Display pointer to NULL. */

	/*! \brief we are basically encapsulating the basic functions of a game within the Entity class? We have to call those functions now in the respective CApp functions. 
	
	We are basically running through each Entity in our vector, and calling the OnLoop function. Simple enough! (And we're doing an error checking so we don't call any NULL pointers).*/
	for (int i = 0; i < CEntity::EntityList.size(); i++) {
		if (!CEntity::EntityList[i]) continue;

		CEntity::EntityList[i]->OnCleanup();
	}

	CEntity::EntityList.clear();

	CArea::AreaControl.OnCleanup();

	CSoundBank::SoundControl.OnCleanup();	/*!< \brief To tidy things up, we need to make sure we stop the SDL_mixer service when we are done, as well as freeing any sounds we may have loaded. */
 
	Mix_CloseAudio();	/*!< \brief Close AUDIO. */

    SDL_Quit();	/*!< \brief Quit SDL. */
}
