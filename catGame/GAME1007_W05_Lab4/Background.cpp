#include "Background.h"

Background::Background(): bgSrcTutorial({0,0,384,480})
{
	bgDst = { 0,-700, bgSrcTutorial.w *4, bgSrcTutorial.h * 4 };
}
