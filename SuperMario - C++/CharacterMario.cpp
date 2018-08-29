#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"
#include "CharacterMario.h"


CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition) : Character(renderer, imagePath, map, startPosition)
{

}

CharacterMario::~CharacterMario()
{
	mRenderer = NULL;
}


void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	//Handle any events
	switch (e.type)
	{
		//Click the 'X' to quit
		//case SDL_QUIT:
		//	return true;
		//	break;

	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			mMovingLeft = true;
			mFacingDirection = FACING_LEFT;
			break;
		case SDLK_d:
			mMovingRight = true;
			mFacingDirection = FACING_RIGHT;
			break;
		case SDLK_w:
			Jump();
			break;
		default:
			break;
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			mMovingLeft = false;
			break;
		case SDLK_d:
			mMovingRight = false;
			break;
		default:
			break;
		}
		break;
	}
}

void CharacterMario::SetState(CHARACTERSTATES state)
{
	if (state == CHARACTERSTATE_PLAYER_DEATH)
	{
		cout << "DEAD!" << endl;
		mFallOff = true;
		Jump();
	}
}
