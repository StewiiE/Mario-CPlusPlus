#include "Coin.h"
#include <iostream>
using namespace::std;

Coin::Coin(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition) : Character(renderer, imagePath, map, startPosition)
{
	mPosition = startPosition;

	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();

}

Coin::~Coin()
{

}


void Coin::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e); 

	mFrameDelay -= deltaTime;
	if (mFrameDelay <= 0.0f)
	{
		// Reset delay
		mFrameDelay = ANIMATION_DELAY;

		// Move frame
		mCurrentFrame++;

		// Loop frame
		if (mCurrentFrame > 2)
		{
			mCurrentFrame = 0;
		}
	}
}

void Coin::Render()
{
	// Get the portion of the spritesheet you want to draw
	//								{ XPos, YPos, WidthOfSingleSprite, HeightOfSingleSprite }
	SDL_Rect portionOfSpritesheet = { mSingleSpriteWidth*mCurrentFrame, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	// Determine where you want it drawn
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
}

void Coin::SetCollected(bool collected)
{
	isCollected = collected;
}

bool Coin::GetCollected()
{
	return isCollected;
}