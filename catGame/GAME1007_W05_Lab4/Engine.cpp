#include "Engine.h"
#include "player1.h"

Dumbie::Dumbie(int x, int y) :dumbieSrc({0,0,69,69})
{
	//random dumie spawn
	dumbieDst= { rand() % 1000,rand() % 900,dumbieSrc.w, dumbieSrc.h };
}

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
					rockTxtr = IMG_LoadTexture(m_pRenderer, "art/Rocko100.png");
					dumbieTxtr = IMG_LoadTexture(m_pRenderer, "art/Dumbie.png");
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
			deathSfx = Mix_LoadWAV("sfx/dedEnemy.wav");
			maintheme = Mix_LoadMUS("Aud/TitleTheme.mp3");
			
		}
	}
	else return false; // initalization failed.
	m_fps = (Uint32)round(1.0 / (double)FPS * 1000); // Converts FPS into milliseconds, e.g. 16.67
	m_keystates = SDL_GetKeyboardState(nullptr);

	srand(time(NULL));
	//sounds
	Mix_PlayMusic(maintheme, -1);
	Mix_VolumeMusic(12); //0-128
	Mix_Volume(-1, 69);	
	
	//dumbieSrc = { 0,0,32,32 };
	//dumbietimer = 0;

	playerpew.reserve(4);
	dumbie.reserve(4);

	cout << "Initialization successful!" << endl;
	m_running = true;
	return true;

	return 0;
}

void Engine::Clean()
{
	cout << "Cleaning engine..." << endl;
	for (unsigned i = 0; i < dumbie.size(); i++)
	{
		delete dumbie[i];
		dumbie[i] = nullptr;
	}
	for (unsigned i = 0; i < playerpew.size(); i++)
	{
		delete playerpew[i];
		playerpew[i] = nullptr;
	}
	playerpew.clear();
	playerpew.shrink_to_fit();	
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyTexture(dumbieTxtr);
	Mix_FreeChunk(stepSfx);
	Mix_FreeChunk(deathSfx);
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
				}
			}
			if (event.key.keysym.sym == SDLK_a)
			{
				if (!Mix_Playing(7))
				{
					Mix_PlayChannel(7, stepSfx, -1);
				}
			}
			if (event.key.keysym.sym == SDLK_w)
			{
				if (!Mix_Playing(7))
				{
					Mix_PlayChannel(7, stepSfx, -1);
				}
			}
			if (event.key.keysym.sym == SDLK_d)
			{
				if (!Mix_Playing(7))
				{
					Mix_PlayChannel(7, stepSfx, -1);
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
	rockCooldown++;

	if (KeyDown(SDL_SCANCODE_UP))
	{
		upPressed = true;
		downPressed = false;
		leftPressed = false;
		rightPressed = false;
		if (upPressed && !downPressed && !leftPressed && !rightPressed && rockCooldown > 50) {
			rockCooldown = 0;
			rockDir.push_back(0);
			rockDir.shrink_to_fit();
			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30));
			playerpew.shrink_to_fit();
		}
	}
	else if (KeyDown(SDL_SCANCODE_DOWN))
	{
		upPressed = false;
		downPressed = true;
		leftPressed = false;
		rightPressed = false;
		if (!upPressed && downPressed && !leftPressed && !rightPressed && rockCooldown > 50) {
			rockCooldown = 0;
			rockDir.push_back(1);
			rockDir.shrink_to_fit();
			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30));
			playerpew.shrink_to_fit();
		}
	}
	else if (KeyDown(SDL_SCANCODE_LEFT))
	{
		upPressed = false;
		downPressed = false;
		leftPressed = true;
		rightPressed = false;
		if (!upPressed && !downPressed && leftPressed && !rightPressed && rockCooldown > 50) {
			rockCooldown = 0;
			rockDir.push_back(2);
			rockDir.shrink_to_fit();
			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30));
			playerpew.shrink_to_fit();
		}
	}
	else if (KeyDown(SDL_SCANCODE_RIGHT))
	{
		upPressed = false;
		downPressed = false;
		leftPressed = false;
		rightPressed = true;
		if (!upPressed && !downPressed && !leftPressed && rightPressed && rockCooldown > 50) {
			rockCooldown = 0;
			rockDir.push_back(3);
			rockDir.shrink_to_fit();
			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30));
			playerpew.shrink_to_fit();
		}
	}


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
	//cout << plr1.state << endl;
	
	// moving catboi rock	
		for (unsigned i = 0; i < playerpew.size(); i++)
		{
			playerpew[i]->Update(rockDir[i], rockSpeed);
		}

		//delete rock after collision
		for (unsigned i = 0; i < playerpew.size(); i++)
		{
			if (playerpew[i]->rockDst.x >= WIDTH || playerpew[i]->rockDst.x <= -64 || playerpew[i]->rockDst.y >= HEIGHT || playerpew[i]->rockDst.y <= -64)
			{
				rockDir.erase(rockDir.begin());
				rockDir.shrink_to_fit();
				delete playerpew[i];
				playerpew[i] = nullptr;
				playerpew.erase(playerpew.begin() + i);
				playerpew.shrink_to_fit();
				break;
			}
		}
		
		
		//dumbie spawning stuff
		dumbietimer++;
		if (dumbietimer >= FPS * DSPAWN)
		{
			dumbietimer = 0;
			srand(time(NULL));
			dumbie.push_back(new Dumbie(WIDTH + dumbieSrc.w, rand() % (HEIGHT - dumbieSrc.h)));
			dumbie.shrink_to_fit();
			cout << "spawning dumbie" << endl;
		}
		
		//hitbox stuff/Collision
		for (unsigned i = 0; i < playerpew.size(); i++)
		{
			
			for (unsigned j = 0; j < dumbie.size(); j++)
			{
				if (SDL_HasIntersection(&playerpew[i]->rockDst, &dumbie[j]->dumbieDst)) //AABB Check
				{
					rockDir.erase(rockDir.begin());
					rockDir.shrink_to_fit();
					cout << "catboy hits dumbie" << endl;
					Mix_PlayChannel(-1, deathSfx, 0);
					delete playerpew[i]; 
					playerpew[i] = nullptr; 
					playerpew.erase(playerpew.begin() + i); 
					playerpew.shrink_to_fit();
					delete dumbie[j];
					dumbie[j] = nullptr;
					dumbie.erase(dumbie.begin() + j);
					dumbie.shrink_to_fit();
					break;
				}
			}
		}
	
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
	
	
	//dumbie
	for (unsigned i = 0; i < dumbie.size();i++)
	{
		SDL_RenderCopyEx(m_pRenderer, dumbieTxtr, &dumbie[i]->dumbieSrc, &dumbie[i]->dumbieDst, 00.0, NULL, SDL_FLIP_NONE);

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

