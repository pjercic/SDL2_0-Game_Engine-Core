/*! \file CTile.cpp
    \brief Code for the tiles.
    	
	\author Petar Jerčić
*/

#include "CTile.h"

//! A tile constructor.
/*!
	Sets IDs to zero.
*/
CTile::CTile() {
	TileID = 0;
	TypeID = TILE_TYPE_NONE;
}