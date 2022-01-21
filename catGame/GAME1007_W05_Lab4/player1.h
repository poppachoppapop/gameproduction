#pragma once
#include <SDL.h>
#include <iostream>
#define MOVESPEED 7
enum state { IDLE, MOVE };
class Player {

private:
	unsigned short frameCtr, frameMax, spriteIdx, spriteMin, spriteMax;

public:
	state m_state;
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
class Rock
{
public:
	SDL_Rect rockSrc, rockDst;

	Rock(int = 0, int = 0);
	void Update(int moving);


};