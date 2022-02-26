#pragma once
#include <SDL.h>
#include <iostream>

class Player
{

private:
	unsigned short frameCtr, frameMax, spriteIdx, spriteMin, spriteMax;

public:
	int state;
	SDL_Rect plrFrontIdle, plrMoveLeft, plrMoveRight, plrMoveUp, plrMoveDown, plrDst;
	int plrSpd, plrDsh;
	Player();
	//Player(int h, int w, int s);
	void Update();
	void setPlrSize(int h, int w);
	void setPlrSpd(int s);
	void setPlrPos(int x, int y);
	int getPlrSpd();

};


class Rock
{
private:
	int speed;
	char dir;
public:
	SDL_Rect rockSrc, rockDst;
	Rock(int x, int y, int s, char d);
	void Update();
	
};


