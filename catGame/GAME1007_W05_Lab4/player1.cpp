#include "player1.h"

Player::Player() :plrSrc({ 0,0,32,32 }), frameCtr(0), frameMax(3),
spriteIdx(0), spriteMax(6) 
{ 
	plrDst = {10 ,10 ,100, 100};
	plrSpd = 10;
	plrDsh = 20;
}



void Player::Update()
{
	if (frameCtr++ == frameMax)
	{
		frameCtr = 0;
		if (++spriteIdx == spriteMax)
		{
			spriteIdx = 0;
		}
		plrSrc.x = 0 + plrSrc.w * spriteIdx;
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


