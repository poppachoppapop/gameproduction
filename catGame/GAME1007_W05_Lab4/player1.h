#pragma once
#include <SDL.h>
#include <iostream>

class Player {

private:
	unsigned short frameCtr, frameMax, spriteIdx, spriteMax;

public:
	SDL_Rect plrSrc, plrDst;
	int plrSpd, plrDsh;
	Player();
	//Player(int h, int w, int s);
	void Update();
	void setPlrSize(int h, int w);
	void setPlrSpd(int s);
	void setPlrPos(int x, int y);
	int getPlrSpd();

};