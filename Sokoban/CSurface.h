/*! \file CApp.h
    \brief Header definitions for the core of our program.
    
    Details.
	
	\author Petar Jerčić
*/

/*! \fn CSurface()
    \brief A contructor for surface blitting.
	
	Elaborate details for construxctor in HEAD.
*/

/*! \fn static SDL_Surface* OnLoad(char* File, SDL_Surface* Screen_Display)
    \brief Since we already have the main surface (Surf_Display) setup and ready, we are going to need a way to draw images on it. This process is called Blitting, where we basically transfer one image onto another. But before we can do that, we have to have a way to load these images into memory. SDL offers a simple function to do this called SDL_LoadBMP.
	
	It's rather simple, SDL_LoadBMP takes a single argument, the file you want to load, and returns a surface. If the functions returns NULL, either the file is not found, corrupted, or some other error. Unfortunately, for the sake of effeciency, this method is not enough. Often the image loaded will be in a different pixel format than the display. Thus, when we draw an image to the display we can incurr performance loss, lose image colors, and the like. But, thanks to SDL, it offers a quick solution around this, SDL_DisplayFormat. This function takes a surface already loaded, and returns a new surface using the same format as the display.
*/

/*! \fn static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y)
    \brief Now that we have a way of loading surfaces into memory, we are also going to need a way to draw them onto other surfaces. Just like SDL offers a function to load images, it also offers a function to draw (blit) images: SDL_BlitSurface. Unfortunately, this function is not as easy to use as the SDL_LoadBMP, but nonetheless, it's simple enough.
	
	First of all, look at the arguments being passed to the OnDraw function. We have two surfaces, and two int variables. The first surface is the destination surface, or the surface we are going to draw on. The second surface is the source surface, or the surface we going to use to draw on another surface. Basically, we are putting Surf_Src on top of Surf_Dest. The X, Y variables is the position on the Surf_Dest where we are drawing this surface to.
*/

/*! \fn static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H)
    \brief Now lets take this process a little bit further. While it's nice and all to draw images to the screen, often we'll need to draw only parts of an image.
	
	First of all, look at the arguments being passed to the OnDraw function. We have two surfaces, and two int variables. The first surface is the destination surface, or the surface we are going to draw on. The second surface is the source surface, or the surface we going to use to draw on another surface. Basically, we are putting Surf_Src on top of Surf_Dest. The X, Y variables is the position on the Surf_Dest where we are drawing this surface to.
*/

/*! \fn static bool Transparent(SDL_Surface* Surf_Dest, int R, int G, int B)
	\brief we are going to implement transparency onto these surfaces. Basically, wherever there is pink, it will show through; we will make the pink color transparent.

	SDL offers a simple function to do this, SDL_SetColorKey. Notice 3 extra arguments being passed besides the surface. These are the 3 color values that we want to make transparent, it doesn't have to be just pink. For instance, it we wanted red to be transparent it would be 255, 0, 0.
*/

#ifndef _CSURFACE_H_
    #define _CSURFACE_H_
 
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

//!  A surface blitting class.
/*!
  A more elaborate class description.
*/
class CSurface {
    public:
        CSurface();
 
    public:
        static SDL_Surface* OnLoad(char* File, SDL_Surface*    Screen_Display);
 
        static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);

		static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H);

		static bool Transparent(SDL_Surface* Surf_Dest, int R, int G, int B);
};
 
#endif
