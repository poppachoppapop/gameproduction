#pragma once
#include "SDL.h"
#include <ctime>
#include "engine.h"
#define MOVESPEED
//#define FROGSPEED 2
#define FROGATTACK 7
#define ATTACKRATE 3
class Attack
{
private:

public:
	SDL_Rect frogAttackDst,frogAttackSrc;
	SDL_Rect rfrogAttackDst, rfrogAttackSrc;
	Uint16 frames = 0;
	Attack(int = 0, int = 0);	
	void Update(int move);

};
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
//shooting frog
class Frog
{
	private:
		unsigned short frameCtr, frameMax, spriteIdx, spriteMin, spriteMax;
		int state;
		double health;
		double maxHealth;				
public:	
	SDL_Rect frogSrc, frogDst, healthBar;
	Frog(int x, int y, int h);
	Uint16 frames = 0;
	void setHp(double h);
	int getHp();
	void Update(int move);
	void resetFrames();
};

class Frog2
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
	SDL_Rect frog2Src, frog2Dst, healthBar;
	Frog2(int x, int y, int h);
	Uint16 frames = 0;
	void setHp(double h);
	int getHp();
	void Update();
	//void resetFrames();
};
class Shroom
{
private:
	unsigned short frameCtr, frameMax, spriteIdx, spriteMin, spriteMax;
	int state;
	double health;
	double maxHealth;
public:
	SDL_Rect shroomSrc, shroomDst, healthBar;
	Shroom(int x, int y, int h);
	Uint16 frames = 0;
	void setHp(double h);
	int getHp();
	void Update();
	//void resetFrames();

};

