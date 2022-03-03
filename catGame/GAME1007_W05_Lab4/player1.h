#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

class Player
{

private:
	unsigned short frameCtr, frameMax, spriteIdx, spriteMin, spriteMax;
	int damageCD = 100;
	double plrHp, maxHp;
	Mix_Chunk* hurtSfx;

public:
	int state;
	SDL_Rect plrFrontIdle, plrMoveLeft, plrMoveRight, plrMoveUp, plrMoveDown, plrDst, plrHpBar;
	int plrSpd, plrDsh, plrMaxSpd;
	Player();
	//Player(int h, int w, int s);
	void Update();
	void setPlrSize(int h, int w);
	void setPlrSpd(int s);
	void setPlrPos(int x, int y);
	int getPlrSpd();
	int getMaxSpd();
	void takeDamage(int howMuch);

};


class Rock
{
private:
	int speed;
	char dir;
public:
	SDL_Rect rockSrc, rockDst;
	SDL_Rect rock2Src, rock2Dst;
	Rock(int x, int y, int s, char d);
	void Update();
	
};


