#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Collisions.h"
#include <SDL.h>
#include <iostream>

; using namespace::std;

// Initalise the instance to null
Collisions* Collisions::mInstance = NULL;

Collisions::Collisions()
{

}

Collisions::~Collisions()
{
	mInstance = NULL;
}

Collisions* Collisions::Instance()
{
	if (!mInstance)
	{
		mInstance = new Collisions;
	}
	return mInstance;
}

bool Collisions::Circle(Character* Character1, Character* Character2)
{
	// Calculate the vector that seperates the two objects
	Vector2D vec = Vector2D((Character1->GetPosition().x - Character2->GetPosition().x),
							(Character1->GetPosition().y - Character2->GetPosition().y));

	// Length of vector
	double distance = sqrt((vec.x*vec.x) + (vec.y*vec.y));

	// Get collision radius of each character and accumulate them
	double combinedDistance = (Character1->GetCollisionRadius() + Character2->GetCollisionRadius());

	// Check if the distance is shorter than the accumulated collision radius
	return distance < combinedDistance;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
	if (rect1.x + (rect1.width / 2) > rect2.x &&
		rect1.x + (rect1.width / 2) < rect2.x + rect2.width &&
		rect1.y + (rect1.height / 2) > rect2.y &&
		rect1.y + (rect1.height / 2) < rect2.y + rect2.height)
	{
		return true;
	}
	return false;
}

