#include "Items.h"
#include "Player1.h"
Items::Items(int item, int x, int y) :item({ x,y,50,50 })
{
	itemNum = item;
}

void Items::ItemType(int type)
{

}

Heart::Heart(int x, int y) : heartSrc({ 0,0,8,8 }),heartDst({ x,y,32,32 })
{
	//cool
}
