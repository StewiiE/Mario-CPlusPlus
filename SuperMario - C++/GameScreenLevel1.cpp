#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "LevelMap.h"
#include "Collisions.h"
#include "PowBlock.h"
#include "Texture2D.h"
#include "CharacterKoopa.h"
#include "Collisions.h"
#include "Constants.h"
#include <iostream>

using namespace::std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete mMarioCharacter;
	mMarioCharacter = NULL;

	delete mLuigiCharacter;
	mLuigiCharacter = NULL;

	delete mPowBlock;
	mPowBlock = NULL;

	delete mCharacterKoopa;
	mCharacterKoopa = NULL;

	mEnemies.clear();
	mCoins.clear();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	Timer -= deltaTime;

	if (Timer <= 0.0f)
	{
		CreateKoopa(Vector2D(160, 10), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(255, 80), FACING_RIGHT, KOOPA_SPEED);

		CreateKoopa(Vector2D(160, 470), FACING_LEFT, KOOPA_SPEED);
		CreateKoopa(Vector2D(255, 390), FACING_LEFT, KOOPA_SPEED);

		CreateKoopa(Vector2D(30, 410), FACING_LEFT, KOOPA_SPEED);
		CreateKoopa(Vector2D(30, 67), FACING_RIGHT, KOOPA_SPEED);

		Timer = KOOPA_RESPAWN_TIMER;
	}

	// Do the screen shake if required
	if (mScreenshake)
	{
		mScreenshakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		// End the shake after the duration
		if (mScreenshakeTime <= 0.0f)
		{
			mScreenshake		= false;
			mBackgroundYPos		= 0.0f;
		}
	}

	UpdatePowBlock();
	UpdateCoins(deltaTime, e);
	UpdateEnemies(deltaTime, e);

	// Update Mario
	mMarioCharacter->Update(deltaTime, e);

	// Update Luigi
	mLuigiCharacter->Update(deltaTime, e);

	if (Collisions::Instance()->Circle(mMarioCharacter, mLuigiCharacter))
	{

	}
	if (Collisions::Instance()->Box(mMarioCharacter->GetCollisionBox(), mLuigiCharacter->GetCollisionBox()))
	{
	
	}

}

void GameScreenLevel1::Render()
{
	// Draw the enemies
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}

	 // Draw the coins
	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render();
	}

	// Draw the background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);
	mMarioCharacter->Render();
	mLuigiCharacter->Render();
	mPowBlock->Render();
}

bool GameScreenLevel1::SetUpLevel()
{
	// Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/ForegroundMB.png"))
	{
		cout << "Failed to load background tecture!";
		return false;
	}

	SetLevelMap();

	// Set up the player character
	mMarioCharacter = new CharacterMario(mRenderer, "Images/Mario.png", mLevelMap, Vector2D(40, 220));
	mLuigiCharacter = new CharacterLuigi(mRenderer, "Images/Luigi.png", mLevelMap, Vector2D(40, 300));

	// Floor
	CreateCoin(Vector2D(345, 70));
	CreateCoin(Vector2D(345, 425));

	// Lower platforms
	CreateCoin(Vector2D(250, 165));
	CreateCoin(Vector2D(250, 330));

	// Mid platforms
	CreateCoin(Vector2D(100, 470));
	CreateCoin(Vector2D(100, 25));
	CreateCoin(Vector2D(130, 248));

	// Upper platforms
	CreateCoin(Vector2D(35, 165));
	CreateCoin(Vector2D(35, 330));

	// Set up our POW block
	mPowBlock = new PowBlock(mRenderer, mLevelMap);


	mScreenshake = false;
	mBackgroundYPos = 0.0f;

	return true;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = 
									{ { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									{ 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
									{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
									{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
									{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
									{ 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
									{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
									{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } };

	// Clear up any old map
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	// Set the new one
	mLevelMap = new LevelMap(map);
}

void GameScreenLevel1::UpdatePowBlock()
{
	if (Collisions::Instance()->Box(mMarioCharacter->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		if (mPowBlock->IsAvailable())
		{
			// Collided whilst jump
			if (mMarioCharacter->IsJumping())
			{
				for (unsigned int i = 0; i < mEnemies.size(); i++)
				{
					mEnemies[i]->TakeDamage();
				}

				DoScreenshake();
				mPowBlock->TakeAHit();
				mMarioCharacter->CancelJump();
				//mCoinCounter++;
			}
		}
	}

	if (Collisions::Instance()->Box(mLuigiCharacter->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		if (mPowBlock->IsAvailable())
		{
			// Collided whilst jump
			if (mLuigiCharacter->IsJumping())
			{
				for (unsigned int i = 0; i < mEnemies.size(); i++)
				{
					mEnemies[i]->TakeDamage();
				}

				DoScreenshake();
				mPowBlock->TakeAHit();
				mLuigiCharacter->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::DoScreenshake()
{
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
	mMarioCharacter->CancelJump();
	mLuigiCharacter->CancelJump();
	
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	// UPDATE THE ENEMIES
	if (!mEnemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			//Check if the enemy is on the bottom row of tiles
			if (mEnemies[i]->GetPosition().y > 300.0f)
			{
				// Is the enemy off screen to the left / right?
				if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().width*0.5f) || mEnemies
					[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width*0.55f))
				{
					mEnemies[i]->SetAlive(false);
				}
			}

			// Now do the update
			mEnemies[i]->Update(deltaTime, e);

			// Check to see if the enemy collides with the player
			if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) && (mEnemies[i]
				->GetPosition().x < 64.0f || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				// Ignore the collisions if the enemy is behind a pipe?
			}
			else
			{
				if (Collisions::Instance()->Circle(mEnemies[i], mMarioCharacter))
					mMarioCharacter->SetState(CHARACTERSTATE_PLAYER_DEATH);

				if (Collisions::Instance()->Circle(mEnemies[i], mLuigiCharacter))
					mLuigiCharacter->SetState(CHARACTERSTATE_PLAYER_DEATH);
			}

			// If the enemy is no longer alive, then schedule it for deletion
			if (!mEnemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		// REMOVE DEAD ENEMIES - 1 EACH UPDATE
		if (enemyIndexToDelete != -1)
		{
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event e)
{
	if (!mCoins.empty())
	{
		int coinIndexToDelete = -1;
		for (unsigned int i = 0; i < mCoins.size(); i++)
		{
			mCoins[i]->Update(deltaTime, e);

			if (Collisions::Instance()->Circle(mCoins[i], mMarioCharacter))
			{
				mCoins[i]->SetCollected(true);
			}

			if (Collisions::Instance()->Circle(mCoins[i], mLuigiCharacter))
			{
				mCoins[i]->SetCollected(true);
			}

			if (mCoins[i]->GetCollected())
			{
				coinIndexToDelete = i;
			}
		}

		// Remove deleted coins
		if (coinIndexToDelete != -1)
		{
			mCoins.erase(mCoins.begin() + coinIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	mEnemies.push_back(new CharacterKoopa(mRenderer, "Images/Koopa.png", mLevelMap, position, direction, KOOPA_SPEED));
}

void GameScreenLevel1::CreateCoin(Vector2D position)
{
	mCoins.push_back(new Coin(mRenderer, "Images/Coin.png", mLevelMap, position));
}


