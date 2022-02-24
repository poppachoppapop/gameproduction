#pragma once
#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "player1.h"
#include <vector>
#include <ctime>
#include <string>
#include "enemy.h"
#include "Items.h"
#include "Background.h"
#include "NPC.h"
#define FPS 60
#define WIDTH 1024
#define HEIGHT 768
#define SPEED 10

using namespace std;

class Engine
{
private: // private propeties.
	bool m_running = false;
	Uint32 m_start, m_end, m_delta, m_fps;
	const Uint8* m_keystates;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	
	//// SFX Timers
	//int stepSoundTimer = 0, turnSoundTimer = 0;
	//int dashCooldown = 100, dashTimer = 0 , tempSpeed = 0;
	//int rockCooldown = 50;
	//int spcooldown = 200;
	//int itemSpawnTimer = 0;
	//int score = 0;
	//int textBoxCounter = 0;
	//int textBoxTimer = 0;
	//int dummiesTimer = 0;

	////modifiable variables
	//int playerDamage = 1;

	//double speedAcc = 1, speedy = 0, speedx = 0;
	//double rockSpeed = 15;
	//double dumbieTimerMax = 200;
	//
	//bool dashPressed = false;
	//bool pauseGame = false;
	//bool spawnDummies = false;
	//bool renderTextBox = false;
	//bool renderScoreBox = false;

	//TTF_Font* font;
	//char message[100] = "Hello! Welcome To the First Playable";
	//char scoreMessage[100] = "Score: 0";
	//SDL_Color White;
	//SDL_Surface* dummyScore;
	//SDL_Surface* surfaceMessage;

	//string tempStr = "Score: ";
	//
	//SDL_Texture* Message;
	//SDL_Texture* Score;
	//SDL_Texture* npcTxtr;
	//SDL_Texture* plrTxtr;
	//SDL_Texture* rockTxtr;
	//SDL_Texture* dumbieTxtr;
	//SDL_Texture* bgTutorial;

	//vector<Rock*> playerpew;
	//vector<Enemy*> dumbie;
	//vector<Items*> item1;

	//SDL_Rect textBoxRect;
	//SDL_Rect textBoxBorder;
	//SDL_Rect scoreRect;

	//Player plr1;
	//NPC catDude;
	//Background bg1;
	//Uint16 dumbietimer;

	//Mix_Chunk* stepSfx;
	//Mix_Chunk* turnSfx;
	//Mix_Chunk* deathSfx;
	//Mix_Chunk* hurtSfx;
	//Mix_Chunk* powerSfx;
	//Mix_Chunk* talk;
	//Mix_Chunk* winscore;
	//Mix_Chunk* hehe;
	//Mix_Chunk* projectileRock;
	//Mix_Chunk* aoeSound;
	//Mix_Chunk* dashing;
	//Mix_Music* maintheme;
	//Mix_Chunk* dashMeow;

private: // private method prototypes
	Engine()
	{
		cout << "creating instance of engine..." << endl;
	}
	int Init(const char* title, int xPos, int yPos, int width, int height, int flags);
	void Clean();
	void Wake();
	void HandleEvents();
	void Update();
	void Render();
	void Sleep();

public: // public method prototypes
	int Run();
	static Engine& Instance();
	SDL_Renderer* GetRenderer() { return m_pRenderer; }
	bool& Running() { return m_running; }
	bool KeyDown(SDL_Scancode c);
};

#endif

// Reminder: you can ONLY have declarations (of variables and functions) in headers. What we have here is fine.
