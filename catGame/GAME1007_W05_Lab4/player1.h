#pragma once
#include <SDL.h>
#include <iostream>

//enum state { IDLE, MOVE };
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
public:
	SDL_Rect rockSrc, rockDst;
	Rock(int x, int y);
	void Update(int direction, double speed);


};