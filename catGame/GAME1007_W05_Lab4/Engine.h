#pragma once
#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "player1.h"
#include <vector>
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

	double speedAcc = 2, speedy = 0, speedx = 0;

	bool dashPressed = false;
	
	SDL_Texture* plrTxtr;
	vector<Rock*> playerpew;
	Player plr1;

	Mix_Chunk* stepSfx;
	Mix_Chunk* turnSfx;

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
