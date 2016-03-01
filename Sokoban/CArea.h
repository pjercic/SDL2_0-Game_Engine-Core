/*! \file CTile.h
    \brief Header definitions for the area.
    
    What we are going to do is have one Area object, this Area object will have many children Map objects in a vector (like the Entities in a vector). Within each of these Map objects, they will have a vector of each individual tile. So basically, we have a bunch of tiles that make up a map, and a bunch of maps make up an area.
	
	Okay, cool! I know that is quite a bit to take in at once, but don't fret! It's really not too bad once you get the hang of it. I want to say that right now we could create Map objects and render maps just fine. This would be ideal for games like Mario and Megaman, as they are just one big map. But for games like Zelda and Metroid, it won't work too well. That is where Areas come in. Just like maps having file formats, each area will have its own file and file format. Each area is going to have a tileset to load, the size of the area, and the maps that are to be loaded in each area. Here is the area we are going to be using below:

	./tilesets/1.png
	3
	./maps/1.map ./maps/1.map ./maps/1.map
	./maps/1.map ./maps/1.map ./maps/1.map
	./maps/1.map ./maps/1.map ./maps/1.map

	Save this into a file called 1.area, and save it in your maps directory. Just like maps, this area will tile maps. 
	
	\author Petar Jerčić
*/

/*! \var static CArea AreaControl
    \brief we have a static AreaControl, much like Entities have a static control. This will allow us to manipulate an Area from any class by using this object.
*/

/*! \var std::vector<CMap> MapList
    \brief Similarly, we have MapList that will hold our maps, just like the Map class had a list of tiles.
*/

/*! \var int AreaSize
    \brief we have the AreaSize which is the number of maps. We are going to assume that areas will always be square, so an AreaSize of 3, would be a 3x3 area. If you wanted to, and I don't think it's necessary, you would have AreaWidth and AreaHeight.
*/

/*! \var SDL_Surface* Surf_Tileset
    \brief Next, we have a surface for the Tileset. You probably noticed that within the CMap class we never actually loaded a tileset. That's because the Area is going to do it for us, and then pass that pointer to the CMap class. That way each map doesn't load a tileset for itself, but effectively all maps share the same tileset. Again, if you wanted each Map to have its own tileset you can easily modify the class to do so.
*/
/*! \fn bool    OnLoad(char* File, SDL_Surface*    Screen_Display)
    \brief OnLoad does what you expect, loads a map from a file, and populates the TileList.
*/

/*! \fn void void    OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY)
    \brief The OnRender also does what you expect, properly puts each tile on the screen and draws them using the Surf_Tileset.
*/

#ifndef _CAREA_H_
#define _CAREA_H_

#include "CMap.h"

class CArea {
public:
	static CArea            AreaControl;

public:
	std::vector<CMap>       MapList;

private:
	int                     AreaSize;

	SDL_Surface*        Surf_Tileset;

public:
	CArea();

	bool    OnLoad(char* File, SDL_Surface*    Screen_Display);

	void    OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY);

	void    OnCleanup();

public:
    CMap*    GetMap(int X, int Y);
 
    CTile*    GetTile(int X, int Y);
};

#endif