/*! \file CApp_OnLoop.cpp
    \brief Code for our big loop.
    
    Details.
	\author Petar Jerčić
*/

#include "CApp.h"

void CApp::OnLoop() {

	/*	My addition, check for win	*/
	int o_num[3] = { 17, 15, 11 }; int o = 0;
	int x_num[3] = { 17, 15, 11 }; int x = 0;
	for (int i = 0; i < 9; i++) {
		if (Grid[i] == GRID_TYPE_O) {
			o_num[o] = i;
			o++;
		}
		if (Grid[i] == GRID_TYPE_X) {
			x_num[x] = i;
			x++;
		}
	}

	if ((o_num[1] - o_num[0]) / (o_num[2] - o_num[1]) == 1 || (x_num[1] - x_num[0]) / (x_num[2] - x_num[1]) == 1)
		Reset();

	/*	My addition, check for win	*/

	Anim_Yoshi.OnAnimate();	/*!< \brief now to make our animation loop. */

	/*! \brief we are basically encapsulating the basic functions of a game within the Entity class? We have to call those functions now in the respective CApp functions. 
	
	We are basically running through each Entity in our vector, and calling the OnLoop function. Simple enough! (And we're doing an error checking so we don't call any NULL pointers).*/
	for (int i = 0; i < CEntity::EntityList.size(); i++) {
		if (!CEntity::EntityList[i]) continue;

		CEntity::EntityList[i]->OnLoop();
	}
 
	/*! \brief We're already storing the collision events in a queue, now we need to do something with them. Open up CApp_OnLoop.cpp. You'll notice we already have a loop going for entities and we're calling OnLoop. We're basically going to do the same thing again. 
	
	Not much going on here. We're first iterating through every event in the queue. We then grab the two entities involved (EntityA, and EntityB), and we make sure they are valid pointers. If so, we first tell EntityA that it has collided with EntityB by calling OnCollision. Now, this is where that void to bool change comes in. EntityA can choose to prevent EntityB from knowing it has collided with him. If you remember, only Entities that are moving check for collision. This would mean EntityA is definitly a moving entity, and EntityB may or may not be moving.

	Here's an example to explain why you wouldn't want to waste time calling EntityB's OnCollision. Say you fire a bullet, and it hits a rock entity. Now, lets say the rock has a flag stating it's indestructable. Our rock doesn't care its been hit. So, when the OnCollision is called for the bullet, the bullet can see the entity it has hit is indestructable. And because of that, it can create a little "bullet being destroyed" animation, and then we can ignore telling the rock about it. */
	
	//Collision Events
	for(int i = 0;i < CEntityCol::EntityColList.size();i++) {
		CEntity* EntityA = CEntityCol::EntityColList[i].EntityA;
		CEntity* EntityB = CEntityCol::EntityColList[i].EntityB;
 
		if(EntityA == NULL || EntityB == NULL) continue;
 
		if(EntityA->OnCollision(EntityB)) {
			EntityB->OnCollision(EntityA);
		}
	}
 
	CEntityCol::EntityColList.clear();
	
	/*	Missing from tutorial - added */
	
	CFPS::FPSControl.OnLoop();

    char Buffer[255];
    sprintf(Buffer, "FPS: %d", CFPS::FPSControl.GetFPS());
	SDL_SetWindowTitle(window, Buffer);
	
	/*	Missing from tutorial - added */
}