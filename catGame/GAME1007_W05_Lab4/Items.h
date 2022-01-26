#pragma once

#include <SDL.h>

class Items
{
private:
	int itemNum;
public:
	SDL_Rect item;
	Items(int item);
	void ItemType(int type);

};

