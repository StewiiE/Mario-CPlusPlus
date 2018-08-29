#ifndef _COIN_
#define _COIN_
#include "SDL.h"
#include "Character.h"
#include <iostream>

using namespace std;

class Coin : public Character
{
private:

	float			mSingleSpriteWidth;
	float			mSingleSpriteHeight;

	float			mCurrentFrame;
	float			mFrameDelay;

	bool			isCollected = false;

public:
	Coin(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition);
	~Coin();

	void			Update(float deltaTime, SDL_Event e);
	void			Render();

	bool			GetCollected();
	void			SetCollected(bool collected);
};

#endif