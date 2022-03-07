#include "NPC.h"


NPC::NPC() /*: npcSrc({ 0,0,64,64 }), frameCtr(0), frameMax(3), spriteIdx(0), spriteMax(6)*/
{
	
	npcSrc= { 0,0,64,64 };
	npcDst = { 0, 0 ,128, 128 };
}

void NPC::Update()
{
	
	/*if (frameCtr++ == frameMax)
	{
		frameCtr = 0;
		if (++spriteIdx == spriteMax)
		{
			spriteIdx = 0;
		}
		npcSrc.x = 0 + npcSrc.w * spriteIdx;
	}*/
}

void NPC::setNPCSize(int h, int w)
{
	npcDst.w = w;
	npcDst.h = h;
}

int NPC::getX()
{
	return npcDst.x;
}

int NPC::getY()
{
	return npcDst.y;
}

void NPC::setX(int x)
{
	npcDst.x = x;
}
void NPC::setY(int y)
{
	npcDst.y = y;
}
