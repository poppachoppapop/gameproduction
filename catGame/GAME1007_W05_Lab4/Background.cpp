#include "Background.h"

Background::Background(): bgSrcTutorial({0,0,384,480}), gameOverScreenSrc({0, 0, 1024, 768})
{
	bgDst = { 0,-1300, bgSrcTutorial.w *4, bgSrcTutorial.h * 4 };
	//gameOverScreenDst = { 350, -150, gameOverScreenSrc.w * 2, gameOverScreenSrc.h * 4 };
}

Level1Background::Level1Background(int bg): swamp1Src({ 0,0,1024,768 }), swamp1aSrc({ 0,0,1024,768 }), swamp1bSrc({ 0,0,1024,768 }), swamp1bdownSrc({ 0,0,1024,768 })
{
	swamp1Dst = { + 350, -150,swamp1Src.w * 2 ,swamp1Src.h * 2  };
}
