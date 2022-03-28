#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

class Player
{

private:
	unsigned short frameCtr, frameMax, spriteIdx, spriteMin, spriteMax;
	int damageCD = 100;
	Mix_Chunk* hurtSfx;

public:
	int state;
	SDL_Rect plrFrontIdle, plrMoveLeft, plrMoveRight, plrMoveUp, plrMoveDown, plrDst, plrHpBar, hpborder;
	SDL_Rect plrwinbar;
	int plrSpd, plrDsh, plrMaxSpd;
	int fireRate;
	double plrHp, maxHp;
	double winbar, maxwin;
	int hurt;
	Player();
	//Player(int h, int w, int s);
	void Update();
	void setPlrSize(int h, int w);
	void setPlrSpd(int s);
	void setPlrPos(int x, int y);
	int getPlrSpd();
	int getMaxSpd();
	int getHurtOpacity();
	void takeDamage(double howMuch);
	void points(double howMuch);

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
class Portal
{
private:

public:
	SDL_Rect portalSrc, portalDst;
	Portal(int x, int y);
};


