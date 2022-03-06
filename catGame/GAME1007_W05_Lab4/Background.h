#pragma once

#include <SDL.h>

class Background
{
private:
	int whichBg;
public:
	SDL_Rect bgSrcTutorial, bgDst;
	SDL_Rect gameOverScreenSrc, gameOverScreenDst;
	Background();
};

class Level1Background
{
private:
	int whichBg;
	int howMany;
public:
	SDL_Rect swamp1Src, swamp1Dst;
	SDL_Rect swamp1aSrc;
	SDL_Rect swamp1bSrc;
	SDL_Rect swamp1bdownSrc;
	Level1Background(int bg, int length);
	void Update();
	int getBg();
};

