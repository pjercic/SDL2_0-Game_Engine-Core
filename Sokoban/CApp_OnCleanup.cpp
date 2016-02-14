#include "CApp.h"
 
void CApp::OnCleanup() {
	SDL_FreeSurface(Surf_Grid);
	SDL_FreeSurface(Surf_X);
	SDL_FreeSurface(Surf_O);
    SDL_FreeSurface(Surf_Test);
    SDL_FreeSurface(Surf_Display);

	for (int i = 0; i < CEntity::EntityList.size(); i++) {
		if (!CEntity::EntityList[i]) continue;

		CEntity::EntityList[i]->OnCleanup();
	}

	CEntity::EntityList.clear();

	CArea::AreaControl.OnCleanup();

	CSoundBank::SoundControl.OnCleanup();
 
	Mix_CloseAudio();

    SDL_Quit();
}
