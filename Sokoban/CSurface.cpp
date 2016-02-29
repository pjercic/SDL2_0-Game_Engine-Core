/*! \file CApp.h
    \brief Header definitions for the core of our program.
    
    Details.
	
	\author Petar Jerčić
*/

#include "CSurface.h"

//! A constructor.
/*!
	A more elaborate description of the constructor in CPP.
*/
CSurface::CSurface() {
}

//! Load image in memory
/*!
	There are a couple of important things to note here. Firstly, always remember that when you make a pointer to set it to NULL, or 0. Many problems can come along later if you fail to do this. Secondly, notice how SDL_DisplayFormat returns a new Surface, and doesn't overwrite the original. This important to remember because since it creates a new surface, we have to free the old one. Otherwise, we have a surface floating around in memory.
	
	Remember I said BMPs don't support alpha layers? Well, PNGs do!
*/
SDL_Surface* CSurface::OnLoad(char* File, SDL_Surface*    Screen_Display) {

    SDL_Surface* Surf_Return = NULL;	/*!< \brief pointer to set it to NULL, or 0. */
 
	if ((Surf_Return = IMG_Load(File)) == NULL) {	/*!< \brief Call SDL method to load images. */
		printf("Failed to load image: %s\n", SDL_GetError());
		return NULL;
	}
 
    return Surf_Return;	/*!< \brief returns a new Surface. */

}

//! Draw surfaces onto other surfaces.
/*!
	The start of the function makes sure we have valid surfaces, if we don't, return false. Next, we find SDL_Rect. This is a SDL structure that basically has four members: x, y, w, h. This, of course, creates the dimensions for a rectangle. We are only worried about where we are drawing to, not the size. So we assign X, Y coordinates to the destination surface. If you are wondering what NULL is within SDL_BlitSurface, it's another parameter for a SDL_Rect. We'll get to this later on in this lesson.
*/
bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y) {
    if(Surf_Dest == NULL || Surf_Src == NULL) {	/*!< \brief Test valid surfaces. */
		printf("Failed to draw empty surfaces!\n");
        return false;
    }
 
    SDL_Rect DestR;	/*!< \brief creates the dimensions for a rectangle. */
 
    DestR.x = X;
    DestR.y = Y;
 
    SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);	/*!< \brief blit surface */
 
    return true;
}

//! Draw a part of surfaces onto other surfaces.
/*!
	Notice that it's basically the same function as our first one, except we've added another SDL_Rect. This source rect allows use to specify what pixels from the source to copy over to the destination. If we specified 0, 0, 50, 50 as parameters for X2...H, it would only draw upper left part of the surface (a 50x50 square). 
*/
bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H) {
    if(Surf_Dest == NULL || Surf_Src == NULL) {
        return false;
    }
 
    SDL_Rect DestR;
 
    DestR.x = X;
    DestR.y = Y;
 
    SDL_Rect SrcR;
 
    SrcR.x = X2;
    SrcR.y = Y2;
    SrcR.w = W;
    SrcR.h = H;
 
    SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);
 
    return true;
}

//! Set transparent key color on BMP images
/*!
	This function first checks to see if we have a valid surface. If so, we set a color key (transparency) for a color. The first argument is the surface to apply the color key to, the second is some flags telling SDL how to perform the operation, and the third is the color to make transparent. The flags being applied are basic, the first tells SDL to apply the color key to the source (the surface being passed) and the second tells SDL to try to use RLE acceleration (basically, try to make drawing later on faster). The third argument is a little bit more complex; we are using SDL_MapRGB in order to create a color. SDL_MapRGB takes a surface, and your requested color (R, G, B), and tries to match it as close as it can to that surface. You might be thinking why this is useful. Not all surfaces have the same color palette. Remember the old NES days where there was only a few colors that could be used? Same idea here, SDL_MapRGB takes a color and matches it with the closest color on that surface palette.
*/
bool CSurface::Transparent(SDL_Surface * Surf_Dest, int R, int G, int B)
{
	if (Surf_Dest == NULL) {
		return false;
	}

	SDL_SetColorKey(Surf_Dest, SDL_TRUE, SDL_MapRGB(Surf_Dest->format, R, G, B));

	return true;
}
