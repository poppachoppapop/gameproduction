#include "enemy.h"
#include <cmath>
#include <iostream>
#define PI 3.14159265 




Boss::Boss(int x, int y,int h,int s) :BossSrc({ 0,0,32,32 }), frameCtr(0), frameMax(6), spriteIdx(0), spriteMax(9)
{
	HP = { 0,0,100,4 };
	BossDst = { x,y, 125, 125 };
	state = s;
	health = h;
	maxHealth = h;
	shootTimer = 0;
	health = h;
	maxHealth = h;
	//state = 0;
	//speed = 4;
	///halt = 0;
	attack1timer = 0;
	attack2timer = 0;
	attack3timer = 0;
	//Mix_Volume(2, 12);

}

void Boss::setState(int s)
{
	s = state;
}

int Boss::getState()
{
	return state;
}



void Boss::setHp(double h)
{
	h = health;
}

int Boss::getHp()
{
	return health;
}

int Boss::getShootTimer()
{
	return shootTimer;
}

int Boss::getDir()
{
	return dir;
}

void Boss::Update()
{
	if (state == 0||state == 2|| state == 4)
	{
		spriteMax = 9;
		if (spriteIdx > 9)
			spriteIdx = 0;
		if (frameCtr++ == frameMax)
		{
			frameCtr = 0;
			if (++spriteIdx == spriteMax)
			{
				spriteIdx = 0;
			}
			BossSrc.x = 0 + BossSrc.w * spriteIdx;
		}
	}
	
	frames++;
	healthBar.w = double(health / maxHealth) * 100;
	healthBar.x = BossDst.x + 15;
	healthBar.y = BossDst.y - 5;
	//cout << attack1timer << endl;
	//attack1 
	if (state == 0)
	{
		attack1timer++;
		if (attack1timer < 100)
		{
			state = 0;
		}
		if (attack1timer > 100)//spawns clones
		{
			state = 1;
			//attack1timer = 0;
		}

		if (attack1timer > 101)//attack 1 duration
		{
			state = 2;
		}
	}

	if (attack1timer > 300)

	if (attack1timer > 1000)//resets attack 1

	{
		state = 3;
		attack1timer = 0;
	}

	//attack 2
	
	if (state == 3)//spawns mushrooms
	{
		
		attack2timer++;
		if (attack2timer > 1)
		{
			state = 4;
			//attack2timer = 0;
		}
	}
		if (state == 4)//attack 2 duration
		{
			attack2timer++;
			if (attack2timer > 500)
			{
				state = 5;
			}
		}
		if (state == 5)//resets attack 2
		{
			attack2timer++;
			if (attack2timer > 505)
			{
				attack2timer = 0;
				//state = 0;
			}
			
		}

		if (state == 6)
		{
			attack3timer++;
			if (attack3timer > 1)
			{
				state = 7;
			}
		}
	
	
	//cout << attack2timer << endl;
	cout << state  << endl;

}

Bossf::Bossf(int x, int y, int s) :fBossSrc({ 0,0,32,32 }), frameCtr(0), frameMax(6), spriteIdx(0), spriteMax(9)
{
	HP = { 0,0,100,4 };
	fBossDst = { x,y, 125, 125 };

	//health = h;
	//maxHealth = h;
	shootTimer = 0;
	//health = h;
	//maxHealth = h;
	state = 0;
	//speed = 4;
	///halt = 0;
	//attack1timer = 0;
	//Mix_Volume(2, 12);
}


int Bossf::getState()
{
	return state;
}
void Bossf::setState(int s)
{
	s = state;
}

void Bossf::setHp(double h)
{
	h = health;
}

int Bossf::getHp()
{
	return health;
}

int Bossf::getShootTimer()
{
	return shootTimer;
}

int Bossf::getDir()
{
	return dir;
}

void Bossf::Update()
{
	if (state == 0)
	{
		spriteMax = 9;
		if (spriteIdx > 9)
			spriteIdx = 0;
		if (frameCtr++ == frameMax)
		{
			frameCtr = 0;
			if (++spriteIdx == spriteMax)
			{
				spriteIdx = 0;
			}
			fBossSrc.x = 0 + fBossSrc.w * spriteIdx;
		}
	}
	frames++;
	healthBar.w = double(health / maxHealth) * 100;
	healthBar.x = fBossDst.x + 15;
	healthBar.y = fBossDst.y - 5;
	//cout << attack1timer << endl;
	//attack1timer++;
	//cout << state  << endl;
	//cout <<"fboss" << endl;

}
Plant::Plant(int x, int y, int h) :plantSrc({ 0,0,32,64 }), plant2Src({ 0,0,32,32 }), plant3Src({ 0,0,32,32 })
{
	HP = { 0,0,100,4 };
	plantDst = { x,y, 64, 96 };
	plant2Dst = { x,y, 64, 64 };
	plant3Dst = { x,y, 64, 64 };
	health = h;
	maxHealth = h;
	health = h;
	maxHealth = h;
	//Mix_Volume(2, 12);
}

int Plant::getState()
{
	return state;
}

void Plant::setHp(double h)
{
	h = health;
}

int Plant::getHp()
{
	return health;
}


void Plant::Update()
{
	
	frames++;
	healthBar.w = double(health / maxHealth) * 100;
	healthBar.x = plantDst.x + 15;
	healthBar.y = plantDst.y - 5;
	
}


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
	HP.y = flyDst.y - 5;
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
	speed = 4;
	halt = 0;
	movetimer = 0;
	randNum = rand() % 81;
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
	if (movetimer > 120 + randNum)
	{
		movetimer = 0;
	}
	shootTimer++;
	if (shootTimer > 120 + randNum) {
		shootTimer = 0;
	}
	
}

Shroom::Shroom(int x, int y, int h) : shroomSrc({0,0,32,32}), frameCtr(0), frameMax(4), spriteIdx(0), spriteMax(4)
{
	HP = { 0,0,100,4 };
	shroomDst = { x,y,128,128 };
	healthBar = { x, y , 50, 5 };
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
	HP.x = shroomDst.x + 5;
	HP.y = shroomDst.y - 5;
	healthBar.w = double(health / maxHealth) * 100;
	healthBar.x = shroomDst.x + 5;
	healthBar.y = shroomDst.y - 5;
	frames++;

	shootTimer++;
	//cout << shootTimer << endl;
	if (shootTimer > rand()%150 + 200) {
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
