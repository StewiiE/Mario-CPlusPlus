#ifndef _Character_Koopa_
#define _Character_Koopa_

#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "Constants.h"
#include "LevelMap.h"
#include "Texture2D.h"
#include "Character.h"

using namespace::std;

class Texture2D;	

class CharacterKoopa : public Character
{
private:
	float	 mSingleSpriteWidth;
	float	 mSingleSpriteHeight;
	bool	 mInjured;
	float	 mInjuredTime;

	void FlipRightWayUp();

public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacing, float movementSpeed);
	~CharacterKoopa();

	void			 TakeDamage();
	void			 Jump();
	virtual void	 Update(float deltaTime, SDL_Event e);
	void			 Render();
	bool			 GetAlive();
	void			 SetAlive(bool alive);

	bool			 isAlive = true;
};

#endif