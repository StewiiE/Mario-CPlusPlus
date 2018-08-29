#ifndef _CHARACTER_LUIGI_
#define _CHARACTER_LUIGI_

#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "Constants.h"
#include "LevelMap.h"
#include "Character.h"

using namespace::std;

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition);
	~CharacterLuigi();

	virtual void	 Update(float deltaTime, SDL_Event e);

	void			 SetState(CHARACTERSTATES);
};

#endif