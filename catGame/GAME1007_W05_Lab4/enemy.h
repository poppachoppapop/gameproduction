#pragma once
#include "SDL.h"
#include <ctime>
#include "engine.h"
#define MOVESPEED
#define FROGSPEED 2

class Enemy
{

protected:
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
	double health;
	double maxHealth;
	int dir;
	int speed;
	int dirTimer;
	int distance;
	int upCount, downCount, rightCount, leftCount, maxCount;
public:
	DragonFly(int x, int y, double h);
	SDL_Rect flySrc, flyDst, healthBar;
	Uint16 frames = 0;
	void setHp(double h);
	int getHp();
	void Update();
};

class Vines {
private:

public:
	SDL_Rect vineSrc, vineDst;
	Vines(int x, int y);
};
class Frog
{
	private:
		unsigned short frameCtr, frameMax, spriteIdx, spriteMin, spriteMax;
		int state;
		double health;
		double maxHealth;
		
public:
	Frog(int x, int y, int h);
	SDL_Rect frogSrc, frogDst, healthBar;
	Uint16 frames = 0;
	void setHp(double h);
	int getHp();
	void Update();
};


