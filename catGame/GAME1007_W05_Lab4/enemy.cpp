#include "enemy.h"

Attack::Attack(int x, int y)
{
	//temp sdl rect for attack
	frogAttackDst = { x,y,29,7 };
}

void Attack::Update(int move)
{
	//frogAttackSrc

	frogAttackDst.x += SPEED * move;
}

//Dumbie
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
	upCount = 0;
	downCount = 0;
	leftCount = 0;
	rightCount = 0;
	maxCount = 5;
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

	if (dir == 0 && maxCount > upCount) {
		if (dirTimer < distance) {
			flyDst.y -= speed;
		}
		else {
			dirTimer = 0;
			dir = rand()% 5;
			upCount++;
		}
	}
	else if (dir == 1 && maxCount > leftCount) {
		if (dirTimer < distance) {
			flyDst.x -= speed;
		}
		else {
			dirTimer = 0;
			dir = rand() % 5;
			leftCount++;
		}
	}
	else if (dir == 2 && maxCount > downCount) {
		if (dirTimer < distance) {
			flyDst.y += speed;
		}
		else {
			dirTimer = 0;
			dir = rand() % 5;
			downCount++;
		}
	}
	else if (dir == 3 && maxCount > rightCount) {
		if (dirTimer < distance) {
			flyDst.x += speed;
		}
		else {
			dirTimer = 0;
			dir = rand() % 5;
			rightCount++;
		}
	}
	else{
		if (dirTimer > distance) {
			dirTimer = 0;
			dir = rand() % 5;
		}
	}
	if ((maxCount * 4) <= leftCount + rightCount + upCount + downCount) {
		leftCount = 0;
		rightCount = 0;
		downCount = 0;
		upCount = 0;
	}
}

//Vines
Vines::Vines(int x, int y) :vineSrc({ 0,0,32,32 })
{
	vineDst = { x - 10 ,y + 10,vineSrc.w * 4, vineSrc.h * 4 };
}

//frog
Frog::Frog(int x, int y, int h) :frogSrc({ 0,0,32,32 }), frameCtr(0), frameMax(4), spriteIdx(0), spriteMax(7)
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

void Frog::Update(int move)
{
	//shooting frog
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
	frames++;	
	
}

void Frog::resetFrames()
{
	frames = 0;
}

//frog that moves rand & doesnt shoot
Frog2::Frog2(int x, int y, int h): frog2Src({ 0,0,32,32 }), frameCtr(0), frameMax(4), spriteIdx(0), spriteMax(7)
{
	//frog2Src = { 0,0,32,32 };
	frog2Dst = { x,y, 160, 160 };
	healthBar = { x, y , 50, 5 };
	health = h;
	maxHealth = h;
	state = 0;
	dir = 0;
	dirTimer = 0;
	speed = 5;
	distance = 10;
	upCount = 0;
	downCount = 0;
	leftCount = 0;
	rightCount = 0;
	maxCount = 5;
}

void Frog2::setHp(double h)
{
	health = h;
}

int Frog2::getHp()
{
	return health;
}

void Frog2::Update()
{
	//moving frog
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
			frog2Src.x = 0 + frog2Src.w * spriteIdx;
		}
	}
	healthBar.w = double(health / maxHealth) * 100;
	healthBar.x = frog2Dst.x + 15;
	healthBar.y = frog2Dst.y - 5;
	dirTimer++;

	if (dir == 0 && maxCount > upCount) {
		if (dirTimer < distance) {
			frog2Dst.y -= speed;
		}
		else {
			dirTimer = 0;
			dir = rand() % 5;
			upCount++;
		}
	}
	else if (dir == 1 && maxCount > leftCount) {
		if (dirTimer < distance) {
			frog2Dst.x -= speed;
		}
		else {
			dirTimer = 0;
			dir = rand() % 5;
			leftCount++;
		}
	}
	else if (dir == 2 && maxCount > downCount) {
		if (dirTimer < distance) {
			frog2Dst.y += speed;
		}
		else {
			dirTimer = 0;
			dir = rand() % 5;
			downCount++;
		}
	}
	else if (dir == 3 && maxCount > rightCount) {
		if (dirTimer < distance) {
			frog2Dst.x += speed;
		}
		else {
			dirTimer = 0;
			dir = rand() % 5;
			rightCount++;
		}
	}
	else {
		if (dirTimer > distance) {
			dirTimer = 0;
			dir = rand() % 5;
		}
	}
	if ((maxCount * 4) <= leftCount + rightCount + upCount + downCount) {
		leftCount = 0;
		rightCount = 0;
		downCount = 0;
		upCount = 0;
	}
}
