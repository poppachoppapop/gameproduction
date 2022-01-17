#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include <ctime>
#include <vector>
#define FPS 60.0
#define WIDTH 1024
#define HEIGHT 768

using namespace std;

// g is global variables
bool g_running = false;
//GLobal unassigned 32 bit integer
Uint32 g_start, g_end, g_delta, g_fps;
//Holds key states
const Uint8* g_keystates;
// * points variable to window
SDL_Window* g_pWindow;
SDL_Renderer* g_pRenderer;


// Init function. Sets up SDL and all subsystems and other (dynamic) memory allocation.
int Init(const char* title, int xPos, int yPos, int width, int height, int flags)
{
	cout << "Initializing game..." << endl;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) { // if initialization is ok

		//try to create SDL_Window
		g_pWindow = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (g_pWindow != nullptr) { // window creation passes
			//try to create SDL_Renderer
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
			if (g_pRenderer != nullptr) {
				//do later
			}
			else return false; //REnder failed to init

		}
		else return false; //Window failed to init

	}
	else return false; // init failed

	//if everything is okay, we are here :)

	g_fps = (Uint32)round(1 / (double)FPS * 1000);
	g_keystates = SDL_GetKeyboardState(nullptr);
	cout << "Initialization succesful" << endl;
	g_running = true;

	return true;
}

// HandleEvents function. Gets input from user, e.g. mouse/keyboard/gamepad events.
void HandleEvents()
{
	cout << "Getting input..." << endl;
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT: // Pressing x of the window
			g_running = false;
			break;
		}
	}
}

bool KeyDown(SDL_Scancode c) {// checks if keys are down

	if (g_keystates != nullptr) {
		
		if (g_keystates[c] == 1) // key we are testing for is down
			return true;
	}
	return false;

}

// Update function. Moves objects, performs physics, e.g. projectiles, gravity, collisions.
void Update()
{
	cout << "Updating game..." << endl;
	if (KeyDown(SDL_SCANCODE_W))
		cout << "w is pressed" << endl;
	
}

// Render function. Renders changes in game objects to window.
void Render()
{
	cout << "Rendering changes to window..." << endl;
	SDL_SetRenderDrawColor(g_pRenderer, 135, 206, 235, 255);
	SDL_RenderClear(g_pRenderer);
	//Any drawing goes here



	SDL_RenderPresent(g_pRenderer); // flip buffers, send data to window
}

// Clean function. De-initialize SDL and de-allocate memory.
void Clean()
{
	cout << "Cleaning up..." << endl;
	SDL_DestroyRenderer(g_pRenderer);
	SDL_DestroyWindow(g_pWindow);
	SDL_Quit();
}

void Wake() {
	g_start = SDL_GetTicks(); // Gets milliseconds since initialization
}

void Sleep() {
	g_end = SDL_GetTicks();
	g_delta = g_end - g_start; // 1055 - 1050 = 5ms
	if (g_delta < g_fps) // gfps is 17ms (if (5ms < 17ms))
		SDL_Delay(g_fps - g_delta); // (delays for 12 ms)
	//this creates a perfectly fixed framerate
}




// Run function. Contains the primary game loop.
int Run()
{
	if (g_running == true) { // if engine is already running
		return 1;
	}
	if (Init("GAME1007_M1_PorrittJeremy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0) == false) { // if initialization fails
		return 2;
	}
	//IF INIT PASSES WE ARE HERE
	

	while (g_running) // Primary game loop. "frame"
	{
		Wake();
		HandleEvents(); // Input.
		Update(); // Processing.
		Render(); // Output.
		if (g_running == true) 
			Sleep();
		
	}
	Clean();
	return 0;
}

// main function. Entry point in every C++ program.
int main(int argc, char* argv[]) //SDL main is purple
{
	
	return Run();
}

