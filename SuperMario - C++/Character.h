#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "Constants.h"
#include "LevelMap.h"
#include "Texture2D.h"

using namespace::std;

class Texture2D;

class Character
{
public:
	Character(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition);
	~Character();

	virtual void	 Render();
	virtual void	 Update(float deltaTime, SDL_Event e);

	void			 SetPosition(Vector2D newPosition);
	Vector2D		 GetPosition();

	float			 GetCollisionRadius();

	bool IsJumping();
	void CancelJump();

	Rect2D GetCollisionBox();

protected:
	SDL_Renderer*	 mRenderer;
	Vector2D		 mPosition;
	Texture2D*		 mTexture;

	virtual void	 MoveLeft(float deltaTime);
	virtual void	 MoveRight(float deltaTime);
	virtual void	 KoopaMoveLeft(float deltaTime);
	virtual void	 KoopaMoveRight(float deltaTime);
	virtual void	 AddGravity(float deltaTime);
	virtual void	 Jump();

	bool			 mJumping;
	bool			 mFallOff;
	bool			 mCanJump;
	float			 mJumpForce;

	LevelMap*		 mCurrentLevelMap;

	float			 mCollisionRadius;

	bool			 mMovingLeft;
	bool			 mMovingRight;

	bool			 mKoopaMovingLeft;
	bool			 mKoopaMovingRight;

	FACING			 mFacingDirection;

	float			 mMovementSpeed;
};


#endif