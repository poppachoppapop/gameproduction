#include "enemy.h"
#include <cmath>
#define PI 3.14159265 



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
	HP = { 0,0,100,4 };
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
	lookLeft = true;	
	
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
	HP.x = flyDst.x + 15;
	HP.y = flyDst.y - 1;
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
			lookLeft = true;
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
			lookLeft = false;
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
	
	HP = { 0,0,100,4 };
	frogDst = { x,y, 125, 125 };	
	healthBar = { x, y , 50, 5 };	
	shootTimer = 0;
	health = h;
	maxHealth = h;
	state = 0;	
	speed = 5;
	halt = 0;
	movetimer = 0;
	//Mix_Volume(2, 12);
}
	

int Frog::getState()
{
	return state;
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
	HP.x = frogDst.x + 15;
	HP.y = frogDst.y - 5;
	healthBar.w = double(health / maxHealth) * 100;
	healthBar.x = frogDst.x + 15;
	healthBar.y = frogDst.y - 5;
	frames++;
	movetimer++;
	if (movetimer < 100){
		if (Util::distanceOffset(plr, frogDst) < 550)
		{
			float angle = atan2(frogDst.y + 50 - plr.y - 50, frogDst.x + 50 - plr.x - 50) * 180 / PI;
			frogDst.x -= speed * (cos(angle * PI / 180));
			frogDst.y -= speed * (sin(angle * PI / 180));
		}
	}	
	if (movetimer > 150)
	{
		movetimer = 0;
	}
	shootTimer++;
	if (shootTimer > 100) {
		shootTimer = 0;
	}
	
}

Shroom::Shroom(int x, int y, int h) : shroomSrc({0,0,32,32}), frameCtr(0), frameMax(9), spriteIdx(0), spriteMax(4)
{
	HP = { 0,0,100,4 };
	shroomDst = { x,y,128,128 };
	healthBar = { x, y , 25, 5 };
	health = h;
	maxHealth = h;
	state = 0;
	shootTimer = 0;
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
	HP.x = shroomDst.x + 15;
	HP.y = shroomDst.y - 5;
	healthBar.w = double(health / maxHealth) * 100;
	healthBar.x = shroomDst.x + 5;
	healthBar.y = shroomDst.y - 5;
	frames++;

	shootTimer++;
	//cout << shootTimer << endl;
	if (shootTimer > rand()%100 + 150) {
		shootTimer = 0;
	}
	
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
	float angle = atan2(bubbleDst.y - plr.y - 50, bubbleDst.x - plr.x - 50) * 180 / PI;
	if (!foundDir) {
		speedx = speed * (cos(angle * PI / 180));
		speedy = speed * (sin(angle * PI / 180));
		
		foundDir = true;
	}
	bubbleDst.x -= speedx;
	bubbleDst.y -= speedy;

	//follows player (maybe use for dragon fly?)
	//bubbleDst.x -= 5 * (cos(angle * PI / 180));
	//bubbleDst.y -= 5 * (sin(angle * PI / 180));

}

Cloud::Cloud(int x, int y, int s, char d):cloudSrc({ 0,0,16,16 })
{
	cloudDst = { x,y,32,32 };	
	speed = s;
	dir = d;
}

void Cloud::Update()
{
	if (dir == 'x')
		cloudDst.x += speed;
	if (dir == 'y')
		cloudDst.y += speed;

}
