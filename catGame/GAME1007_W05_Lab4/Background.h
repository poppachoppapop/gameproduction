#pragma once

#include <SDL.h>

class Background
{
private:
	int whichBg;
public:
	SDL_Rect bgSrcTutorial, bgDst;
	SDL_Rect swamp1Src, swamp1Dst;
	SDL_Rect swamp1aSrc, swamp1aDst;
	SDL_Rect swamp1bSrc, swamp1bDst;
	SDL_Rect swamp1bdownSrc,swamp1bdownDst;
	SDL_Rect gameOverScreenSrc, gameOverScreenDst;

	Background();
};

class Level1Background
{
private:
	int whichBg;
public:
	
	Level1Background(int bg);
};

