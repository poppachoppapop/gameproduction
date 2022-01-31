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

