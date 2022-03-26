#include "Background.h"

Background::Background(): bgSrcTutorial({0,0,704,608}), gameOverScreenSrc({0, 0, 1024, 768}),treesrc({0,0,704,608})
{
	bgDst = { 0,-1300, bgSrcTutorial.w *4, bgSrcTutorial.h * 4 };
	treedst= { 0,-1300, bgSrcTutorial.w *4, bgSrcTutorial.h * 4 };
	//gameOverScreenDst = { 350, -150, gameOverScreenSrc.w * 2, gameOverScreenSrc.h * 4 };
}

Level1Background::Level1Background(int bg, int length): swampSrc({ 0,0,1024,768 })
{
	swampDst = { 350, -150,swampSrc.w * 2 ,swampSrc.h * 2  };
	whichBg = bg;
	howMany = length;
}

void Level1Background::Update()
{
	
}

int Level1Background::getBg()
{
	return whichBg;
}
