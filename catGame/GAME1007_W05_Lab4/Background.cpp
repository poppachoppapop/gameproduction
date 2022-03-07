#include "Background.h"

Background::Background() : bgSrcTutorial({ 0,0,384,480 }), gameOverScreenSrc({ 0, 0, 1024, 768 }),
swamp1Src({ 0,0,1024,768 }), swamp1aSrc({ 0,0,1024,768 }),
swamp1bSrc({ 0,0,1024,768 }), swamp1bdownSrc({ 0,0,1024,768 })
{
	bgDst = { 0,-1300, bgSrcTutorial.w *4, bgSrcTutorial.h * 4 };
	swamp1Dst = { +350, -150,swamp1Src.w * 2 ,swamp1Src.h * 2 };
	swamp1aDst = { -1695,-150,swamp1aSrc.w * 2 ,swamp1aSrc.h * 2 };
	swamp1bDst = { -3743,-150,swamp1bSrc.w * 2 ,swamp1bSrc.h * 2 };
	swamp1bdownDst = { -3743, +1378,swamp1bdownSrc.w * 2 ,swamp1bdownSrc.h * 2 };
	//gameOverScreenDst = { 350, -150, gameOverScreenSrc.w * 2, gameOverScreenSrc.h * 4 };
}


