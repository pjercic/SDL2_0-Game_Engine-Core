/*! \file CSoundBank.h
    \brief Header definitions for the sounds of our program.
    
    Just a little side note here about sounds. SDL_mixer treats any sound in memory as a chunk. This chunk basically contains the frequency data. What's nice about SDL_mixer is that it takes this data and sends it to the audio output, meaning it has taken care of all the hard work. So all that we have to do is load our data, from a WAV file for instance, and then send it to SDL_mixer to be played.
	
	\author Petar Jerčić
*/

/*! \var static CSoundBank           SoundControl
    \brief We have a static control object first, this lets us add sounds and play sounds from anywhere in our program.
    
    hink of this as your master control for adding/playing sounds. We then have our SoundList, this is a list of SDL mixer sounds.
*/

/*! \var std::vector<Mix_Chunk*>     SoundList
    \brief Now, a Mix_Chunk object contains the information needed to play a sound.
    
    What we will do later on is load a wav file into a Mix_Chunk object. Think of it as the sound equivalent to SDL_Surface.
*/

/*! \fn CSoundBank()
    \brief A contructor in HEAD.
	
	Elaborate details for construxctor in HEAD.
*/

/*! \fn int OnLoad(char* File)
    \brief Loading sound.
	
	Details.
*/

/*! \fn void OnCleanup()
    \brief Cleaning up sound.
	
	Details.
*/
/*! \fn void Play(int ID)
    \brief Playing sound.
	
	Details.
*/

#ifndef _CSOUNDBANK_H_
#define _CSOUNDBANK_H_
 
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
 
class CSoundBank {
    public:
        static CSoundBank           SoundControl;
 
        std::vector<Mix_Chunk*>     SoundList;
 
    public:
        CSoundBank();
 
        int OnLoad(char* File);
 
        void OnCleanup();
 
    public:
        void Play(int ID);
};
 
#endif