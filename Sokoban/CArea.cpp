/*! \file CTile.h
    \brief Code for the area.
    
   Details. 
	
	\author Petar Jerčić
*/

#include "CArea.h"


CArea CArea::AreaControl;	/*!< \brief we declare the static object. */

//! A constructor.
/*!
	and then set the AreaSize to 0. 
*/
CArea::CArea() {
	AreaSize = 0;
}

//! Then we have our Load function.
/*!
	It works just like the Load function within CMap, except there are a few differences. We have to load tileset first. We try to load this tileset into the surface, and if it fails return false. We then load the size of the Area. Okay, after that we have two loops, just like maps, that will go through and grab each map filename. It will then create a map object, load the map, set the tileset to be used, and then push it into the list. Pretty simply and straight forward.
*/
bool CArea::OnLoad(char* File, SDL_Surface*    Screen_Display) {
	MapList.clear();

	FILE* FileHandle = fopen(File, "r");

	if (FileHandle == NULL) {
		printf("Area recieved empty handle\n");
		return false;
	}

	char TilesetFile[255];

	fscanf(FileHandle, "%s\n", TilesetFile);

	if ((Surf_Tileset = CSurface::OnLoad(TilesetFile, Screen_Display)) == false) {
		printf("Area failedto load tielset\n");
		fclose(FileHandle);

		return false;
	}

	fscanf(FileHandle, "%d\n", &AreaSize);

	for (int X = 0; X < AreaSize; X++) {
		for (int Y = 0; Y < AreaSize; Y++) {
			char MapFile[255];

			fscanf(FileHandle, "%s ", MapFile);

			CMap tempMap;
			if (tempMap.OnLoad(MapFile) == false) {
				printf("Area failed to open map file\n");
				fclose(FileHandle);

				return false;
			}

			tempMap.Surf_Tileset = Surf_Tileset;

			MapList.push_back(tempMap);
		}
		fscanf(FileHandle, "\n");
	}

	fclose(FileHandle);

	return true;
}

//! Next, we have the Render function.
/*!
	We calculate the actual Map width and height, in pixels, first. This will let us find the first map to render. Some explanation first of what I am trying to do. Since an area can be of any size, like 100x100 maps, we don't want to go through all the trouble and render every single map. We only want to render the maps that are visible in the screen area. For our size of a screen, 640x480, only a possible 4 maps can be visible at one time (like standing at the corner of 4 maps). So what we have to do is calculate the first Map ID to grab. This is going to the first map to render. From the first ID, we know the next 3 maps to render. The one to the right of the first map, the one at the bottom of the first map, and the one at the bottom right of the first map.
	
	We have a guy, the circle, in the very center of the screen, represented by the red square. The other squares are each Map, and we have a Camera position of -700, -700. Why negative? Think about it, the screen itself never really moves, everything else does. So, for something to move up, it must increase its Y in the negative direction. Same with the X coordinate. So, to get to the 4th map, we have to move the area in the negative direction. Now, notice the grayed out maps, these are maps not visible within the players view, so they shouldn't be rendered. To figure out the First ID, which is 4 in this case, we need to use the specified Camera coordinates. We translate those Camera coordinates into Map coordinates. So, taking -(-700) / 640 (which is 40 * 16, remember the MapWidth calculation done above) we get 1 (dropping the decimal because its an integer operation). This is the X coordinate in Maps, but we aren't done. We then calculate the Y coordinate in Maps the same way -(-700) / 640, but we multiply that by the AreaSize. That's because we are grabbing the ID. So, it would become 1 * 3, which is 3, and adding that to the first calculation of 1, we get 4. And what do you know, the First ID on the map!

	Okay, so we go through each of the four maps now. Since I did a regular loop of i < 4, we need to figure out how to add that to the First ID, to actually figure out each of the four Map IDs. This is done by taking the First ID as an offset first. We then take i, our position in the loop, divide by two and multiply by the area size. What does this do? Much like the Map class, it creates a pattern, 0, 0, 1, 1. Same with the last operation i % 2, it creates a pattern of 0, 1, 0, 1. This then gives us the correct pattern of, 4, 5, 7, 8. Which are the correct map to render.

	We do a little check to make sure the ID is good, since the ID may not exist. And now the last calculation (yes, I know, a lot of complex calculations). It works just like the way we calculated which tile to grab on the tileset. It's turning an ID into actual pixel coordinates, and then offsetting those coordinates by the camera (making it seem like it moved). We then finally render the map, passing the coordinates of where to draw it.
*/
void CArea::OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY) {
	int MapWidth = MAP_WIDTH * TILE_SIZE;
	int MapHeight = MAP_HEIGHT * TILE_SIZE;

	int FirstID = -CameraX / MapWidth;
	FirstID = FirstID + ((-CameraY / MapHeight) * AreaSize);

	for (int i = 0; i < 4; i++) {
		int ID = FirstID + ((i / 2) * AreaSize) + (i % 2);

		if (ID < 0 || ID >= MapList.size()) continue;

		int X = ((ID % AreaSize) * MapWidth) + CameraX;
		int Y = ((ID / AreaSize) * MapHeight) + CameraY;

		MapList[ID].OnRender(Surf_Display, X, Y);
	}
}

//! Lastly, we have our cleanup function that frees the surface and clears the maps.
/*!
	Details.
*/
void CArea::OnCleanup() {
	if (Surf_Tileset) {
		SDL_FreeSurface(Surf_Tileset);
	}

	MapList.clear();
}

//! Get the current map
/*!
	Now, how it works is first by determining the size of our maps. We then translate our X,Y into an ID, and then return the CMap pointer. I won't go into how translating X,Y into an ID works, because I believe this is explained in the last tutorial.
*/
CMap* CArea::GetMap(int X, int Y) {
    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;
 
    int ID = X / MapWidth;
        ID = ID + ((Y / MapHeight) * AreaSize);
 
    if(ID < 0 || ID >= MapList.size()) {
        return NULL;
    }
 
    return &MapList[ID];
}
 
//! Get the current tile
/*!
	We do a simple check for a NULL pointer (hint, hint), and then turn our X and Y into Tile coordinates. So, if our TILE_SIZE was 16, and our X was at 128, our Tile coordinate for X would be 8. Meaning, we are 8 tiles over. We finally then send this over to the Map GetTile. (Oh yes, one other function). This is why we have a GetMap function, if you are wondering. Rememember, CArea is a bunch of maps making one big area. So, we will have to determine which map is needed when grabbing tiles.
*/
CTile* CArea::GetTile(int X, int Y) {
    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;
 
    CMap* Map = GetMap(X, Y);
 
    if(Map == NULL) return NULL;
 
    X = X % MapWidth;
    Y = Y % MapHeight;
 
    return Map->GetTile(X, Y);
}