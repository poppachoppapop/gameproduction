#include "player1.h"


Player::Player() :plrFrontIdle({ 0,0,32,32 }), plrMoveDown({ 0,128,32,32 }), plrMoveUp({ 0,160,32,32 }), plrMoveLeft({ 0,192,32,32 }), plrMoveRight({ 0,224,32,32 }) ,
frameCtr(0), frameMax(3), spriteIdx(0), spriteMax(6)
{ 
	plrDst = {10 ,10 ,100, 100};
	plrSpd = 5;
	plrDsh = 50;
	state = 0;
}




void Player::Update()
{
	if (state == 0) { // idle down
		spriteMax = 6;
		if (spriteIdx > 6)
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
		spriteMax = 10;
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
		spriteMax = 10;
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
		spriteMax = 10;
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
		spriteMax = 10;
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

Rock::Rock(int x,int y, int s, char d) :rockSrc ({0,0,32,32})
{
	rockDst = { x,y,64,64 };
	speed = s;
	dir = d;
}

void Rock::Update()
{
	if (dir == 'x')
		rockDst.x += speed;
	if (dir == 'y')
		rockDst.y += speed;
	
	
}


