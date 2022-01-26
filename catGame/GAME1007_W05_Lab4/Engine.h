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
	
	// SFX Timers
	int stepSoundTimer = 0, turnSoundTimer = 0;
	int dashCooldown = 100, dashTimer = 0 , tempSpeed = 0;
	int rockCooldown = 50;
	int spcooldown = 200;
	int itemSpawnTimer = 0;

	//modifiable variables
	int playerDamage = 1;

	double speedAcc = 2, speedy = 0, speedx = 0;
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

	vector<Rock*> playerpew;
	vector<Enemy*> dumbie;
	vector<Items*> item1;

	SDL_Rect textBoxRect;
	SDL_Rect textBoxBorder;

	Player plr1;
	Uint16 dumbietimer;

	Mix_Chunk* stepSfx;
	Mix_Chunk* turnSfx;
	Mix_Chunk* deathSfx;
	Mix_Chunk* hurtSfx;
	Mix_Chunk* powerSfx;
	Mix_Music* maintheme;

private: // private method prototypes
	int Init(const char* title, int xPos, int yPos, int width, int height, int flags);
	void Clean();
	void Wake();
	void HandleEvents();
	bool KeyDown(SDL_Scancode c);
	void Update();
	void Render();
	void Sleep();

public: // public method prototypes
	int Run();


};

#endif

// Reminder: you can ONLY have declarations (of variables and functions) in headers. What we have here is fine.
