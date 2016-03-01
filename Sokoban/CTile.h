/*! \file CTile.h
    \brief Header definitions for the tiles.
    
    What we are going to do is have one Area object, this Area object will have many children Map objects in a vector (like the Entities in a vector). Within each of these Map objects, they will have a vector of each individual tile. So basically, we have a bunch of tiles that make up a map, and a bunch of maps make up an area.
	
	\author Petar Jerčić
*/

/*! \var int TileID
    \brief This is called the Tile ID.
    
    You'll notice that the very top left has an ID of 0, and going to the left it increments in 1s. By using the ID, and the size of each tile (TILE_SIZE), we can know which tile to draw to the screen.
*/

/*! \var int TypeID
    \brief The next important thing is TypeID.
    
    This determines what type of tile it is. Some examples might be, invisible (don't draw a tile), block (like a wall), or ground (player can walk on it). You can define whatever TypeIDs you want, but these are the most basic (other examples might be water, fire, ice, etc...).
*/

#ifndef _CTILE_H_
#define _CTILE_H_

#include "Define.h"

//! This lets us assign or check the TypeID, and know what it is at the same time.
/*! So if I did TypeID == TILE_TYPE_BLOCK, I would be able to notice in my code that I am checking for a block type of tile. TypeID == 2 isn't as easy to interpret. If you never used enums, think of them like const variables. The value never changes. Also, the starting value defines the rest, notice I have = 0 on TILE_TYPE_NONE. From there the rest of the variables would automatically be assigned values in increments of 1. */
enum {
	TILE_TYPE_NONE = 0,

	TILE_TYPE_NORMAL,
	TILE_TYPE_BLOCK
};

//!  This class is going to define a single tile on a map.
/*!
	In gaming terms, a tile is basically a single square graphic that we draw to the screen. Remember the animation tutorial, each frame of Yoshi could be thought of as a tile. So when I say we have a map made up of many tiles, we are taking these tiles and repeating them in a grid sequence.

	And since we have a single graphic containg all of our tiles, we only have to load one graphic, and not several for each tile. Each tile then needs some properties. The most obvious is which graphical tile to use.
*/
class CTile {
public:
	int     TileID;
	int     TypeID;

public:
	CTile();
};

#endif