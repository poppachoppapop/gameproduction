#pragma once

#include <SDL.h>

class Background
{
private:
	int whichBg;
public:
	SDL_Rect bgSrcTutorial, bgDst;
	Background();
};

