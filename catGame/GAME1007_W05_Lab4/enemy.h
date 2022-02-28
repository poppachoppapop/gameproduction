#pragma once
#include "SDL.h"
#define EMOVESPEED

class Enemy
{
private:
	double health;
	double maxHealth;
public:
	SDL_Rect enemySrc, enemyDst , healthBar;
	Uint16 frames = 0;
	Enemy(int x, int y, double h);
	void setHp(double h);
	int getHp();
	void update();
};

class DragonFly
{
private:
	unsigned short frameCtr, frameMax, spriteIdx, spriteMin, spriteMax;
	int state;
public:
	DragonFly();
	SDL_Rect dfAni, dfDst;
	Uint16 frames = 0;
	void setDFsz(int w, int h);
	void setDFpos(int x, int y);
	void Update();
};

class Vines {
private:

public:
	SDL_Rect vineSrc, vineDst;
	Vines(int x, int y);
};


