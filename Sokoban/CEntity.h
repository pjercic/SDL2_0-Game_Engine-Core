/*! \file CEntity.h
    \brief Header definitions for the entities of our program.
    
    Okay, now for some basic explanation. What we are doing here is encapsulating the basic 5 components I mentioned within the first lesson (excluding Events, which will be handled in a later lesson). This allows us to handle Entities within the game much more easily, rather than clumping them together with everything else in the game within the main CApp class. This will also be the way we handle other things as well.
	
	Now, lets go ahead and add this new Player to the game. But first, some explanation. Remember, anything that moves in the game or that can be interacted with (besides the Map), is an Entity. So, our main Player will be an entity. But, Player is distinct, he likes certain things other Entities do not. So, instead of simply doing CEntity Player; we need to create a class just for Player. But! Before we can even to get to making the Player class, we're going to need to extend the Entity class.
	
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

/*! \var float SpeedX
    \brief So, to get past this, we have six variables SpeedX, SpeedY, AccelX, AccelY, MaxSpeedX, and MaxSpeedY.
	
	Using these is simple. First, the MaxSpeed variables cap how fast the entity can go; if we didn't cap it, the Entities would continue to go faster and faster into infinity. The SpeedX and SpeedY are the current speed of the entity. If these were 1, again, that would be 1 pixel per second. Now, the AccelX and AccelY, determine how fast we increase or decrease our speed. If AccelX and AccelY are 0, then we aren't moving at all. If AccelX is 1, then our SpeedX is increasing over time. Now, this is where it gets a little confusing with the Speed factor.
*/

/*! \var static std::vector<CEntityCol>    EntityColList
    \brief List of objects that collided.
	
	So, for example, if EntityA and EntityB collide, what happens? Well, first, neither can pass through each other; that's the easy part. The other part, is that EntityA needs to know EntityB collided with him. Such as, Mario falling on a spike. The spike notifies Mario, "Hey, I killed you! Change your animation and die." Well, the thing is, we cannot notify the other entity when the collision happens. One important reason is that, if the Spike kills Mario, Mario may not have been able to notify the Goomba that he killed him. So, what we do instead is store everything in a queue. This is the new vector called CEntityColList. This stores any collision that have happened when all the entities have moved. And once all movement has taken place, that is when we'll notify all the Entities of collisions, and call OnCollision.
*/

/*! \var int Col_X
    \brief Also with this, is four Col_ variables. These variables are used to offset a collision for an entity.
	
	Back in previous tutorials we had a Yoshi image we were using. If you notice, it would make little sense to use the width of the image for collision purposes. Yoshi doesn't actually come to the edges of the images; so, we have to offset it a little, so when Yoshi runs into a wall it actually looks like his nose is hitting the wall, and not being a few pixels away. And since these variables are used to collision purposes only, I have prefixed them with Col_.
*/

/*! \var int CurrentFrameCol
    \brief Next, we have some Animation variables.
	
	There are only two of them: CurrentFrameCol, and CurrentFrameRow. These two determine where on our image we start to find individual frames of an animation. A CurrentFrameCol and CurrentFrameRow would be the top left of the image. Moving over one column would change things. Think of it like tilesets.
*/

/*! \var int Type
    \brief and the type of entity.
*/

/*! \var bool Dead
    \brief Last, but not least, we have variables to indicate if a variable is dead.
*/

/*! \var bool CanJump
    \brief Useful function can a character jump.
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

/*! \fn virtual void OnAnimate()
    \brief OnAnimate is used to define Animation States, like I mentioned earlier.
	
	This is useful for selecting the right animation when the Player moves left or right.
*/

/*! \fn virtual bool OnCollision(CEntity* Entity)
    \brief OnCollision, is called when an Entity collides with another Entity.
	
	Details.
*/

/*! \fn void    OnMove(float MoveX, float MoveY)
    \brief Now, for some movement explanation. Whenever an Entity wants to move, we do not move it to where it wants to go immediately. What we do instead, is move it in the direction we want it to go at a certain speed.
	
	Remember the whole CFPS class? That's why time based movement is so important. So, in the new OnMove function, we pass it how fast we want our Entity to go. If we want the Entity to move 1 pixel a second to the right, we would do OnMove(1, 0). Now, I wish it was this simple, but it's not. In real life we don't move in steps. We move according to speed and acceleration. Meaning, it takes us a little time to start moving at first (inertia). It looks unnatural to have entities jumping around. 
*/

/*! \fn bool     Jump()
    \brief Jump our character.
*/

/*! \fn bool    Collides(int oX, int oY, int oW, int oH)
    \brief Whew. Also, in correlation with this, is Collides function, which is used to determine the actual collision (more on this later).
	
	Details.
*/

/*! \fn bool     PosValid(int NewX, int NewY)
    \brief Brief.
	
	Before an entity is allowed to move, we have to check a few things. The first is if the entity collides with the map, and the second is if the entity collides with another entity. This is where the three PosValid functions come in. The first, PosValid(), is the main function that handles the other two. It checks to see if the tile the entity is trying to move to is valid, and also checks the entities. The other two PosValid functions determine what a valid tile is, and what a valid entity is. Again, more explanation later.
*/

#ifndef _CENTITY_H_
#define _CENTITY_H_

#include <vector>

#include "CAnimation.h"
#include "CSurface.h"
#include "CArea.h"
#include "CCamera.h"
#include "CFPS.h"

//! An enum.
/*! You'll notice we have another enum, like the Flags, to specify the type of entity. This is important when dealing with collision events. So, back to the Mario and Spike example; lets say a Goomba happens to step in a spike. Now, in Mario world, the Goomba would not die. So, the Spike needs to know that entities type. Simple enough I think. */
enum {
	ENTITY_TYPE_GENERIC = 0,

	ENTITY_TYPE_PLAYER
};

//! An enum.
/*! Now, last for movement, we have MoveLeft, MoveRight, Flags, and StopMove. Now, MoveLeft and MoveRight are simply flags, true or false, that determine if the entity is moving left or right. If true, the AccelX will be set a value, causing the entity to move. Now, StopMove simply sets the AccelX in the opposite direction until we reach 0. Again, we don't stop suddenly in real life, we gradually stop. The last item, Flags, is used to determine a few things. */
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