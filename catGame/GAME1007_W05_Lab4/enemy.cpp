#include "enemy.h"

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

DragonFly::DragonFly() :dfAni({ 0,0,32,32 }), frameCtr(0), frameMax(3), spriteIdx(0), spriteMax(3)
{
	dfDst = { 448, 100, 128, 128 };
	state = 0;
}


void DragonFly::setDFsz(int w, int h)
{
	w = dfDst.w;
	h = dfDst.h;
}

void DragonFly::setDFpos(int x, int y)
{
	x = dfDst.x;
	y = dfDst.y;
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
			dfAni.x = 0 + dfAni.w * spriteIdx;
		}
	}
}


