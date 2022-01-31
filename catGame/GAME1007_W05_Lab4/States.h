#pragma once
#ifndef _STATES_H_
#define _STATES_H_

#include <map>
#include <string>
#include <SDL_mixer.h>
#include "Items.h"
#include "player1.h"
#include "enemy.h"
#include "Background.h"
#include "Engine.h"
using namespace std;

//An abstract class is one that cannot be instantiated.
//Why? Because they'd be a base class most likely.

class State // This is the abstract base class for all state subclasses.
{
protected: //Private but inherited.
	State() = default; // Could be State() {};
public:
	virtual ~State() = default;
	virtual void Enter() = 0; // = 0 means pure virtual. Method MUST be defined in subclass.
	virtual void Update() = 0;
	virtual void Render();
	virtual void Exit() = 0;
	virtual void Resume() {};
};

class TitleState : public State
{
private:
	// map for music track goes here.
public:
	TitleState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

class PauseState : public State
{
public:
	PauseState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

class GameState : public State
{
private:
	//map for sfx.
	int stepSoundTimer = 0, turnSoundTimer = 0;
	int dashCooldown = 100, dashTimer = 0, tempSpeed = 0;
	int rockCooldown = 50;
	int spcooldown = 200;
	int itemSpawnTimer = 0;

	//modifiable variables
	int playerDamage = 1;

	double speedAcc = 1, speedy = 0, speedx = 0;
	double rockSpeed = 15;
	double dumbieTimerMax = 200;

	bool dashPressed = false;
	bool textBoxOpen = false;
	bool pauseGame = false;

	TTF_Font* font;
	char message[100] = "OWwwwww!";
	SDL_Color White;
	SDL_Surface* surfaceMessage;

	SDL_Texture* Message;
	SDL_Texture* plrTxtr;
	SDL_Texture* rockTxtr;
	SDL_Texture* dumbieTxtr;
	SDL_Texture* bgTutorial;

	vector<Rock*> playerpew;
	vector<Enemy*> dumbie;
	vector<Items*> item1;

	SDL_Rect textBoxRect;
	SDL_Rect textBoxBorder;

	Player plr1;
	Background bg1;
	Uint16 dumbietimer;

	Mix_Chunk* stepSfx;
	Mix_Chunk* turnSfx;
	Mix_Chunk* deathSfx;
	Mix_Chunk* hurtSfx;
	Mix_Chunk* powerSfx;
	map<string, Mix_Chunk*> m_sfx;

	Mix_Music* maintheme;
	map<string, Mix_Music*> m_gamemusic;


public:
	GameState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();
};

class EndState : public State
{
public:
	EndState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

};
// State* myStateArray[# of elements];
#endif
