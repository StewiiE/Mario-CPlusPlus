#ifndef _GAME_SCREEN_H
#define _GAME_SCREEN_H
#include <SDL.h>
#include <iostream>

using namespace std;

class GameScreen
{

public:

	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);


protected:
	SDL_Renderer* mRenderer;


};
#endif