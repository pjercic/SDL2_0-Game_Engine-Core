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

	Anim_Yoshi.OnAnimate();

	for (int i = 0; i < CEntity::EntityList.size(); i++) {
		if (!CEntity::EntityList[i]) continue;

		CEntity::EntityList[i]->OnLoop();
	}
 
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