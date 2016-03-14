/*! \file CEntity.cpp
    \brief Header definitions for the entities of our program.
    
    Details.
	\author Petar Jerčić
*/

#include "CEntity.h"

std::vector<CEntity*> CEntity::EntityList;

//! A constructor.
/*!
	Everything is simply set to 0, NULL, or some respective value. One thing to notice is the MaxSpeed variables. Set these to whatever you like. Usually this will depend on the particular entity that is in the game. Such as Mario will be able to move faster than a Goomba. Notice that I have grouped two classes into one file; that is okay to do sometimes!
*/
CEntity::CEntity() {
	Surf_Entity = NULL;

	X = Y = 0.0f;

	Width = Height = 0;

	//	Possibly not used - delete
	AnimState = 0;

	MoveLeft = false;
	MoveRight = false;

	Type = ENTITY_TYPE_GENERIC;

	Dead = false;
	
	/*!< These are used to determine certain properties about an entity. For example, an entity that is affected by gravity will have the ENTITY_FLAG_GRAVITY turned on. An Entity that can go through walls, will have ENTITY_FLAG_GHOST turned on. An entity that only collides with the map, and not other entities, will have ENTITY_FLAG_MAPONLY turned on. Now, notice how we have them numbered in hex. This is because we're treating the Flags in binary. This way, we can activate multiple flags at once: */
	Flags = ENTITY_FLAG_GRAVITY;

	SpeedX = 0;
	SpeedY = 0;

	AccelX = 0;
	AccelY = 0;

	MaxSpeedX = 10;
	MaxSpeedY = 10;

	CurrentFrameCol = 0;
	CurrentFrameRow = 0;

	Col_X = 0;
	Col_Y = 0;

	Col_Width = 0;
	Col_Height = 0;

	CanJump = false;
}

CEntity::~CEntity() {
}

bool CEntity::OnLoad(char* File, int Width, int Height, int MaxFrames, SDL_Surface*    Screen_Display) {
	if ((Surf_Entity = CSurface::OnLoad(File, Screen_Display)) == NULL) {
		return false;
	}

	CSurface::Transparent(Surf_Entity, 255, 0, 255);

	this->Width = Width;
	this->Height = Height;

	Anim_Control.MaxFrames = MaxFrames;

	return true;
}

//! On Loop.
/*!
	Lots of new things here. First, remember MoveLeft and MoveRight are used to indicate if the entity is moving left or right (duh). If both are these are false, we call StopMove, which will handle settings Acceleration in the reverse direction so we come to a gradual stop. Below that, if MoveLeft or MoveRight are true, we give AccelX a value. 0.5 is an arbitrary number, you probably want to mess with this until you find a value that you like. Just below that, we have a condition checking if gravity is turned on for that particular entity. If it is, we set AccelY. This will cause our entity to fall down. Again, this is whatever value you want. The larger the number, the faster you will fall. Next, below that we have our SpeedX and SpeedY. Again, we increase the Speed of the entity over time in correlation to our Speed Factor.
*/
void CEntity::OnLoop() {
	//We're not Moving
	if (MoveLeft == false && MoveRight == false) {
		StopMove();
	}

	if (MoveLeft) {
		AccelX = -0.5;
	}
	else

		if (MoveRight) {
			AccelX = 0.5;
		}

	if (Flags & ENTITY_FLAG_GRAVITY) {
		AccelY = 0.75f;
	}

	/*! I want my player to increase in speed 1 pixel per second. This would be: */
	
	SpeedX += AccelX * CFPS::FPSControl.GetSpeedFactor();
	SpeedY += AccelY * CFPS::FPSControl.GetSpeedFactor();

	if (SpeedX > MaxSpeedX)  SpeedX = MaxSpeedX;
	if (SpeedX < -MaxSpeedX) SpeedX = -MaxSpeedX;
	if (SpeedY > MaxSpeedY)  SpeedY = MaxSpeedY;
	if (SpeedY < -MaxSpeedY) SpeedY = -MaxSpeedY;

	OnAnimate();
	OnMove(SpeedX, SpeedY);
}

//! On Render.
/*!
	First, we have added the Camera X and Y to the rendering coordinates for the entity. This makes the entities render in connection to where the camera is. This way, if the camera moves, all the entities will in respect to the camera position. Next, we have added CurrentFrameCol and CurrentFrameRow to the X2 and Y2 of OnDraw. This makes it so we can set different animations.

	The first column has Yoshi facing the left, while the second column has Yoshi facing to the right. When we move to the left, we will want to set CurrentFrameCol = 0, so that Yoshi appears to be walking left. And when we move to the right, we will set CurrentFrameCol = 1, so that Yoshi appears to be walking to the right.
*/
void CEntity::OnRender(SDL_Surface* Surf_Display) {
	if (Surf_Entity == NULL || Surf_Display == NULL) return;

	CSurface::OnDraw(Surf_Display, Surf_Entity, X - CCamera::CameraControl.GetX(), Y - CCamera::CameraControl.GetY(), CurrentFrameCol * Width, (CurrentFrameRow + Anim_Control.GetCurrentFrame()) * Height, Width, Height);
}

void CEntity::OnCleanup() {
	if (Surf_Entity) {
		SDL_FreeSurface(Surf_Entity);
	}

	Surf_Entity = NULL;
}

//! On Animate.
/*!
	This is fairly straight forward. Like I said above, depending on which direction we are moving, we set the animation. 
*/
void CEntity::OnAnimate() {
	if (MoveLeft) {
		CurrentFrameCol = 0;
	}
	else

		if (MoveRight) {
			CurrentFrameCol = 1;
		}

	Anim_Control.OnAnimate();
}

//! On Collision.
/*!
	Yay, an empty function. This function will be called whenever two entities hit each other. This entire time we've been creating an class for basic entities. In order to take advantage of this function, you will need to create our own class (like CPlayer, which we'll do later on in this tutorial) and override this function. This is because the action taken by an entity depends upon it's type. Like my earlier examples, a Goomba will not react the same way to a collision with a spike as Mario would.
*/
bool CEntity::OnCollision(CEntity* Entity) {
	return true;
}

//! On Move.
/*!
	This function is quite a bit to take in. Lets see if we can straighten it all out. First, MoveX and MoveY are the where we want to move our entity. Remember up above, we call this passing our SpeedX and SpeedY. So, calling OnMove(1, 0) we would want to move 1 pixel to the right every second. At the top, we check our Speed, and if 0, we don't do anything (duh). Below that, we do something I explained earlier. We multiply MoveX and MoveY by the speed factor. This gives us the correct movement per second. Just below that, we figure out the values for two new variables, NewX and NewY. These will be our X and Y increments. Remember, I mentioned above that this method is pixel perfect, so we need to inch closer and closer to our desired position. Now, we set our NewX and NewY to our speed factor because this is how much we should use to inch closer and closer to our desired position.

	Below that, we have a seemingly infinite loop. This is where the movement magic happens and collision. First, we have a condition to check if the entity is a ghost, if it is, we increase the X and Y regardless if a collision has happened. We still call PosValid though, because this will notify entities of any collision that have taken place. Notice in PosValid we pass the current X and Y, along with adding NewX and NewY. This is where we want to go, so we check if that spot is empty.

	If the entity is not a ghost, we do normal collision. We check X and Y separatly because we may be able to move up but not forward (think jumping into a wall). If the position is valid (empty), we increase the X or Y, if not, we set SpeedX or SpeedY to 0 which causes you to immediately stop (this is as close to reality as we need, if you do run into a wall you usually stop immediately). Now, below that, we change MoveX and MoveY depending upon our NewX. Say our MoveX was 2, and our NewX was 0.5. We would slowly decrease MoveX until it reaches 0. Once it does, we have come to our desired position and we are done. The 8 if statements below check if MoveX and MoveY have reached 0, and break out of the loop.
*/
void CEntity::OnMove(float MoveX, float MoveY) {

	CanJump = false;	/*!< \brief We're going to figure out when our entity is allowed to jump. An entity is allowed to jump whenever it is touching the ground - or, in other words, whenever the entity is no longer moving on the positive Y-axis. So, at the top, we are first always going to reset CanJump to false. */

	if (MoveX == 0 && MoveY == 0) return;

	double NewX = 0;
	double NewY = 0;

	/*! Notice we multiply the AccelX by the Speed Factor. That's because we want to increase the speed 1 pixel every second. If I wanted to increase the speed 1 pixel every loop, I would leave the speed factor out of it. Now, when OnMove receives these Speed variables, it also has to figure in the speed factor: 
	
	(MoveX and MoveY are the arguments passed to OnMove). Now, the SpeedX and SpeedY only determine how fast we want to move per second. So we have to multiply it by the speed factor. A little hint for you people out there, the entire speed of the game is determined by the Speed Factor! If we changed the Speed Factor of the game, it would determine how fast anything in the games moves. Slow motion deaths anyone?

	Now, whenever an Entity moves, there are some things to consider. Say in one loop we are supposed to move the Entity 4 pixels (slow computer perhaps, or really fast entity). Now, lets say 2 pixels away there is a wall. Now, if we checked 4 pixels in front of use, we wouldn't let our guy move. But, we still want him to move as close as he can. So, to move this 2 pixel distance, we have to check every pixel along the way. Now, you might be thinking this will be slow. Well, not really. Someone with a 100 FPS who wants to move 5 pixels a second (a reasonable speed), will move less than one pixel every loop (0.05 to be exact). So, every loop, this entity moves 0.05 pixels over. That means we have 1 or 2 checks when checking for collisions for that entity. More explanation on this later when we actually implement moving. */
	MoveX *= CFPS::FPSControl.GetSpeedFactor();
	MoveY *= CFPS::FPSControl.GetSpeedFactor();

	if (MoveX != 0) {
		if (MoveX >= 0)     NewX = CFPS::FPSControl.GetSpeedFactor();
		else             NewX = -CFPS::FPSControl.GetSpeedFactor();
	}

	if (MoveY != 0) {
		if (MoveY >= 0)     NewY = CFPS::FPSControl.GetSpeedFactor();
		else             NewY = -CFPS::FPSControl.GetSpeedFactor();
	}

	while (true) {
		if (Flags & ENTITY_FLAG_GHOST) {
			PosValid((int)(X + NewX), (int)(Y + NewY)); //We don't care about collisions, but we need to send events to other entities

			X += NewX;
			Y += NewY;
		}
		else {
			
			/*! \brief Now, to run through everything we did. First, we have a flag that states if an entity can jump. When set to true, we are allowed to call the Jump function. This CanJump variable is always false, unless our feet are on the ground. Whenever we actually do want to jump, we simply set our SpeedY in the negative Y-axis direction (up). Remember, gravity is always pushing us down, but at a slow speed. So, if we have a SpeedY of -5, and a AccelY of 0.75, we'll move up for a time, gravity will kick in, and then we will eventually be pushed back down. Thus, giving the effect of a real jump. The trick here is to get the Speed and Acceleration variables just right.

			Also, as a side note, the reason we made Jump return true/false is simply for informational purposes. Meaning, when a key is pressed by the player to jump, they won't always be allowed to jump. And, if you wanted, you could do something based upon what Jump() returns. */
	
			if (PosValid((int)(X + NewX), (int)(Y))) {
				X += NewX;
			}
			else {
				SpeedX = 0;
			}

			if (PosValid((int)(X), (int)(Y + NewY))) {
				Y += NewY;
			}
			else {
				 if(MoveY > 0) {
					CanJump = true;
				}
				SpeedY = 0;
			}

		}

		MoveX += -NewX;
		MoveY += -NewY;

		if (NewX > 0 && MoveX <= 0) NewX = 0;
		if (NewX < 0 && MoveX >= 0) NewX = 0;

		if (NewY > 0 && MoveY <= 0) NewY = 0;
		if (NewY < 0 && MoveY >= 0) NewY = 0;

		if (MoveX == 0) NewX = 0;
		if (MoveY == 0) NewY = 0;

		if (MoveX == 0 && MoveY == 0)     break;
		if (NewX == 0 && NewY == 0)     break;
	}
}

//! Stop Move.
/*!
	This one is fairly straight forward. Depending on our Speed, we set the Acceleration in the reverse direction. So, if we are moving right, we set the acceleration to the left. The last if statement is simply a boundary to how slow we need to be going until we stop. If we didn't do that, it's possible that we could be stuck in a loop of moving left to right.
*/
void CEntity::StopMove() {
    if(SpeedX > 0) {
        AccelX = -1;
    }
 
    if(SpeedX < 0) {
        AccelX =  1;
    }
 
    if(SpeedX < 2.0f && SpeedX > -2.0f) {
        AccelX = 0;
        SpeedX = 0;
    }
}

bool CEntity::Jump() {
    if(CanJump == false) return false;
 
    SpeedY = -MaxSpeedY;
 
    return true;
}

//! Collides.
/*!
	Next, we have a function that determines collision of two boxes. I will say right now that this function was borrowed from Cone3D (), and then modified. If it works, why fix it?

	Anyway, lets take a look at it to see if I can help explain. At the top we define 8 variables, to define 8 sides. 4 sides are for the first object, and 4 sides are for the second object. Basically, we are doing bounding box collision:
	
	So, in a very basic sense, we want to check if two boxes have overlapped. The easiest method, is to determine if we have not collided on all 4 sides. So first, we determine the locations of all the sides: 
	
	The top and left, are the X,Y of the object, and the right and bottom, are the X+Width-1, Y+Height-1. We subtract one in order to get the true coordinate of the side.

	Next, we finally do the checking. What we do here is to check if one of the 4 sides of the first object are out of range of the second object. If one is, then we cannot possibly be colliding. But, if all 4 checks fail, we are colliding. So, if bottom1 is less than top2, that means the Bottom side of the first object is higher up on the screen then the Top of the second object: 
	
	Finally, if all checks pass, then we return true for a collision. One note, remember that the Col_ variables are used to simply offset the size of the entity. If the entity is 32 width, but we offset by 2, that means when we check collision we use the Width of 30. 
*/
bool CEntity::Collides(int oX, int oY, int oW, int oH) {
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;
 
    int tX = (int)X + Col_X;
    int tY = (int)Y + Col_Y;
 
    left1 = tX;
    left2 = oX;
 
    right1 = left1 + Width - 1 - Col_Width;
    right2 = oX + oW - 1;
 
    top1 = tY;
    top2 = oY;
 
    bottom1 = top1 + Height - 1 - Col_Height;
    bottom2 = oY + oH - 1;
 
 
    if (bottom1 < top2) return false;
    if (top1 > bottom2) return false;
 
    if (right1 < left2) return false;
    if (left1 > right2) return false;
 
    return true;
}

//! PosValid.
/*!
	Moving on we find some more fun. We have our 3 last functions, the 3 PosValid functions. Overall, this functions basically determine if a collision has taken place. Remember, earlier OnMove will call PosValid to determine if a requested position is open to move to. So, keep in mind that NewX, and NewY in these functions is where the Entity wants to move to, not where it currently is.

	Lets first look at PosValid. This function will determine any type of collision that has taken place, and return true or false. Now, this function basically has only two type of collision, Entity to Entity, and Map to Entity. That's what PosValidTile and PosValidEntity are used for. 
	
	Now, the first collision we check for is a Map Collision. This is done by first grabbing 4 variables about our Entity. Basically, we want to know all the TileIDs that this entity is over. This is done by grabbing the X (and the Col_ offset) and dividing by the TILE_SIZE. This gives us our TileID for our X. The same goes for the Y variable. These two calculations determine our StartX and StartY. Now, EndX and EndY are determined in a similiar fashion, but we want to also add the Width and Height (just like we determined sides in the Collision function above). This will give us an area of tiles that this entity is over: 
	
	Now that we have the Start and End of tiles, we simply loop through them: 
	
	Inside of this loop, this is where we check each tile to see if it's a valid tile to move into. It the tile happens to be a wall, we would set the Return variable to false, to indicate that this requested position (hence the name PosValid) is not good: 
	
	First, we do a simple check with our Flags again, this will check if we have the ENTITY_FLAG_MAPONLY flag turned on. If so, this means we're only checking collisions against the map, so we don't worry about Entity collisions. If we are checking collisions, then we jump to the loop. The loop is fairly simply, we go through the EntityList and pass each entity to the PosValidEntity, along with NewX and NewY.
*/
bool CEntity::PosValid(int NewX, int NewY) {
    bool Return = true;
 
    int StartX     = (NewX + Col_X) / TILE_SIZE;
    int StartY     = (NewY + Col_Y) / TILE_SIZE;
 
    int EndX    = ((NewX + Col_X) + Width - Col_Width - 1)         / TILE_SIZE;
    int EndY    = ((NewY + Col_Y) + Height - Col_Height - 1)    / TILE_SIZE;
 
    for(int iY = StartY;iY <= EndY;iY++) {
        for(int iX = StartX;iX <= EndX;iX++) {
            CTile* Tile = CArea::AreaControl.GetTile(iX * TILE_SIZE, iY * TILE_SIZE);
 
            if(PosValidTile(Tile) == false) {
                Return = false;
            }
        }
    }
 
    if(Flags & ENTITY_FLAG_MAPONLY) {
    }else{
        for(int i = 0;i < EntityList.size();i++) {
            if(PosValidEntity(EntityList[i], NewX, NewY) == false) {
                Return = false;
            }
        }
    }
 
    return Return;
}

//! PosValidTile.
/*!
	Notice the new function GetTile, we'll define this later on in this tutorial. But to explain it here, GetTile will return the CTile of any X and Y coordinate. After we get the tile, we pass it on to PosValidTile for it to figure out if the tile can be moved over or not. So, for a moment, jump on over to PosValidTile: 
	
	Remember the enum in CTile.h at the top? Those enums were a list of types that you could give a tile. They are used here now, to determine if a tile can be moved on or not. So, that's basically what we do here. First, if the Tile is NULL (which you should always check your pointers), we return true (meaning, yes, they can walk on this tile). Next, we check if the tile is a TILE_TYPE_BLOCK, if so, then no, the entity cannot walk on this tile. And finally, for all other types, yes, they can walk on this tile. Simple enough.
*/
bool CEntity::PosValidTile(CTile* Tile) {
    if(Tile == NULL) {
        return true;
    }
 
    if(Tile->TypeID == TILE_TYPE_BLOCK) {
        return false;
    }
 
    return true;
}

//! PosValidEntity.
/*!
	Okay, this function is actually quite simple. We do some checks first on the Entity (the Entity we are wanting to collide with) to determine that this Entity is not the same Entity we're moving (Mario cannot collide with Mario). That's the "this != Entity." It simply checks to make sure the Entities are not the same. We then check to make sure the Entity is not NULL, not Dead, and doesn't have the ENTITY_FLAG_MAPONLY flag turned on. So far, so good. If all these checks pass, then we finally pass it to the Collides function of that Entity, passing along our Entities coordinates and Width/Height (with Col_ offsets). Remember, if any part of an if statement fails, like this != Entity, none of the other code in the if statement will be executed.

	So, if the Entities do collide, finally, we use our new CEntityCol class. This will be a queue of collisions that have taken place. So, we push our Entity into EntityA, and the other Entity into EntityB, and then push it into the list. Finally, we return false, to indicate that this position is not valid.
*/
bool CEntity::PosValidEntity(CEntity* Entity, int NewX, int NewY) {
    if(this != Entity && Entity != NULL && Entity->Dead == false &&
        Entity->Flags ^ ENTITY_FLAG_MAPONLY &&
        Entity->Collides(NewX + Col_X, NewY + Col_Y, Width - Col_Width - 1, Height - Col_Height - 1) == true) {
 
        CEntityCol EntityCol;
 
        EntityCol.EntityA = this;
        EntityCol.EntityB = Entity;
 
        CEntityCol::EntityColList.push_back(EntityCol);
 
        return false;
    }
 
    return true;
}

