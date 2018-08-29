#ifndef _GAME_SCREEN_MANAGER_H
#define _GAME_SCREEN_MANAGER_H
#include <SDL.h>
#include "Commons.h"

class GameScreen;

class GameScreenManager
{
private:
	SDL_Renderer* mRenderer;
	GameScreen* mCurrentScreen;

public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS newScreen);

};
#endif
