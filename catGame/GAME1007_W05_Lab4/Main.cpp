
// SDL includes pasted for convenience. Move/copy to relevant files.
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <ctime>
#include "Engine.h"

int main(int argc, char* argv[])
{
	return Engine::Instance().Run();
}