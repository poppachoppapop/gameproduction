#include "enemy.h"

Attack::Attack(int x, int y)
{
	//temp sdl rect for attack
	frogAttackDst = { x,y,29,7 };
	rfrogAttackDst = { x,y,29,7 };

	ushroomAtkDst ={ x,y,25,3 };
	lshroomAtkDst= { x,y,3,25 };
	rshroomAtkDst= { x,y,3,25 };
    dshroomAtkDst= { x,y,25,3 };
}

void Attack::Update(int move)
{
	//frogAttackSrc
	frogAttackDst.x += SPEED * move;
	rfrogAttackDst.x += SPEED * move;

	ushroomAtkDst.y += SHROOM * move;
	lshroomAtkDst.x += SHROOM * move;
	rshroomAtkDst.x += SHROOM * move;
	dshroomAtkDst.y += SHROOM * move;
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
	shootTimer = 0;
	health = h;
	maxHealth = h;
	state = 0;	
	speed = 2;
}
	

void Frog::setHp(double h)
{
	health = h;
}

int Frog::getHp()
{
	return health;
}

int Frog::getShootTimer()
{
	return shootTimer;
}

int Frog::getDir()
{
	return dir;
}

void Frog::Update(SDL_Rect plr)
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

	if (Util::distanceOffset(plr, frogDst) < 550) {
		if (plr.x - frogDst.x > 0) {
			frogDst.x += speed;
			dir = 0;
		}
		if (plr.x - frogDst.x < 0) {
			frogDst.x -= speed;
			dir = 1;
		}
		if (plr.y - frogDst.y > 0) {
			frogDst.y += speed;
			dir = 2;
		}
		if (plr.y - frogDst.y < 0) {
			frogDst.y -= speed;
			dir = 3;
		}
	}
	shootTimer++;
	if (shootTimer > 100)
		shootTimer = 0;
}

void Frog::resetFrames()
{
	frames = 0;
}

Shroom::Shroom(int x, int y, int h) : shroomSrc({0,0,32,32}), frameCtr(0), frameMax(9), spriteIdx(0), spriteMax(4)
{
	shroomDst = { x,y,64,64 };
	healthBar = { x, y , 25, 5 };
	health = h;
	maxHealth = h;
	state = 0;
}

void Shroom::setHp(double h)
{
	health = h;
}

int Shroom::getHp()
{
	return health;
}

void Shroom::Update()
{
	if (state == 0)
	{
		spriteMax = 4;
		if (spriteIdx > 4)
			spriteIdx = 0;
		if (frameCtr++ == frameMax)
		{
			frameCtr = 0;
			if (++spriteIdx == spriteMax)
			{
				spriteIdx = 0;
			}
			shroomSrc.x = 0 + shroomSrc.w * spriteIdx;
		}
	}

	healthBar.w = double(health / maxHealth) * 50;
	healthBar.x = shroomDst.x + 5;
	healthBar.y = shroomDst.y - 5;
	frames++;
}

void Shroom::resetFrames()
{
	frames = 0;
}

Bubble::Bubble(int x, int y)
{
	bubbleDst = { x,y,32,32 };
	speed = 8;
	foundDir = false;
	left, right, up, down = false;
}

void Bubble::Update(SDL_Rect plr)
{
	if (!foundDir) {
		left = false;
		right = false;
		up = false;
		down = false;
		if (plr.x - bubbleDst.x >= 0) // left
			left = true;
		if (plr.x - bubbleDst.x <= 0) // right
			right = true;
		if (plr.y - bubbleDst.y >= 0) // down
			down = true;
		if (plr.y - bubbleDst.y <= 0) // up
			up = true;
		foundDir = true;

	}
	if (left)
		bubbleDst.x += speed;
	if (right)
		bubbleDst.x -= speed;
	if (down)
		bubbleDst.y += speed;
	if (up)
		bubbleDst.y -= speed;

}
