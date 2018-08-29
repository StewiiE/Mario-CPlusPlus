#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"
#include "CharacterLuigi.h"



CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition) : Character(renderer, imagePath, map, startPosition)
{

}

CharacterLuigi::~CharacterLuigi()
{
	mRenderer = NULL;
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
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
		case SDLK_LEFT:
			mMovingLeft = true;
			mFacingDirection = FACING_LEFT;
			break;
		case SDLK_RIGHT:
			mMovingRight = true;
			mFacingDirection = FACING_RIGHT;
			break;
		case SDLK_UP:
			Jump();
			break;
		default:
			break;
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mMovingLeft = false;
			break;
		case SDLK_RIGHT:
			mMovingRight = false;
			break;
		default:
			break;
		}
		break;
	}
}

void CharacterLuigi::SetState(CHARACTERSTATES state)
{
	if (state == CHARACTERSTATE_PLAYER_DEATH)
	{
		cout << "DEAD!" << endl;
		mFallOff = true;
		Jump();
	}
}