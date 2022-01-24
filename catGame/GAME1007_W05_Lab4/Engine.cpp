#include "Engine.h"
#include "player1.h"

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
					plrTxtr = IMG_LoadTexture(m_pRenderer, "art/catboy.png");
					rockTxtr = IMG_LoadTexture(m_pRenderer, "art/Rock.png");
					//dumbie = IMG_LoadTexture(m_pRenderer, "art/Dumbie.png");
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
			maintheme = Mix_LoadMUS("Aud/TitleTheme.mp3");
			
		}
	}
	else return false; // initalization failed.
	m_fps = (Uint32)round(1.0 / (double)FPS * 1000); // Converts FPS into milliseconds, e.g. 16.67
	m_keystates = SDL_GetKeyboardState(nullptr);

	srand(time(NULL));
	//sounds
	Mix_PlayMusic(maintheme, -1);
	Mix_VolumeMusic(32); //0-128
	Mix_Volume(-1, 128);

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
	Mix_FreeChunk(stepSfx);
	Mix_FreeChunk(turnSfx);
	Mix_FreeMusic(maintheme);
	Mix_CloseAudio();
	Mix_Quit();
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
		case SDL_KEYDOWN:			
			if (event.key.keysym.sym == SDLK_s)
			{
				if (!Mix_Playing(7))
				{
					Mix_PlayChannel(7, stepSfx, -1);
					cout << "S" << endl;
				}
			}
			if (event.key.keysym.sym == SDLK_a)
			{
				if (!Mix_Playing(7))
				{
					Mix_PlayChannel(7, stepSfx, -1);
					cout << "A" << endl;
				}
			}
			if (event.key.keysym.sym == SDLK_w)
			{
				if (!Mix_Playing(7))
				{
					Mix_PlayChannel(7, stepSfx, -1);
					cout << "W" << endl;
				}
			}
			if (event.key.keysym.sym == SDLK_d)
			{
				if (!Mix_Playing(7))
				{
					Mix_PlayChannel(7, stepSfx, -1);
					cout << "D" << endl;
				}
			}			
			break;

		case SDL_KEYUP:
			
			if (event.key.keysym.sym == 's')
			{
				Mix_HaltChannel(7);
			}
			if (event.key.keysym.sym == 'a')
			{
				Mix_HaltChannel(7);
			}
			if (event.key.keysym.sym == 'w')
			{
				Mix_HaltChannel(7);
			}
			if (event.key.keysym.sym == 'd')
			{
				Mix_HaltChannel(7);
			}
			break;

			
		}
		
		
		if (event.key.keysym.sym == 13) // Enter
		{

			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30));
			playerpew.shrink_to_fit();
			cout << "YEET!";
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
	dashCooldown++;
	plr1.plrDst.x += speedx;
	plr1.plrDst.y += speedy;
	plr1.Update();
	
	if (speedx > plr1.plrSpd)
		speedx = plr1.plrSpd;
	if (speedy > plr1.plrSpd)
		speedy = plr1.plrSpd;
	if (speedy * -1 > plr1.plrSpd)
		speedy = plr1.plrSpd * -1;
	if (speedx * -1 > plr1.plrSpd)
		speedx = plr1.plrSpd * -1;

	//Dash
	if (dashCooldown > 100) {
		if (KeyDown(SDL_SCANCODE_LSHIFT)) {
			dashPressed = true;
			dashTimer = 0;
			dashCooldown = 0;
		}
	}
	dashTimer++;
	if (dashPressed) {
		plr1.plrSpd = plr1.plrDsh;
		if (dashTimer > 10) {
			dashPressed = false;
			dashTimer = 0;
			dashCooldown = 0;
			plr1.plrSpd = 5;
			cout << tempSpeed << endl;
		}

	}
	
	//YAXIS

	if (KeyDown(SDL_SCANCODE_S)) {
		
		speedy += speedAcc;
		plr1.state = 1;
		
	}
	
	if (KeyDown(SDL_SCANCODE_W)) {
		
		speedy -= speedAcc;
		plr1.state = 2;
	}

	//XAXIS
	if (KeyDown(SDL_SCANCODE_A)) {
		speedx -= speedAcc;
		plr1.state = 3;
	}

	if (KeyDown(SDL_SCANCODE_D)) {
		speedx += speedAcc;
		plr1.state = 4;
	}
	
	//Slow Down!
	if (!KeyDown(SDL_SCANCODE_D) && !KeyDown(SDL_SCANCODE_A)) {
		if (speedx > 0)
			speedx--;
		else if (speedx < 0) {
			speedx++;
		}
	}
	if (!KeyDown(SDL_SCANCODE_W) && !KeyDown(SDL_SCANCODE_S)) {
		if (speedy > 0)
			speedy--;
		else if (speedy < 0) {
			speedy++;
		}
	}
	if (!KeyDown(SDL_SCANCODE_W) && !KeyDown(SDL_SCANCODE_S) && !KeyDown(SDL_SCANCODE_D) && !KeyDown(SDL_SCANCODE_A)) {
		plr1.state = 0;
		
	}
	// moving catboi rock
	
		for (unsigned i = 0; i < playerpew.size(); i++)
		{
			playerpew[i]->Update(1);
		}
		for (unsigned i = 0; i < playerpew.size(); i++)
		{
			if (playerpew[i]->rockDst.x >= WIDTH - playerpew[i]->rockDst.w)
			{
				delete playerpew[i];
				playerpew[i] = nullptr;
				playerpew.erase(playerpew.begin() + i); 
				playerpew.shrink_to_fit();
				break;
			}
		}
		cout << plr1.state << endl;

	
	
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 200, 200, 255);
	SDL_RenderClear(m_pRenderer);
	// Any drawing here...
	//SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
	//SDL_RenderFillRect(m_pRenderer, &plr1.plrDst);
	
	if (plr1.state == 0)
		SDL_RenderCopy(m_pRenderer, plrTxtr, &plr1.plrFrontIdle, &plr1.plrDst);
	else if (plr1.state == 1)
		SDL_RenderCopy(m_pRenderer, plrTxtr, &plr1.plrMoveDown, &plr1.plrDst);
	else if (plr1.state == 2)
		SDL_RenderCopy(m_pRenderer, plrTxtr, &plr1.plrMoveUp, &plr1.plrDst);
	else if (plr1.state == 3)
		SDL_RenderCopy(m_pRenderer, plrTxtr, &plr1.plrMoveLeft, &plr1.plrDst);
	else if (plr1.state == 4)
		SDL_RenderCopy(m_pRenderer, plrTxtr, &plr1.plrMoveRight, &plr1.plrDst);

	
	//rock	
	for (unsigned i = 0; i < playerpew.size(); i++)
	{
		SDL_RenderCopy(m_pRenderer, rockTxtr, 
			&(playerpew[i]->rockSrc), &(playerpew[i]->rockDst));
	}
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
	if (Init("Cat Game!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, NULL) == false)
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

