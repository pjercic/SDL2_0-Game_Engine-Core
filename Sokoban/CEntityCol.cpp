/*! \file CEntityCol.cpp
    \brief Header definitions for the entities of our program.
    
    Finally! The next tutorial. This is the 2nd part to the SDL Collision tutorial. We'll be looking at collision events, the part we left unfinished in the last tutorial. To refresh your memory, a collision event is an event that is stored in queue after a collision has taken place. Take our recent shooter contest for an example. When the player fires a bullet, the bullet flies through the air, and then hits the enemy. The moment the bullet and the enemy collide, an event is triggered and stored in the queue. After all movement has taken place, the queue is iterated through, and events can appropriately respond. 
	
	\author Petar Jerčić
*/

#include "CEntity.h"
 
std::vector<CEntityCol> CEntityCol::EntityColList;

//! A constructor.
/*!
	Everything is simply set to 0, NULL, or some respective value.
*/
CEntityCol::CEntityCol() {
    this->EntityA = NULL;
    this->EntityB = NULL;
}
