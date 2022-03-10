#pragma once
#include "SDL.h"
#include <ctime>
#include "engine.h"
#include "Util.h"

#define MOVESPEED
//#define FROGSPEED 2
#define SHROOM 1//shroom spore move speed 
#define FROGATTACK 7
#define ATTACKRATE 3
#define CLOUDRATE 8 //shroom spore spawn rate
class Attack
{
private:

public:
	SDL_Rect frogAttackDst,frogAttackSrc;
	SDL_Rect rfrogAttackDst, rfrogAttackSrc;
	SDL_Rect ushroomAtkDst, ushroomAtkSrc;
	SDL_Rect lshroomAtkDst, lshroomAtkSrc;
	SDL_Rect rshroomAtkDst, rshroomAtkSrc;
	SDL_Rect dshroomAtkDst, dshroomAtkSrc;
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
	bool lookLeft;
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
		int dir;
		double health;
		double maxHealth;			
		double speed;
		bool frogLeft, frogRight, frogUp, frogDown;
		int shootTimer;
		int halt;
		int movetimer;
public:	
	SDL_Rect frogSrc, frogDst, healthBar;
	Frog(int x, int y, int h);
	Uint16 frames = 0;
	void setHp(double h);
	int getHp();
	int getShootTimer();
	int getDir();
	void Update(SDL_Rect plr);
	void resetFrames();
};

class Bubble {
private:
	int speed;
	bool foundDir;
	bool up, down, left, right;
public:
	SDL_Rect bubbleDst;
	Bubble(int x, int y);
	void Update(SDL_Rect plr);

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
	void resetFrames();

};

