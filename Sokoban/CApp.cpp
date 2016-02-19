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

//! A constructor.
/*!
	A more elaborate description of the constructor in CPP.
*/
CApp::CApp() {

	CurrentPlayer = 0;

	Surf_Grid = NULL;	/*!< \brief initialize the surfaces to NULL. */
	Surf_X = NULL;
	Surf_O = NULL;

	window = NULL;
    Surf_Display = NULL;
	//Surf_Test = NULL;
 
    Running = true;
}

//! A game loop.
/*!
	You'll notice some new variables, but let's look at what is happening first. First, we try to Initialize our game, if it fails we return -1 (an error code), thus closing our program. If everything is good, we continue on to the game loop. Within the game loop we use SDL_PollEvent to check for events, and pass them one at a time to OnEvent. Once done with Events, we go to OnLoop for move data around and what not, and then render our game. We repeat this indefinitly. If the user exits the game, we proceed to OnCleanup cleaning up any resources. Simple enough.

	Now, lets look at SDL_Event and SDL_PollEvent. The first is a structure that holds information about events. The second is a function that will grab any events waiting in the queue. This queue can have any number of events, which is the reason why we have to loop through them. So, for example, lets say the user presses A and moves the mouse during the OnRender() function. SDL will detect this and put two events in the queue, one for a key press and one for a mouse move. We can grab this event from the queue by using the SDL_PollEvent, and then passing it to OnEvent to handle it accordingly. Once there are no more events in the queue, SDL_PollEvent will return false, thus exiting out of the Event queue loop.

	The other variable added, Running, is our own. This is our exit out of the game loop. When this is set to false, it will end the program, and in turn exit the program. So, for example, if the user presses the Escape key we can set this variable to false, quitting the game. 
*/
int CApp::OnExecute() {
	if (OnInit() == false) {
		printf("Failed to initialize our game");
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
