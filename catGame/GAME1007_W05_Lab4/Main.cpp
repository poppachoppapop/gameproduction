
// SDL includes pasted for convenience. Move/copy to relevant files.
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Engine.h"
#include <ctime>
#include <vector>

int main(int argc, char* argv[])
{
	return Engine::Instance().Run();
}