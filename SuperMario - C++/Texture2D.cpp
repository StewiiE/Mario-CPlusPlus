#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>

using namespace::std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mRenderer = renderer;
	mTexture = NULL;

	int mWidth = 0;
	int mHeight = 0;
}

Texture2D::~Texture2D()
{
	//Free up the memory
	Free();

	mRenderer = NULL;
}

bool Texture2D::LoadFromFile(string path)
{
	//Remove the memory used for a previous texture
	Free();

	//Load the image
	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface != NULL)
	{
		//Colour key the image - The colour to be transparent
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));

		//Set thew dimensions
		mWidth = pSurface->w;
		mHeight = pSurface->h;

		//Create the texture from the pixels on the surface
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		if (mTexture == NULL)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}

		//Remove the loaded surface now that we have the texture
		SDL_FreeSurface(pSurface);
	}
	else
	{
		cout << "Unable to create texture from surface. Error: " << IMG_GetError() << endl;
	}

	//Return the texture
	return mTexture != NULL;
}

void Texture2D::Free()
{
	//Check if the texture exists before removing it
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
}

void Texture2D::Render(Vector2D newPosision, SDL_RendererFlip flip, double angle)
{
	//Set to where the render to texture
	SDL_Rect renderLocation = { (int)newPosision.x, (int)newPosision.y, mWidth, mHeight };

	//Render to screen
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, angle, NULL, flip);

}

void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle)
{
	//Render to screen
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);
}


