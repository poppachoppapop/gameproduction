#pragma once
#ifndef _STATES_H_
#define _STATES_H_

#include <map>
#include <string>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "enemy.h"
#include "Items.h"
#include "NPC.h"
#include "player1.h"
#include "Background.h"
#include "Engine.h"
using namespace std;

class State // This is the abstract base class for all state subclasses.
{
protected: //Private but inherited.
	State() = default; // Could be State() {};
	Mix_Music* m_titlesong;
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
	map<string, Mix_Music*> m_titlemusic;
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

class TutorialState : public State
{
private:
	//Textures
		// SFX Timers
	const Uint8* m_keystates;
	int stepSoundTimer = 0, turnSoundTimer = 0;
	int dashCooldown = 100, dashTimer = 0, tempSpeed = 0;
	int rockCooldown = 50;
	int spcooldown = 200;
	int itemSpawnTimer = 0;
	int score = 0;
	int textBoxCounter = 0;
	int textBoxTimer = 0;
	int dummiesTimer = 0;
	//modifiable variables
	int playerDamage = 1;

	double speedAcc = 1, speedy = 0, speedx = 0;
	double rockSpeed = 15;
	double dumbieTimerMax = 200;

	bool dashPressed = false;
	bool pauseGame = false;
	bool spawnDummies = false;
	bool renderTextBox = false;
	bool renderScoreBox = false;

	TTF_Font* font;
	char message[100] = "Hello! Welcome To the First Playable";
	char scoreMessage[100] = "Score: 0";
	SDL_Color White;
	SDL_Surface* dummyScore;
	SDL_Surface* surfaceMessage;

	string tempStr = "Score: ";

	SDL_Texture* Message;
	SDL_Texture* Score;
	SDL_Texture* npcTxtr;
	SDL_Texture* plrTxtr;
	SDL_Texture* rockTxtr;
	SDL_Texture* dumbieTxtr;
	SDL_Texture* bgTutorial;

	vector<Rock*> playerpew;
	vector<Enemy*> dumbie;
	vector<Items*> item1;

	SDL_Rect textBoxRect;
	SDL_Rect textBoxBorder;
	SDL_Rect scoreRect;

	Player plr1;
	NPC catDude;
	Background bg1;
	Uint16 dumbietimer;


	//map for sfx.
	Mix_Chunk* stepSfx;
	Mix_Chunk* turnSfx;
	Mix_Chunk* deathSfx;
	Mix_Chunk* hurtSfx;
	Mix_Chunk* powerSfx;
	Mix_Chunk* talk;
	Mix_Chunk* winscore;
	Mix_Chunk* hehe;
	Mix_Chunk* projectileRock;
	Mix_Chunk* aoeSound;
	Mix_Chunk* dashing;
	Mix_Chunk* dashMeow;
	map<string, Mix_Chunk*> m_sfx;

	//map for music track.
	Mix_Music* gametheme;
	map<string, Mix_Music*> m_gamemusic;
public:
	TutorialState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();
	bool KeyDown(SDL_Scancode c);
	bool KeyUp(SDL_Scancode c);

};



// State* myStateArray[# of elements];
#endif