#pragma once
#include <SDL.h>
#include <iostream>

class NPC
{
private:
	unsigned short frameCtr, frameMax, spriteIdx, spriteMin, spriteMax;

public:
	int state;
	SDL_Rect npcSrc, npcDst;
	NPC();
	//Player(int h, int w, int s);
	void Update();
	void setNPCSize(int h, int w);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);

};

