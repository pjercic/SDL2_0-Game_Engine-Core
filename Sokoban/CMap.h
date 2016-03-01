/*! \file CTile.h
    \brief Header definitions for the maps.
    
    What we are going to do is have one Area object, this Area object will have many children Map objects in a vector (like the Entities in a vector). Within each of these Map objects, they will have a vector of each individual tile. So basically, we have a bunch of tiles that make up a map, and a bunch of maps make up an area.
	
	The first thing we need to consider is that our maps will be text files. So we need to come up with a file format, that way we can easily edit our maps outside of our code. And possibly later you could create a map editor.

	Each map is going to have a width and height, defining the number of tiles. So a map of 10x10, would have 100 tiles in it. We are going to make all of our maps the same width and height, so we don't have to define that within the map files (MAP_WIDTH and MAP_HEIGHT). The part that we do need to add though is the TileID and TypeID for each individual tile. We are going to use the file format that I came up with, as it is relatively simple. Take a look at the 5x5 map example below:

	0:0 0:0 0:0 0:0 0:0
	1:0 1:0 1:0 0:0 0:0
	1:0 1:0 1:0 0:0 0:0
	1:0 1:0 1:0 0:0 0:0
	1:0 1:0 1:0 0:0 0:0

	Each tile within the file would consist of 0:0, effectively being the TileID:TypeID. A space would be the deliminator between the tiles.
	
	First create a folder in the same directory as your exe called maps. This folder is where all your maps will be. Save that map as 1.map. Also, make another folder called tilesets in the same directory as your exe, and save the tileset above as 1.png.
	
	\author Petar Jerčić
*/

/*! \fn bool OnLoad(char* File)
    \brief OnLoad does what you expect, loads a map from a file, and populates the TileList.
*/

/*! \fn void OnRender(SDL_Surface* Surf_Display, int MapX, int MapY)
    \brief The OnRender also does what you expect, properly puts each tile on the screen and draws them using the Surf_Tileset.
*/

#ifndef _CMAP_H_
#define _CMAP_H_

#include <SDL.h>
#include <vector>

#include "CTile.h"
#include "CSurface.h"

class CMap {
public:
	SDL_Surface* Surf_Tileset;

private:
	std::vector<CTile> TileList;

public:
	CMap();

public:
	bool OnLoad(char* File);

	void OnRender(SDL_Surface* Surf_Display, int MapX, int MapY);

public:
    CTile*    GetTile(int X, int Y);
};

#endif