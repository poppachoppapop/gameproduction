#include "player1.h"
#include "States.h"

Player::Player() :plrFrontIdle({ 0,0,32,32 }), plrMoveDown({ 0,128,32,32 }), plrMoveUp({ 0,96,32,32 }), plrMoveLeft({ 0,32,32,32 }), plrMoveRight({ 0,64,32,32 }) ,
frameCtr(0), frameMax(3), spriteIdx(0), spriteMax(8)
{ 
	plrDst = {448 ,320 ,128, 128};
	plrHpBar = { 10 ,10 ,200, 25 };
	plrwinbar = { 600 ,10 ,5, 10 };
	hpborder = { 6,7,408,31 };
	plrSpd = 5;
	plrMaxSpd = 5;
	plrDsh = 50;
	plrHp = 10;
	maxHp = 5;
	winbar = 10;
	maxwin = 100;
	state = 0;
	fireRate = 50;
	hurt = 255;
	hurtSfx = Mix_LoadWAV("sfx/ow.wav");
}

void Player::Update()
{
	if (state == 0) { // idle down
		spriteMax = 8;
		if (spriteIdx > 8)
			spriteIdx = 0;
		if (frameCtr++ == frameMax)
		{
			frameCtr = 0;
			if (++spriteIdx == spriteMax)
			{
				spriteIdx = 0;
			}
			plrFrontIdle.x = 0 + plrFrontIdle.w * spriteIdx;
		}
	}
	else if(state == 1) { // walk down
		spriteMax = 8;
		if (frameCtr++ == frameMax)
		{
			frameCtr = 0;
			if (++spriteIdx == spriteMax)
			{
				spriteIdx = 0;
			}
			plrMoveDown.x = 0 + plrMoveDown.w * spriteIdx;
		}
	}
	else if(state == 2) { // walk up
		spriteMax = 8;
		if (frameCtr++ == frameMax)
		{
			frameCtr = 0;
			if (++spriteIdx == spriteMax)
			{
				spriteIdx = 0;
			}
			plrMoveUp.x = 0 + plrMoveUp.w * spriteIdx;
		}
	}
	else if(state == 3) { // walk left
		spriteMax = 8;
		if (frameCtr++ == frameMax)
		{
			frameCtr = 0;
			if (++spriteIdx == spriteMax)
			{
				spriteIdx = 0;
			}
			plrMoveLeft.x = 0 + plrMoveLeft.w * spriteIdx;
		}
	}
	else if(state == 4) { // walk right
		spriteMax = 8;
		if (frameCtr++ == frameMax)
		{
			frameCtr = 0;
			if (++spriteIdx == spriteMax)
			{
				spriteIdx = 0;
			}
			plrMoveRight.x = 0 + plrMoveRight.w * spriteIdx;
		}
	}
	plrwinbar.w = double(winbar / maxwin) * 200;
	plrHpBar.w = double(plrHp / maxHp) * 200;
	
	damageCD++;
	
}



void Player::setPlrSize(int h, int w)
{
	plrDst.h = h;
	plrDst.w = w;
}

void Player::setPlrSpd(int s)
{
	plrSpd = s;
}

void Player::setPlrPos(int x, int y)
{
	plrDst.x = x;
	plrDst.y = y;
}

int Player::getPlrSpd()
{
	return plrSpd;
}

int Player::getMaxSpd()
{
	return plrMaxSpd;
}

int Player::getHurtOpacity()
{
	return hurt;
}

void Player::takeDamage(double howMuch)
{ 
	if (damageCD > 40)
	{
		plrHp -= howMuch;
		damageCD = 0;
		Mix_PlayChannel(-1, hurtSfx, 0);
		hurt = 128;
	}
	else
		hurt = 255;
}

void Player::gainHealth(double howMuch) {
	plrHp += howMuch;
}

void Player::points(double howMuch)
{
	winbar += howMuch;
}

Rock::Rock(int x,int y, int s, char d) :rockSrc ({0,0,32,32}),rock2Src({ 0,0,32,32 })
{
	rockDst = { x,y,64,64 };
	rock2Dst = { x,y,32,32 };
	speed = s;
	dir = d;
}

void Rock::Update()
{
	if (dir == 'x')
		rockDst.x += speed;
	if (dir == 'y')
		rockDst.y += speed;

	//if (dir == 'x')
	//	rock2Dst.x += speed;
	//if (dir == 'y')
	//	rock2Dst.y += speed;
	
	
}

Portal::Portal(int x, int y): portalSrc({ 0,0,32,32 })
{
	portalDst = { x,y,128,128 };
}
