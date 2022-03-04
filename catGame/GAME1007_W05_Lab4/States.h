#pragma once
#ifndef _STATES_H_
#define _STATES_H_
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Engine.h"
#include "Items.h"
#include "enemy.h"
#include "Background.h"
#include "NPC.h"
#include "Util.h"

using namespace std;
//an abstract class is one that cannot be instantiated
//why because theyd be a base class most likely
class State//this is the abstract base class for all state subclasses
{
protected: //priv but inherited
		// SFX Timers

	int stepSoundTimer = 0, turnSoundTimer = 0;
	int dashCooldown = 100, dashTimer = 0, tempSpeed = 0;
	int rockCooldown = 50;
	int spcooldown = 200;
	int itemSpawnTimer = 0;
	int score = 0;
	int textBoxCounter = 0;
	int textBoxTimer = 0;
	int dummiesTimer = 0;

	bool isEzModeActive = false;
	int Noobtimer = 0;
	int ezModeCD = 3000; 	

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
	char message[100] = "Hello! Welcome To the alpha release";
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
	SDL_Texture* swamp1;
	SDL_Texture* swamp1a;
	SDL_Texture* swamp1b;
	SDL_Texture* swamp1bdown;

	SDL_Texture* DragonFlyTxt;
	SDL_Texture* vineTexture;
	SDL_Texture* FrogTxtr;
	SDL_Texture* ShroomTxtr;

	
	vector<Attack*>attack;//shoots left
	vector<Attack*>rattack;//shoots right
	vector<Rock*> playerpew;
	vector<Enemy*> dumbie;
	vector<Items*> item1;
	vector<Vines*> vine;
	vector<DragonFly*> fly;
	vector<Frog*>frog;
	vector<Frog2*>frog2;
	vector <Shroom*>shroom;

	SDL_Rect textBoxRect;
	SDL_Rect textBoxBorder;
	SDL_Rect scoreRect;
		
	Player plr1;
	NPC catDude;
	Background bg1;
	Uint16 dumbietimer;

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
	Mix_Music* maintheme;
	Mix_Chunk* dashMeow;
	State() = default;//or... State(){};
	
public:
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Render();
	virtual void Exit() = 0;
	virtual void Resume() {};
};



class TitleState : public State
{
private:
	SDL_Texture* Title;
	Mix_Music* Titletheme;
public:
	TitleState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	
};




class PauseState : public State
{
private:
	
	
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

	
	bool g_paused; // If music is paused or not
public:
	
	GameState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();

};
class Levelone : public State
{
private:

public:
	Levelone();
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
//add endstatehere
//myarray[0].Render();
#endif