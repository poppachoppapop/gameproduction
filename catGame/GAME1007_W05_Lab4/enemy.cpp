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
	speed = 20;
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
			dir = 1;
		}
	}
	else if (dir == 1) {
		if (dirTimer < distance) {
			flyDst.x -= speed;
		}
		else {
			dirTimer = 0;
			dir = 2;
		}
	}
	else if (dir == 2) {
		if (dirTimer < distance) {
			flyDst.y += speed;
		}
		else {
			dirTimer = 0;
			dir = 3;
		}
	}
	else if (dir == 3) {
		if (dirTimer < distance) {
			flyDst.x += speed;
		}
		else {
			dirTimer = 0;
			dir = 0;
		}
	}
}

//Vines
Vines::Vines(int x, int y) :vineSrc({ 0,0,32,32 })
{
	vineDst = { x - 10 ,y + 10,vineSrc.w * 4, vineSrc.h * 4 };
}
