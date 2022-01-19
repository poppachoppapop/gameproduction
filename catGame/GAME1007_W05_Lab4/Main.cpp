/*******************************************************************************
* File Name   : GAME_M2_OcampoPorritt
* Description : Moving Plane Around screen and put a background
* Author      :	Jeremy Porritt and Sydney Ocampo
* Created     :	11/21/2021
* Modified    :	11/21/2021
*******************************************************************************/

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
	Engine game;
	return game.Run();
}