#ifndef _COLLISIONS_H
#define _COLLISIONS_H
#include <SDL.h>
#include <iostream>

using namespace std;

class Character;
class CharacterMario;
class CharacterLuigi;

class Collisions
{
public:
	~Collisions();

	static Collisions* Instance();

	bool Circle(Character* Character1, Character* Character2);

	bool Box(Rect2D rect1, Rect2D rect2);

private:
	Collisions();

	static Collisions* mInstance;
};
#endif