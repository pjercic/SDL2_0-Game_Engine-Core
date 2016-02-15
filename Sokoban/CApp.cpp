/*! \file CApp.cpp
    \brief The core of our program.
    
	The CApp class is setting the stage for our entire program. Let me step aside to take special note of how games are typically setup. Most games consist of 5 functions that handle how the game processes. These processes are typically:

	Initialize
	This function handles all the loading of data, whether it be textures, maps, NPCs, or whatever.

	Event
	This function handles all input events from the mouse, keyboard, joysticks, or other devices.

	Loop
	This function handles all the data updates, such as a NPCs moving across the screen, decreasing your health bar, or whatever

	Render
	This function handles all the rendering of anything that shows up on the screen. It does NOT handle data manipulation, as this is what the Loop function is supposed to handle.

	Cleanup
	This function simply cleans up any resources loaded, and insures a peaceful quitting of the game.

	It's important to understand that games are one gigantic loop. Within this loop we find events, update data, and render pictures.

*/

#include "CApp.h"

CApp::CApp() {

	CurrentPlayer = 0;

	Surf_Grid = NULL;
	Surf_X = NULL;
	Surf_O = NULL;

	window = NULL;
    Surf_Display = NULL;
	//Surf_Test = NULL;
 
    Running = true;
}

int CApp::OnExecute() {
	if (OnInit() == false) {
		return -1;
	}

	SDL_Event Event;	/*!< \brief The first is a structure that holds information about events. */

	while (Running) {
		while (SDL_PollEvent(&Event)) {
			OnEvent(&Event);
		}

		OnLoop();
		OnRender();
	}

	OnCleanup();

	return 0;	/*!< Get back */
}

void CApp::Reset() {
	for (int i = 0; i < 9; i++) {
		Grid[i] = GRID_TYPE_NONE;
	}
}

void CApp::SetCell(int ID, int Type)
{
	if (ID < 0 || ID >= 9) return;
	if (Type < 0 || Type > GRID_TYPE_O) return;

	Grid[ID] = Type;
}

int main(int argc, char* argv[]) {
	CApp theApp;

	return theApp.OnExecute();
}
