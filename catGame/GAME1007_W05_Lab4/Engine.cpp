#include "Engine.h"

int Engine::Init(const char* title, int xPos, int yPos, int width, int height, int flags) {
	cout << "Initializing engine..." << endl;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) // If initialization is okay...
	{
		// Create the SDL window...
		cout << "First pass." << endl;
		m_pWindow = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (m_pWindow != nullptr)
		{
			// Create the SDL renderer...(back buffer)
			cout << "Second pass." << endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, NULL);
			if (m_pRenderer != nullptr)
			{
				if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0)
				{
					
					// Add check of texture pointer later...
				}
				else return false; // Image init failed.
			}
			else return false; // Renderer creation failed.
		}
		else return false; // Window creation failed.
		if (Mix_Init(MIX_INIT_MP3) != 0) {
			Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096); // make it 2048 if audio is lagging
			Mix_AllocateChannels(16);
			stepSfx = Mix_LoadWAV("sfx/step.wav");
			turnSfx = Mix_LoadWAV("sfx/turn.wav");
			
		}
	}
	else return false; // initalization failed.
	m_fps = (Uint32)round(1.0 / (double)FPS * 1000); // Converts FPS into milliseconds, e.g. 16.67
	m_keystates = SDL_GetKeyboardState(nullptr);

	srand(time(NULL));

	cout << "Initialization successful!" << endl;
	m_running = true;
	return true;

	return 0;
}

void Engine::Clean()
{
	cout << "Cleaning engine..." << endl;
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	IMG_Quit();
	SDL_Quit();
}

void Engine::Wake()
{
	m_start = SDL_GetTicks();
}

void Engine::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_running = false;
			break;
		}
	}
}

bool Engine::KeyDown(SDL_Scancode c)
{
	if (m_keystates != nullptr)
	{
		if (m_keystates[c] == 1) // Key we're testing for is down.
			return true;
	}
	return false;
}

void Engine::Update()
{
	stepSoundTimer++; turnSoundTimer++;
	
	//YAXIS
	if (KeyDown(SDL_SCANCODE_S)) {
		speedAccy+= 1;
		plr1.plr.y += speedAccy;
		if (speedAccy > plr1.plrSpd)
			speedAccy = plr1.plrSpd;
		lastPressedS = true; 
		if (stepSoundTimer > 20) {
			Mix_PlayChannel(1, stepSfx, 0);
			stepSoundTimer = 0;
		}
	}
	else if (!KeyDown(SDL_SCANCODE_S) && lastPressedS) {
		plr1.plr.y += speedAccy;
		speedAccy -= 1.5;
		if (speedAccy <= 0) {
			speedAccy = 0;
			lastPressedS = false;
		}
	}
	if (KeyDown(SDL_SCANCODE_W)) {
		speedAccy += 1;
		plr1.plr.y -= speedAccy;
		if (speedAccy > plr1.plrSpd)
			speedAccy = plr1.plrSpd;
		lastPressedW = true;
		if (stepSoundTimer > 20) {
			Mix_PlayChannel(1, stepSfx, 0);
			stepSoundTimer = 0;
		}
	}
	else if (!KeyDown(SDL_SCANCODE_W) && lastPressedW) {
		plr1.plr.y -= speedAccy;
		speedAccy -= 1.5;
		if (speedAccy <= 0) {
			speedAccy = 0;
			lastPressedW = false;
		}
	}
	

	//XAXIS
	if (KeyDown(SDL_SCANCODE_A)) {
		speedAccx += 1;
		plr1.plr.x -= speedAccx;
		if (speedAccx > plr1.plrSpd)
			speedAccx = plr1.plrSpd;
		lastPressedA = true;
		if (stepSoundTimer > 20) {
			Mix_PlayChannel(1, stepSfx, 0);
			stepSoundTimer = 0;
		}
	}
	else if (!KeyDown(SDL_SCANCODE_A) && lastPressedA) {
		plr1.plr.x -= speedAccx;
		speedAccx -= 1.5;
		if (speedAccx <= 0) {
			speedAccx = 0;
			lastPressedA = false;
		}
	}
	if (KeyDown(SDL_SCANCODE_D)) {
		speedAccx += 1;
		plr1.plr.x += speedAccx;
		if (speedAccx > plr1.plrSpd)
			speedAccx = plr1.plrSpd;
		lastPressedD = true;
		if (stepSoundTimer > 20) {
			Mix_PlayChannel(1, stepSfx, 0);
			stepSoundTimer = 0;
		}
	}
	else if (!KeyDown(SDL_SCANCODE_D) && lastPressedD) {
		plr1.plr.x += speedAccx;
		speedAccx -= 1.5;
		if (speedAccx <= 0) {
			speedAccx = 0;
			lastPressedD = false;
		}
	}
	
	/*if (!KeyDown(SDL_SCANCODE_D) && !KeyDown(SDL_SCANCODE_A) && !KeyDown(SDL_SCANCODE_W) && !KeyDown(SDL_SCANCODE_S)) {
		
	}*/
	
	
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer);
	// Any drawing here...
	SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(m_pRenderer, &plr1.plr);

	SDL_RenderPresent(m_pRenderer); // Flip buffers - send data to window.
}

void Engine::Sleep()
{
	m_end = SDL_GetTicks();
	m_delta = m_end - m_start; // 1055 - 1050 = 5ms
	if (m_delta < m_fps)
		SDL_Delay(m_fps - m_delta);
}

int Engine::Run()
{
	if (m_running == true)
	{
		return 1;
	}
	// Start and run the "engine"
	if (Init("GAME1007 M2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, NULL) == false)
	{
		return 2;
	}
	// We passed our initial checks, start the loop!
	while (m_running == true)
	{
		Wake();
		HandleEvents(); // Input
		Update();       // Processing
		Render();       // Output
		if (m_running == true)
			Sleep();
	}
	Clean();
	return 0;
}

