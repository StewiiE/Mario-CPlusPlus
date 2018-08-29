#ifndef _POW_BLOCK_
#define _POW_BLOCK_
#include "SDL.h"
#include "Texture2D.h"
#include "LevelMap.h"


class PowBlock
{
private:
	SDL_Renderer*	mRenderer;
	Vector2D		mPosition;
	Texture2D*		mTexture;
	LevelMap*		mLevelMap;

	float			mSingleSpriteWidth;
	float			mSingleSpriteHeight;

	int				mNumberOfHitsLeft;

public:
	PowBlock(SDL_Renderer* renderer, LevelMap* mLevelMap);
	~PowBlock();

	void			Render();
	void			TakeAHit();

	Rect2D GetCollisionBox();
	bool IsAvailable()			{ return mNumberOfHitsLeft > 0; }
};

#endif