#pragma once
#include <SDL.h>
#include <iostream>

class Player {

public:
	SDL_Rect plr;
	int plrSpd;
	Player();
	Player(int h, int w, int s);
	void setPlrSize(int h, int w);
	void setPlrSpd(int s);
	void setPlrPos(int x, int y);
	int getPlrSpd();

};