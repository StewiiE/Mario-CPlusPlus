#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"


using namespace::std;

Character::Character(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition)
{
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);

	mPosition = startPosition;
	mFacingDirection = FACING_RIGHT;

	mMovingLeft = false;
	mMovingRight = false;

	mKoopaMovingLeft = false;
	mKoopaMovingRight = false;

	mCurrentLevelMap = map;

	mCollisionRadius = 15.0f;
}

Character::~Character()
{
	mRenderer = NULL;
}

void Character::Render()
{
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{

	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if (mMovingRight)
	{
		MoveRight(deltaTime);
	}

	if (mKoopaMovingLeft)
	{
		KoopaMoveLeft(deltaTime);
	}
	else if (mKoopaMovingRight)
	{
		KoopaMoveRight(deltaTime);
	}


	// Deal with jumping first
	if (mJumping)
	{
		// Adjust the position
		mPosition.y -= mJumpForce*deltaTime;

		// Reduce the jump force
		mJumpForce -= JUMP_FORCE_DECREMENT*deltaTime;

		// Has the jump force reduced to zero?
		if (mJumpForce <= 0.0f)
			mJumping = false;
	}

	if (mFallOff)
	{
		// Adjust the position
		mPosition.y -= mJumpForce*deltaTime;

		// Reduce the jump force
		mJumpForce -= JUMP_FORCE_DECREMENT*deltaTime;

		// Has the jump force reduced to zero?
		//if (mJumpForce <= 0.0f)
			mJumping = false;
	}

	// Collision position variables
	int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth()*0.5)) / TILE_WIDTH;
	int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;

	// Deal with gravity
	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		// Collided with ground so we can jump
		mCanJump = true;
	}

}
	
Rect2D Character::GetCollisionBox() 
{ 
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight()); 
}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}

void Character::MoveLeft(float deltaTime)
{
	mMovingLeft = true;
	mPosition.x -= MARIO_SPEED*deltaTime;
	mFacingDirection = FACING_LEFT;
}

void Character::MoveRight(float deltaTime)
{
	mMovingRight = true;
	mPosition.x += MARIO_SPEED*deltaTime;
	mFacingDirection = FACING_RIGHT;
}

void Character::KoopaMoveLeft(float deltaTime)
{
	mKoopaMovingLeft = true;
	mPosition.x -= KOOPA_SPEED*deltaTime;
	mFacingDirection = FACING_LEFT;
}

void Character::KoopaMoveRight(float deltaTime)
{
	mKoopaMovingRight = true;
	mPosition.x += KOOPA_SPEED*deltaTime;
	mFacingDirection = FACING_RIGHT;
}

void Character::AddGravity(float deltaTime)
{
	mPosition.y += GRAVITY * deltaTime;
	mCanJump = false;
}

void Character::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}

}

float Character::GetCollisionRadius()
{
	return mCollisionRadius;
}

bool Character::IsJumping()
{
	return mJumping;
}

void Character::CancelJump()
{
	mJumping = false;
}
