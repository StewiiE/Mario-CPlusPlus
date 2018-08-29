#pragma once

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		y = 0.0f;
		x = 0.0f;
	}

	Vector2D(float initialY, float initialX)
	{
		x = initialX;
		y = initialY;
	}
};

struct Rect2D
{
	float x;
	float y;
	float width;
	float height;

	Rect2D(float initialX, float initialY, float initialWidth, float initialHeight)
	{
		x = initialX;
		y = initialY;
		width = initialWidth;
		height = initialHeight;
	}
};

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};

enum CHARACTERSTATES
{
	CHARACTERSTATE_PLAYER_ALIVE = 0,
	CHARACTERSTATE_PLAYER_DEATH
};