#include <SDL.h>
#include <SDL_image.h>
#include <SDL_main.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include "Constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include "GameScreenManager.h"

using namespace::std;

//Globals
SDL_Window*			gWindow				= NULL;
SDL_Renderer*		gRenderer			= NULL;

GameScreenManager*	gameScreenManager;
Uint32				gOldTime;

Mix_Music*			gMusic				= NULL;


//Function Prototypes
bool InitSDL();
bool Update();
void CloseSDL();
void Render();
void LoadMusic(string path);

//Variables
int angRotation = 0;

// Flip type
SDL_RendererFlip flipType = SDL_FLIP_NONE;

int main(int argc, char* args[])
{
	//Check if SDL was set up correctly
	if (InitSDL())
	{
		//Flag to check if we wish to quit
		bool quit = false;

		// Set up the game screen manager - Start with Level1
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL1);
		gOldTime = SDL_GetTicks();

		//Game loop
		while (!quit)
		{
			Render();
			quit = Update();
		}

		LoadMusic("Music/Mario.mp3");

		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(gMusic, -1);
		}
	}

	//Close Window and free resources
	CloseSDL();

	return 0;
}

bool InitSDL()
{
	// Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initilise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//All good, so attempt to create the window
		gWindow = SDL_CreateWindow("Super Mario",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		//Did the window get created?
		if (gWindow == NULL)
		{
			//Nope
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		if (gRenderer != NULL)
		{
			//Initialise PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}

		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}

	}

	// Initialise the Mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "Mixer could not not initialise! Error: " << Mix_GetError();
		return false;
	}

	LoadMusic("Music/Mario.mp3");

	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(gMusic, -1);
	}

	return true;
}


void CloseSDL()
{
	//Release the window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Destroy the game screen manager
	delete gameScreenManager;
	gameScreenManager = NULL;

	//Release the renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	// Release music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;
}

bool Update()
{
	// Get the new time
	Uint32 newTime = SDL_GetTicks();

	//Event Handler
	SDL_Event e;

	//Get the events
	SDL_PollEvent(&e);

	//Handle any events
	switch (e.type)
	{
		//Click the 'X' to quit
	case SDL_QUIT:
		return true;
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
			case SDLK_r:
				angRotation -= 60;
				break;
			case SDLK_t:
				angRotation += 60;
				break;

			case SDLK_q:
				flipType = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_w:
				flipType = SDL_FLIP_NONE;
				break;
			case SDLK_e:
				flipType = SDL_FLIP_VERTICAL;
				break;

			case SDLK_p:
				return true;
			break;
		}
		break;

	case SDL_MOUSEBUTTONDOWN:
		switch (e.button.button)
		{
			case SDL_BUTTON_RIGHT:
				return true;
			break;
		}
		break;
	}

	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);

	// Set the current time to be the old time
	gOldTime = newTime;

	return false;
}


void Render()
{
	//Clear the screen - White
	SDL_SetRenderDrawColor(gRenderer, 0x80, 0xC0, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	gameScreenManager->Render();

	//Update the screen
	SDL_RenderPresent(gRenderer);
}

void LoadMusic(string path)
{
	gMusic = Mix_LoadMUS(path.c_str());

	if (gMusic == NULL)
	{
		cout << "Failed to load background music! Error: " << Mix_GetError() << endl;
	}
}


