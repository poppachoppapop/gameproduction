#include "enemy.h"

Enemy::Enemy(int x, int y, double h) :enemySrc({ 0,0,69,69 })
{
	//random dumie spawn
	enemyDst = { x - 10 ,y +10,enemySrc.w, enemySrc.h };
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
	healthBar.w = double(health / maxHealth) * 50;
	healthBar.x = enemyDst.x;
	healthBar.y = enemyDst.y;
}

