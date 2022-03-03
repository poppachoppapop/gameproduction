#include "Background.h"

Background::Background(): bgSrcTutorial({0,0,384,480}),swamp1Src({0,0,1024,768})
{
	bgDst = { 0,-1300, bgSrcTutorial.w *4, bgSrcTutorial.h * 4 };
	swamp1Dst = { + 350, -150,swamp1Src.w * 2 ,swamp1Src.h * 2  };
}
