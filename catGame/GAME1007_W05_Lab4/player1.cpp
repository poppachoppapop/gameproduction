#include "player1.h"

Player::Player()
{
	plr.h = 50;
	plr.w = 50;
	plr.x = 100;
	plr.y = 100;
	plrSpd = 10;
}

Player::Player(int h, int w, int s)
{
	plr.h = h;
	plr.w = w;
	plrSpd = s;
}

void Player::setPlrSize(int h, int w)
{
	plr.h = h;
	plr.w = w;
}

void Player::setPlrSpd(int s)
{
	plrSpd = s;
}

void Player::setPlrPos(int x, int y)
{
	plr.x = x;
	plr.y = y;
}

int Player::getPlrSpd()
{
	return plrSpd;
}


