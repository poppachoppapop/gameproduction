#pragma once

#include <SDL.h>

class Background
{
private:
	int whichBg;
public:
	SDL_Rect bgSrcTutorial, bgDst;
	SDL_Rect swamp1Src, swamp1Dst;
	Background();
};

