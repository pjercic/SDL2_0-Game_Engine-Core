#include "CMap.h"

CMap::CMap() {
	Surf_Tileset = NULL;
}

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

void CMap::OnRender(SDL_Surface* Surf_Display, int MapX, int MapY) {
	if (Surf_Tileset == NULL) return;

	int TilesetWidth = Surf_Tileset->w / TILE_WIDTH;
	int TilesetHeight = Surf_Tileset->h / TILE_HEIGHT;

	int ID = 0;

	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			if (TileList[ID].TypeID == TILE_TYPE_NONE) {
				ID++;
				continue;
			}

			int tX = MapX + (X * TILE_WIDTH);
			int tY = MapY + (Y * TILE_HEIGHT);

			int TilesetX = (TileList[ID].TileID % TilesetWidth) * TILE_WIDTH;
			int TilesetY = (TileList[ID].TileID / TilesetWidth) * TILE_HEIGHT;

			CSurface::OnDraw(Surf_Display, Surf_Tileset, tX, tY, TilesetX, TilesetY, TILE_WIDTH, TILE_HEIGHT);

			ID++;
		}
	}
}

CTile* CMap::GetTile(int X, int Y) {
    int ID = 0;
 
    ID = X / TILE_WIDTH;
    ID = ID + (MAP_WIDTH * (Y / TILE_HEIGHT));
 
    if(ID < 0 || ID >= TileList.size()) {
        return NULL;
    }
 
    return &TileList[ID];
}