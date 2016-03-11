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
