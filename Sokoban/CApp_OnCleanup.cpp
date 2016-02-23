#include "CApp.h"

//! An game destructor.
/*!
	We basically quit out of SDL. You should take note that in this function is where you would free other surfaces as well. This keeps all your code centralized to the function its performing.
*/
void CApp::OnCleanup() {

    SDL_FreeSurface(Surf_Paddle);	/*!< \brief Free the surfaces. */
	SDL_FreeSurface(Surf_PaddleSmall);
	SDL_FreeSurface(Surf_Ball);
	SDL_FreeSurface(Surf_BallBreak);
	SDL_FreeSurface(Surf_Background);
    SDL_FreeSurface(Surf_Display);	/*!< \brief To keep things tidy, lets also set the Surf_Display pointer to NULL. */

	for (int i = 0; i < CEntity::EntityList.size(); i++) {
		if (!CEntity::EntityList[i]) continue;

		CEntity::EntityList[i]->OnCleanup();
	}

	CEntity::EntityList.clear();

	CArea::AreaControl.OnCleanup();

	CSoundBank::SoundControl.OnCleanup();
 
	Mix_CloseAudio();	/*!< \brief Close AUDIO. */

    SDL_Quit();	/*!< \brief Quit SDL. */
}
