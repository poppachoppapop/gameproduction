#pragma once
#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "player1.h"
#include <vector>
#include <ctime>
#define FPS 60
#define WIDTH 1024
#define HEIGHT 768
#define SPEED 10
#define DSPAWN 3//dumbie spawn rate

using namespace std;

class Dumbie
{
public:
	SDL_Rect dumbieSrc, dumbieDst;
	Uint16 frames = 0;
	Dumbie(int x, int y);	
	
};



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
	int Qcooldown = 200;

	double speedAcc = 2, speedy = 0, speedx = 0;
	double rockSpeed = 15;
	
	
	bool dashPressed = false;
	bool upPressed = false, downPressed = false, leftPressed = false, rightPressed = false;
	bool q = false;
	SDL_Texture* plrTxtr;
	SDL_Texture* rockTxtr;
	SDL_Texture* dumbieTxtr;

		
	vector<int> rockDir;
	vector<int> rockq;
	vector<Rock*> playerpew;
	vector<Dumbie*> dumbie;

	SDL_Rect dumbieSrc, dumbieDst;

	Player plr1;
	Uint16 dumbietimer;

	Mix_Chunk* stepSfx;
	Mix_Chunk* turnSfx;
	Mix_Chunk* deathSfx;
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
