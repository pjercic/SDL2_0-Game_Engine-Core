/*! \file CEntity.h
    \brief Header definitions for the entities of our program.
    
    Okay, now for some basic explanation. What we are doing here is encapsulating the basic 5 components I mentioned within the first lesson (excluding Events, which will be handled in a later lesson). This allows us to handle Entities within the game much more easily, rather than clumping them together with everything else in the game within the main CApp class. This will also be the way we handle other things as well.
	\author Petar Jerčić
*/

/*! \var static std::vector<CEntity*> EntityList
    \brief he first thing you may notice is a static vector called EntityList. This vector will hold all of our entities, easily accessible through CEntity::EntityList, because it's declared as a static.
    
    I should make a special note here: we declare this EntityList within CEntity because it prevents from circular dependencies later on. An example of this is trying to get a Map to communicate with Entities, and Entities to get to communicate with the Map. Such as CMap declaring a CEntity member, and CEntity declaring a CMap member. It would cause problems on the compile level.
	
	So this vector contains all of our Entities within the game. Notice that each member of the vector is a pointer. This is because later on we are going to inherit this CEntity class for Entity specific classes. So, for example, if we were going to make a Megaman game, we would have a CMegaMan class inheriting the CEntity class. And, via polymorphism, we can store that CMegaMan class within the EntityList. This is the very reason why we declared the functions above as virtuals, and certain members as protected.
*/

/*! \var SDL_Surface* Surf_Entity
    \brief we have basic information about the Entity, common to all Entities, coordinates, dimensions, and a surface for its image.
*/

/*! \var float X
    \brief we have basic information about the Entity, common to all Entities, coordinates, dimensions, and a surface for its image.
*/

/*! \var float Y
    \brief we have basic information about the Entity, common to all Entities, coordinates, dimensions, and a surface for its image.
*/

/*! \var int Width
    \brief we have basic information about the Entity, common to all Entities, coordinates, dimensions, and a surface for its image.
*/

/*! \var int Height
    \brief we have basic information about the Entity, common to all Entities, coordinates, dimensions, and a surface for its image.
*/

/*! \fn virtual bool OnLoad(char* File, int Width, int Height, int MaxFrames, SDL_Surface*    Screen_Display)
    \brief we have a loading function that basically takes a filename, and loads the image. 
	
	By default, we have it setting a transparent color.
*/

/*! \fn virtual void OnLoop()
    \brief we have a basic OnLoop function that handles basic calculations. 
	
	Right now we are only calculating Animation. Also please note that we have only set the MaxFrames for the Animation, and left the defaults in place.
*/

/*! \fn virtual void OnRender(SDL_Surface* Surf_Display)
    \brief we have the OnRender function. 
	
	Instead of making it render to the display only, I've allowed a parameter to specify where to render this entity. This could be any surface you want. So you could, if you wanted, render one entity onto another.
*/

/*! \fn virtual void OnCleanup()
    \brief we have an OnCleanup function that restores memory and all that stuff.
*/

#ifndef _CENTITY_H_
#define _CENTITY_H_

#include <vector>

#include "CAnimation.h"
#include "CSurface.h"
#include "CArea.h"
#include "CCamera.h"
#include "CFPS.h"

enum {
	ENTITY_TYPE_GENERIC = 0,

	ENTITY_TYPE_PLAYER
};

enum {
	ENTITY_FLAG_NONE = 0,

	ENTITY_FLAG_GRAVITY = 0x00000001,
	ENTITY_FLAG_GHOST = 0x00000002,
	ENTITY_FLAG_MAPONLY = 0x00000004
};

//!  A entity class.
/*!
	Entities, for all gaming purposes, are anything that can be interacted with in any way, shape, or form. Some examples might be a monster or a treasure chest that you can open. In this sense, practically everything within the game that moves is an Entity. A rock that is part of a map, which never moves, is not an entity.
*/
class CEntity {
public:
	static std::vector<CEntity*>    EntityList;

protected:
	CAnimation      Anim_Control;

	SDL_Surface*    Surf_Entity;

public:
	float           X;
	float           Y;

	int             Width;
	int             Height;

	//	Possibly gone and needs to be deleted
	int             AnimState;

	bool        MoveLeft;
	bool        MoveRight;

protected:
    bool    CanJump;

public:
	int        Type;

	bool        Dead;
	int        Flags;

protected:
	float        SpeedX;
	float        SpeedY;

	float        AccelX;
	float        AccelY;

public:
	float        MaxSpeedX;
	float        MaxSpeedY;

protected:
	int             CurrentFrameCol;
	int             CurrentFrameRow;

protected:
	int        Col_X;
	int        Col_Y;
	int        Col_Width;
	int        Col_Height;

public:
	CEntity();

	virtual ~CEntity();

public:
	virtual bool OnLoad(char* File, int Width, int Height, int MaxFrames, SDL_Surface*    Screen_Display);

	virtual void OnLoop();

	virtual void OnRender(SDL_Surface* Surf_Display);

	virtual void OnCleanup();

	virtual void OnAnimate();

	virtual bool OnCollision(CEntity* Entity);

public:
	void    OnMove(float MoveX, float MoveY);

	void     StopMove();

public:
    bool     Jump();

public:
	bool    Collides(int oX, int oY, int oW, int oH);

private:
	bool     PosValid(int NewX, int NewY);

	bool     PosValidTile(CTile* Tile);

	bool     PosValidEntity(CEntity* Entity, int NewX, int NewY);
};

class CEntityCol {
public:
	static std::vector<CEntityCol>    EntityColList;

public:
	CEntity* EntityA;
	CEntity* EntityB;

public:
	CEntityCol();
};

#endif