/*! \file CPlayer.h
    \brief This class will be our main player and will extend our new CEntity class.
	
	I won't explain any of this other than it's overriding all the virtual functions from CEntity.
	
	\author Petar Jerčić
*/

#ifndef _CPLAYER_H_
    #define _CPLAYER_H_
 
#include "CEntity.h"
 
class CPlayer : public CEntity {
    public:
        CPlayer();
 
        bool OnLoad(char* File, int Width, int Height, int MaxFrames, SDL_Surface* Screen_Display);
 
        void OnLoop();
 
        void OnRender(SDL_Surface* Surf_Display);
 
        void OnCleanup();
 
        void OnAnimate();
 
        bool OnCollision(CEntity* Entity);
};
 
#endif