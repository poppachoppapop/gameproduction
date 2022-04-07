#pragma once
#include "SDL.h"
#include <ctime>
#include "engine.h"
#include "Util.h"

//#define MOVESPEED
//#define FROGSPEED 2
//#define SHROOM 1//shroom spore move speed 
//#define FROGATTACK 7
//#define ATTACKRATE 3
//#define CLOUDRATE 8 //shroom spore spawn rate
class Boss
{
private:
	unsigned short frameCtr, frameMax, spriteIdx, spriteMin, spriteMax;
	int state;
	int dir;
	double health;
	double maxHealth;
	int speedx;
	double speed;
	int shootTimer;
	int halt;
	int attack1timer;
	int attack2timer;
	int attack3timer;
	int attack4timer;
	int randNum;

public:
	SDL_Rect BossSrc, BossDst;
	SDL_Rect HP;//white hp
	SDL_Rect healthBar;

	Boss(int x, int y,int h,int s);

	Uint16 frames = 0;
	void setState(int s);
	int getState();
	void setHp(double h);
	int getHp();
	int getShootTimer();
	int getDir();
	void Update();
};
class Bossf
{
private:
	unsigned short frameCtr, frameMax, spriteIdx, spriteMin, spriteMax;
	int state;
	int dir;
	double health;
	double maxHealth;

	double speed;
	int shootTimer;
	int halt;
	int attack1timer;
	int randNum;

public:
	SDL_Rect fBossSrc, fBossDst;
	SDL_Rect HP;//white hp
	SDL_Rect healthBar;
	Bossf(int x, int y, int s);
	Uint16 frames = 0;
	int getState();
	void setState(int s);
	void setHp(double h);
	int getHp();
	int getShootTimer();
	int getDir();
	void Update();
};
class Plant
{
private:
	int state;
	double health;
	double maxHealth;
public:
	SDL_Rect plantSrc, plantDst;
	SDL_Rect plant2Src, plant2Dst;
	SDL_Rect plant3Src, plant3Dst;
	SDL_Rect HP;//white hp
	SDL_Rect healthBar;
	Plant(int x, int y, int h);
	Uint16 frames = 0;
	int getState();
	void setHp(double h);
	int getHp();
	void Update();

};
class Cloud
{
private:

public:
	SDL_Rect cloudSrc, cloudDst;
	Cloud(int x, int y,int s, char d);
	void Update();
	char dir;
	int speed;
	int shootTimer;
	int state;
	
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
	SDL_Rect HP;//white hp
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
		int randNum;
		
public:	
	
	SDL_Rect HP;//white hp
	SDL_Rect frogSrc, frogDst, healthBar;
	Frog(int x, int y, int h);
	Uint16 frames = 0;
	int getState();
	void setHp(double h);
	int getHp();
	int getShootTimer();
	int getDir();
	void Update(SDL_Rect plr);
	
};

class Bubble {
private:
	int speed , speedx, speedy;
	bool foundDir;
	bool up, down, left, right;
	bool seek;
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
	int shootTimer;
	SDL_Rect HP;//white hp
	SDL_Rect shroomSrc, shroomDst, healthBar;
	Shroom(int x, int y, int h);
	Uint16 frames = 0;
	void setHp(double h);
	int getHp();
	void Update();
	//void resetFrames();

};

