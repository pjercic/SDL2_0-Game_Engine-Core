#include "CArea.h"

CArea CArea::AreaControl;

CArea::CArea() {
	AreaSize = 0;
}

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

void CArea::OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY) {
	int MapWidth = MAP_WIDTH * TILE_WIDTH;
	int MapHeight = MAP_HEIGHT * TILE_HEIGHT;

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

void CArea::OnCleanup() {
	if (Surf_Tileset) {
		SDL_FreeSurface(Surf_Tileset);
	}

	MapList.clear();
}

CMap* CArea::GetMap(int X, int Y) {
    int MapWidth  = MAP_WIDTH * TILE_WIDTH;
    int MapHeight = MAP_HEIGHT * TILE_HEIGHT;
 
    int ID = X / MapWidth;
        ID = ID + ((Y / MapHeight) * AreaSize);
 
    if(ID < 0 || ID >= MapList.size()) {
        return NULL;
    }
 
    return &MapList[ID];
}
 
CTile* CArea::GetTile(int X, int Y) {
    int MapWidth  = MAP_WIDTH * TILE_WIDTH;
    int MapHeight = MAP_HEIGHT * TILE_HEIGHT;
 
    CMap* Map = GetMap(X, Y);
 
    if(Map == NULL) return NULL;
 
    X = X % MapWidth;
    Y = Y % MapHeight;
 
    return Map->GetTile(X, Y);
}