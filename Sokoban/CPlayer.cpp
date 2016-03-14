/*! \file CPlayer.cpp
    \brief This class will be our main player and will extend our new CEntity class.
	
	I won't explain any of this other than it's overriding all the virtual functions from CEntity.
	
	\author Petar Jerčić
*/

#include "CPlayer.h"
 
CPlayer::CPlayer() {
}
 
bool CPlayer::OnLoad(char* File, int Width, int Height, int MaxFrames, SDL_Surface*    Screen_Display) {
    if(CEntity::OnLoad(File, Width, Height, MaxFrames, Screen_Display) == false) {
        return false;
    }
 
    return true;
}
 
void CPlayer::OnLoop() {
    CEntity::OnLoop();
}
 
void CPlayer::OnRender(SDL_Surface* Surf_Display) {
    CEntity::OnRender(Surf_Display);
}
 
void CPlayer::OnCleanup() {
    CEntity::OnCleanup();
}
 
//! Animation
/*!
	One minor note, look at OnAnimate. In there we check our SpeedX to make a modification to our MaxFrames. Basically, if SpeedX != 0, (which means we are moving) we set our MaxFrames to 8. If we aren't moving we set it to 0. Now, remember our Yoshi animation above, it has 8 frames for walking. So, if our Speed is not 0, we make Yoshi walk, otherwise we make it look like he's standing still. This is the area where you would define other animations, like Idle, Walking, Running, Jumping, and so on.
*/
void CPlayer::OnAnimate() {
    if(SpeedX != 0) {
        Anim_Control.MaxFrames = 8;
    }else{
        Anim_Control.MaxFrames = 0;
    }
 
    CEntity::OnAnimate();
}
 
bool CPlayer::OnCollision(CEntity* Entity) {
    Jump();
 
    return true;
}