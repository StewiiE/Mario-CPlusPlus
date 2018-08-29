#ifndef _GAME_SCREEN_LEVEL_1_H
#define _GAME_SCREEN_LEVEL_1_H
#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include "Coin.h"
#include <vector>

class Texture2D;
class Character;
class CharacterMario;
class CharacterLuigi;
class CharacterKoopa;
class PowBlock;
class LevelMap;
class Coin;

class GameScreenLevel1 : GameScreen
{
private:
	bool				SetUpLevel();
	void				SetLevelMap();
	void				DoScreenshake();

	Texture2D*			mBackgroundTexture;
	CharacterMario*		mMarioCharacter;
	CharacterLuigi*		mLuigiCharacter;
	LevelMap*			mLevelMap;
	PowBlock*           mPowBlock;
	Coin*				mCoin;
	CharacterKoopa*     mCharacterKoopa;
	
	bool				mScreenshake;
	float				mScreenshakeTime;
	float				mWobble;
	float				mBackgroundYPos;

	float				mCoinCounter;


	float Timer;

public:
	 GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void UpdatePowBlock();

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

	void UpdateCoins(float deltaTime, SDL_Event e);
	void CreateCoin(Vector2D position);

	vector<CharacterKoopa*> mEnemies;
	vector<Coin*> mCoins;
};
#endif