#pragma once

#include <SDL.h>

class Items
{
private:
	int itemNum;
public:
	SDL_Rect item;
	Items(int item, int x, int y);
	void ItemType(int type);

};

class Heart {

public:
	Heart(int x, int y);
	SDL_Rect heartSrc, heartDst;
};

