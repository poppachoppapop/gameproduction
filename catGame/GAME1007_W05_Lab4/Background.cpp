#include "Background.h"

Background::Background(): bgSrcTutorial({0,0,768,960})
{
	bgDst = { 700,0, bgSrcTutorial.w *2, bgSrcTutorial.h * 2 };
}
