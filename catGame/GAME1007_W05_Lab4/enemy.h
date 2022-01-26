#pragma once
#include "SDL.h"

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

