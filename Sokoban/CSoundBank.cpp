/*! \file CSoundBank.cpp
    \brief Code definitions for the sounds of our program.
	
	We haven't done much with channels in this class, but the class is easily changeable to add that functionality. Basically, a channel allows you to set certain settings to certain sounds. For instance, you can set volume or panning on the first channel, so any sounds played on that channel would be affected.
	
	\author Petar Jerčić
*/

#include "CSoundBank.h"
 
CSoundBank CSoundBank::SoundControl;	/*!< \brief We have our static control. */
 
CSoundBank::CSoundBank() {	/*!< \brief our empty constructor. */
}
 
//! A sound loading function.
/*!
	We basically take the filename of the sound to be loaded, and try to load it via Mix_LoadWAV into the Mix_Chunk object. Notice I am making a temporary object first, and then throwing it into the list. At the very end of the function, I return the ID of the last inserted sound. The ID for playing this sounds later would be returned by the OnLoad function.
*/
int CSoundBank::OnLoad(char* File) {
    Mix_Chunk* TempSound = NULL;
 
    if((TempSound = Mix_LoadWAV(File)) == NULL) {
        return -1;
    }
 
    SoundList.push_back(TempSound);
 
    return (SoundList.size() - 1);
}

//! A sound cleaning function.
/*!
	next we have our cleanup function which goes through the list and frees the sound chunks. Simple enough, just like SDL_FreeSurface.
*/
void CSoundBank::OnCleanup() {
    for(int i = 0;i < SoundList.size();i++) {
        Mix_FreeChunk(SoundList[i]);
    }
 
    SoundList.clear();
}
 
//! A sound playing function.
/*!
	Lastly, we have our Play function that actually plays the sound. We pass an ID (the one we got returned from the Load function) first. We do a little boundary check to make sure the ID is valid, and then actually try to play the sound. The Mix_PlayChannel takes three arguments:

	The first specifies which channel to play the sound on, -1 means use the first available.
	The second specifies which sound chunk to play.
	The last specifies how many times to play this sound (loop). -1 would be infinite.
*/
void CSoundBank::Play(int ID) {
    if(ID < 0 || ID >= SoundList.size()) return;
    if(SoundList[ID] == NULL) return;
 
    Mix_PlayChannel(-1, SoundList[ID], 0);
}