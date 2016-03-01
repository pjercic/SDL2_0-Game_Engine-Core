#include "CMap.h"

//! A constructor.
/*!
	The constructor sets the Tileset to NULL, obviously.
*/
CMap::CMap() {
	Surf_Tileset = NULL;
}

//! Next we have the OnLoad function.
/*!
	First, we are clearing out any old tiles, that way if we load twice, it won't have double the amount of tiles, effectively loading a new map. We then open up a FileHandle, and try to open the requested map file. Now, we go through the map file and grab each tile. This is accomplished by using the two loops. The outer loop is the Y axis loop, going from the top row to the bottom row of the map file. The inner loop is the X axis loop, going from the left most tile, to the right most tile. Pay attention to how this loop works, because it is also used below in the OnRender function. It basically goes from the top left tile, to the bottom right tile, 1 tile at a time. Inside of those loops we create a temporary tile, and load the file information into it. We then push that into our TileList, effectively saving the tile. We close the filehandle, and we are done.
*/
bool CMap::OnLoad(char* File) {
	TileList.clear();

	FILE* FileHandle = fopen(File, "r");

	if (FileHandle == NULL) {
		printf("Map recieved empty handle\n");
		return false;
	}

	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			CTile tempTile;

			fscanf(FileHandle, "%d:%d ", &tempTile.TileID, &tempTile.TypeID);

			TileList.push_back(tempTile);
		}
		fscanf(FileHandle, "\n");
	}

	fclose(FileHandle);

	return true;
}

//! Next, we have the function to render a map.
/*!
	Notice the MapX and MapY arguments. These tell use where to render this map on the screen. This is useful later on for moving maps around. First in the function we check for a valid tileset, because we are going to access this tileset directly and don't want to cause a crash. We then grab the TilesetWidth and TilesetHeight in Tiles. This is important, because we need to know how many tiles a tileset contains, not its actual width and height. That way we can match up a TileID to a tileset. So, a Tileset with a Width and Height, in tiles, of 2x2, would have 4 tiles on it, but in reality it would be 32x32 pixels. So, a TileID of 0 would match the first tile, a TileID of 1 would be the next, and so on. TileIDs repeat on the next row, from left to right.
	
	After that, we do something with the Tileset. What we are doing is calculating where on the Tileset to grab the appropriate tile. This is by grabing the TileID of the tile first, and then converting that to a Tile coordinate. A little bit of explanation here. We have our 2x2 tileset, and a TileID of 1. Figuring out X, we would get 1 % 2, which would be 1 still. We when multiply that by the TILE_SIZE, and get 16. That is the correct X coordinate for the Tile. Same with the Y, we put 1 / 2, which is 0.5. Since this an integer operation, the .5 is automatically dropped. Thus we are left with 0. Which is also the correct row. Now, say we had a TileID of 2. 2 % 2 = 0, and 2 / 2 = 1. See how the X repeats in a pattern? 0, 1, 0, 1... And notice how Y increases every time it goes past the Tileset Width? 0, 0, 1, 1. I hope this is clear, as it is somewhat hard to explain.
	
	Next, we actually draw the tile to the screen using the coordinates we just calculated, and then increase the ID to go to the next tile. A little side note here, we could, for the sake of speed, create an OnRender_Cache function that would perform this same operation, but would draw to a Surface defined in the CMap class. Something like SDL_Surface* Surf_Map. Then, the OnRender function would render the Surf_Map only, and not perform any operations. But also take note that that method does not necessarely work later on when we want to animate tiles.
*/
void CMap::OnRender(SDL_Surface* Surf_Display, int MapX, int MapY) {
	if (Surf_Tileset == NULL) return;

	int TilesetWidth = Surf_Tileset->w / TILE_SIZE;
	int TilesetHeight = Surf_Tileset->h / TILE_SIZE;

	int ID = 0;

	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			if (TileList[ID].TypeID == TILE_TYPE_NONE) {
				ID++;
				continue;
			}

			int tX = MapX + (X * TILE_SIZE);
			int tY = MapY + (Y * TILE_SIZE);

			int TilesetX = (TileList[ID].TileID % TilesetWidth) * TILE_SIZE;
			int TilesetY = (TileList[ID].TileID / TilesetWidth) * TILE_SIZE;

			CSurface::OnDraw(Surf_Display, Surf_Tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);

			ID++;
		}
	}
}

CTile* CMap::GetTile(int X, int Y) {
    int ID = 0;
 
    ID = X / TILE_SIZE;
    ID = ID + (MAP_WIDTH * (Y / TILE_SIZE));
 
    if(ID < 0 || ID >= TileList.size()) {
        return NULL;
    }
 
    return &TileList[ID];
}