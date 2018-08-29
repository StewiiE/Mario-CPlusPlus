#include "Texture2D.h"
#include "CharacterKoopa.h"
#include "Character.h"
#include "Constants.h"
#include <iostream>
#include <string>

using namespace::std;

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition,
	FACING startFacing, float movementSpeed)
	: Character(renderer, imagePath, map, startPosition)
{
	mFacingDirection	= startFacing;
	mMovementSpeed		= KOOPA_SPEED;
	mPosition			= startPosition;

	mInjured = false;

	mSingleSpriteWidth		= mTexture->GetWidth() / 2; // 2 sprites on this spritesheet in 1 row
	mSingleSpriteHeight		= mTexture->GetHeight();
}

CharacterKoopa::~CharacterKoopa()
{

}

void CharacterKoopa::TakeDamage()
{
	Jump();
	mInjured	   	 = true;
	mInjuredTime	 = INJURED_TIME;
}

void CharacterKoopa::Jump()
{
	if (!mJumping)
	{
		mJumpForce	= INITIAL_JUMP_FORCE;

		mJumping	= true;
		mCanJump	= false;
	}
}

void CharacterKoopa::FlipRightWayUp()
{
	if (mFacingDirection == FACING_LEFT)
	{
		mFacingDirection == FACING_RIGHT;
	}
	else if(mFacingDirection == FACING_RIGHT)
	{
		mFacingDirection == FACING_LEFT;
	}

	mInjured = false;
	Jump();
}

void CharacterKoopa::Render()
{
	// Variable to hold the left position of the sprite we want to draw
	int left = 0.0f;

	// If injured move the left position of the second image on the spritesheet
	if (mInjured)
		left = mSingleSpriteWidth;

	// Get the portion of the spritesheet you want to draw
	//								{ XPos, YPos, WidthOfSingleSprite, HeightOfSingleSprite }
	SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	// Determine where you want it drawn
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	// Then draw it facing the correct direction
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}

// To gain the benefit of the code written in the base class Update() function we need to call it
void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	if (!mInjured)
	{
		// We are not injured so move
		if (mFacingDirection == FACING_LEFT)
		{
			mKoopaMovingLeft	= true;
			mKoopaMovingRight	= false;
		}
		else if (mFacingDirection == FACING_RIGHT)
		{
			mKoopaMovingRight	= true;
			mKoopaMovingLeft		= false;
		}
	}
	else
	{
		// We should not be moving when injured
		mKoopaMovingRight = false;
		mKoopaMovingLeft  = false;

		// Count down the injurd time
		mInjuredTime -= deltaTime;

		if (mInjuredTime <= 0.0)
			FlipRightWayUp();
	}

	Character::Update(deltaTime, e);
}

bool CharacterKoopa::GetAlive()
{
	return isAlive;
}

void CharacterKoopa::SetAlive(bool alive)
{
	isAlive = alive;
}