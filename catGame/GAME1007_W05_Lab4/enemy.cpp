#include "enemy.h"
//Dummy
Enemy::Enemy(int x, int y, double h) :enemySrc({ 0,0,64,64 })
{
	//random dumie spawn
	enemyDst = { x - 10 ,y +10,enemySrc.w *2, enemySrc.h*2 };
	healthBar = { x, y , 50, 5};
	health = h;
	maxHealth = h;
}


void Enemy::setHp(double h) {
	health = h;
}

int Enemy::getHp()
{
	return health;
}

void Enemy::update()
{
	healthBar.w = double(health / maxHealth) * 100;
	healthBar.x = enemyDst.x + 15;
	healthBar.y = enemyDst.y - 5;
}


//DragonFly
DragonFly::DragonFly(int x, int y, double h) : flySrc({ 0,0,32,32 }), frameCtr(0), frameMax(3), spriteIdx(0), spriteMax(3)
{
	flyDst = { x, y, 128, 128 };
	healthBar = { x, y , 50, 5 };
	health = h;
	maxHealth = h;
	state = 0;
	dir = 0;
	dirTimer = 0;
	speed = 5;
	distance = 10;
}

void DragonFly::setHp(double h)
{
	health = h;
}

int DragonFly::getHp()
{
	return health;
}

void DragonFly::Update()
{
	
	//dragon fly animation
	if (state == 0)
	{
		spriteMax = 3;
		if (spriteIdx > 3)
			spriteIdx = 0;
		if (frameCtr++ == frameMax)
		{
			frameCtr = 0;
			if (++spriteIdx == spriteMax)
			{
				spriteIdx = 0;
			}
			flySrc.x = 0 + flySrc.w * spriteIdx;
		}
	}
	healthBar.w = double(health / maxHealth) * 100;
	healthBar.x = flyDst.x + 15;
	healthBar.y = flyDst.y - 5;
	dirTimer++;

	if (dir == 0) {
		if (dirTimer < distance) {
			flyDst.y -= speed;
		}
		else {
			dirTimer = 0;
			dir = rand()% 5;
		}
	}
	else if (dir == 1) {
		if (dirTimer < distance) {
			flyDst.x -= speed;
		}
		else {
			dirTimer = 0;
			dir = rand() % 5;
		}
	}
	else if (dir == 2) {
		if (dirTimer < distance) {
			flyDst.y += speed;
		}
		else {
			dirTimer = 0;
			dir = rand() % 5;
		}
	}
	else if (dir == 3) {
		if (dirTimer < distance) {
			flyDst.x += speed;
		}
		else {
			dirTimer = 0;
			dir = rand() % 5;
		}
	}
	else {
		if (dirTimer < distance) {
			
		}
		else {
			dirTimer = 0;
			dir = rand() % 5;
		}
	}
}

//Vines
Vines::Vines(int x, int y) :vineSrc({ 0,0,32,32 })
{
	vineDst = { x - 10 ,y + 10,vineSrc.w * 4, vineSrc.h * 4 };
}

//frog
Frog::Frog(int x, int y, int h) :frogSrc({ 0,0,32,32 }), frameCtr(0), frameMax(3), spriteIdx(0), spriteMax(7)
{
	frogDst = { x,y, 125, 125 };
	healthBar = { x, y , 50, 5 };
	health = h;
	maxHealth = h;
	state = 0;
	
	
}

void Frog::setHp(double h)
{
	health = h;
}

int Frog::getHp()
{
	return health;
}

void Frog::Update()
{
	if (state == 0)
	{
		spriteMax = 7;
		if (spriteIdx > 7)
			spriteIdx = 0;
		if (frameCtr++ == frameMax)
		{
			frameCtr = 0;
			if (++spriteIdx == spriteMax)
			{
				spriteIdx = 0;
			}
			frogSrc.x = 0 + frogSrc.w * spriteIdx;
		}
	}
	healthBar.w = double(health / maxHealth) * 100;
	healthBar.x = frogDst.x + 15;
	healthBar.y = frogDst.y - 5;
}
