#ifndef _TEXTURE_2D_H
#define _TEXTURE_2D_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_main.h>
#include <iostream>
#include "Commons.h"

using namespace::std;

class Texture2D
{
public:

	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	bool LoadFromFile(string path);
	void Free();
	void Render(Vector2D newPosision, SDL_RendererFlip flip, double angle = 0.0f);
	void Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle = 0.0f);

	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }

private:

	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};

#endif //_TEXTURE_2D_H
