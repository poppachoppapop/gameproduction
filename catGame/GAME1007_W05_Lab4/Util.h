#pragma once
#include <SDL.h>
#include <cmath>

class Util
{
private:
	int change;
public:
	static double distance(SDL_Rect a, SDL_Rect b);
	static double distanceOffset(SDL_Rect a, SDL_Rect b);
	static int fadeToBlack();
};

