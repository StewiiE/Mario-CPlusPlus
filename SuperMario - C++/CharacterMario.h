#ifndef _CHARACTER_MARIO_
#define _CHARACTER_MARIO_

#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "Constants.h"
#include "LevelMap.h"
#include "Character.h"

using namespace::std;


class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition);
	~CharacterMario();

	virtual void	 Update(float deltaTime, SDL_Event e);

	void			 SetState(CHARACTERSTATES);

};

#endif