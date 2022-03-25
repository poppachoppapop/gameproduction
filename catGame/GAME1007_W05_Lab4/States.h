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
	int rockCooldown = 20;
	int spcooldown = 200;
	int itemSpawnTimer = 0;
	int score = 0;
	int textBoxCounter = 0;
	int textBoxTimer = 0;
	int dummiesTimer = 0;	
	bool isEzModeActive = false;
	bool wallHitx = false;
	bool wallHity = false;
	int Noobtimer = 0;
	int ezModeCD = 3000; 
	int fadeMod = 255;
	int fadeSpeed = 5;
	bool fadeIn = false;
	bool fadeOut = false;

	bool isfreezeActive = false;
	int freezetimer = 0;
	int freezeCD = 3000;

	//modifiable variables
	int playerDamage = 1;

	int speedAcc = 1, speedy = 0, speedx = 0;
	double rockSpeed = 15;
	double dumbieTimerMax = 200;

	bool dashPressed = false;
	bool pauseGame = false;
	bool spawnDummies = false;
	bool renderTextBox = false;
	bool renderScoreBox = false;
	bool isPauseActive = false;
	
	bool titleLoading = false;
	bool lvlLoading = false;

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
	SDL_Texture* swampIsland;
	SDL_Texture* flyingMaki;
	SDL_Texture* sleepingMaki;
	SDL_Texture* resumeButton;
	SDL_Texture* restartButton;
	SDL_Texture* exitButton;
	SDL_Texture* paused;
	SDL_Texture* pauseBg;
	SDL_Texture* mainMenuButton;

	SDL_Texture* DragonFlyTxt;
	SDL_Texture* vineTexture;
	SDL_Texture* FrogTxtr;
	SDL_Texture* ShroomTxtr;

	SDL_Texture* gameOverScreen;

	vector<Attack*>ushroomatk;
	vector<Attack*>lshroomatk;
	vector<Attack*>rshroomatk;
	vector<Attack*>dshroomatk;
	vector<Attack*>attack;//shoots left frog atk
	vector<Attack*>rattack;//shoots right frog atk
	vector<Rock*> playerpew;
	vector<Enemy*> dumbie;
	vector<Items*> item1;
	vector<Vines*> vine;
	vector<DragonFly*> fly;
	vector<Frog*>frog;
	vector<Bubble*> bub;
	vector <Shroom*>shroom;

	SDL_Rect textBoxRect;
	SDL_Rect textBoxBorder;
	SDL_Rect scoreRect;
	SDL_Rect blackRect;
	SDL_Rect resumeButtonSrc, resumeButtonDst;
	SDL_Rect restartButtonSrc, restartButtonDst;
	SDL_Rect exitButtonSrc, exitButtonDst;
	SDL_Rect pausedSrc, pausedDst;
	SDL_Rect pausedBgSrc, pausedBgDst;
	SDL_Rect mainMenuButtonSrc, mainMenuButtonDst;
	SDL_Point g_mousePos;
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
	Mix_Music* swampSong;
	Mix_Chunk* beepbeep;
	Mix_Chunk* beeppew;


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
	unsigned short frameCtr, frameMax, spriteIdx, spriteMin, spriteMax;
	SDL_Texture* TitleScreen;
	Mix_Music* Titletheme;
	SDL_Rect bg1Ani;
	int state;
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
	SDL_Texture* swamp;
	SDL_Texture* swamp1;
	SDL_Texture* swamp2;
	SDL_Texture* swamp3;
	SDL_Texture* swamp4;
	SDL_Texture* swamp5;
	int areaNum = 0;
	vector<Level1Background*> bg;
	vector<SDL_Rect*> levelRect;
	SDL_Rect exitRect;
	bool loadArea = false;
	int entrance;
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
private:
	unsigned short frameCtr, frameMax, spriteIdx, spriteMin, spriteMax;
	SDL_Rect makiFlying, makiFlyingDst;
	int state;
public:
	EndState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

};
class WState : public State
{

public:
	WState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

};
//add endstatehere
//myarray[0].Render();
#endif