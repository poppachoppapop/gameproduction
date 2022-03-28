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
#define LV1SPEED 4

using namespace std;

class Engine
{
private: // private propeties.
	bool m_running = false;
	Uint32 m_start, m_end, m_delta, m_fps;
	const Uint8* m_keystates;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
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
