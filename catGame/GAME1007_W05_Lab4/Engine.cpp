#include "Engine.h"
#include "player1.h"
#include "enemy.h"
#include "items.h"
#include "Background.h"
#include "StateManager.h"
#include "States.h"
#include <ctime>

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
					bgTutorial = IMG_LoadTexture(m_pRenderer, "bgs/tutorial.png");
					npcTxtr = IMG_LoadTexture(m_pRenderer, "art/catDude.png");
				}
				else return false; // Image init failed.
			}
			else return false; // Renderer creation failed.
		}
		else return false; // Window creation failed.
		if (Mix_Init(MIX_INIT_MP3) != 0) {
			Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096); // make it 2048 if audio is lagging
			Mix_AllocateChannels(16);
			//stepSfx = Mix_LoadWAV("sfx/step.wav");
			//turnSfx = Mix_LoadWAV("sfx/turn.wav");
			//deathSfx = Mix_LoadWAV("sfx/dedEnemy.wav");
			//hurtSfx = Mix_LoadWAV("sfx/enemyHurt.wav");
			//powerSfx = Mix_LoadWAV("sfx/powerUp.wav");
			//talk = Mix_LoadWAV("sfx/texttalk.wav");
			//winscore = Mix_LoadWAV("sfx/scorewin.wav");
			//hehe = Mix_LoadWAV("sfx/killsound.wav");
			//projectileRock = Mix_LoadWAV("sfx/rocksound.wav");
			//aoeSound = Mix_LoadWAV("sfx/aoeAbility.wav");
			//dashing = Mix_LoadWAV("sfx/dashSound.wav");
			//dashMeow = Mix_LoadWAV("sfx/dashMeow.wav");
			//Mix_VolumeChunk(dashing, 25);
			//Mix_VolumeChunk(aoeSound, 50);
			//Mix_VolumeChunk(projectileRock, 50);
			//Mix_VolumeChunk(hehe, 20);
			//maintheme = Mix_LoadMUS("Aud/GameTheme.mp3");
			
		}
		TTF_Init();
	}
	else return false; // initalization failed.
	m_fps = (Uint32)round(1.0 / (double)FPS * 1000); // Converts FPS into milliseconds, e.g. 16.67
	m_keystates = SDL_GetKeyboardState(nullptr);

	srand(time(NULL));
	//sounds
	//Mix_PlayMusic(maintheme, -1);
	Mix_VolumeMusic(12); //0-128
	Mix_Volume(-1, 50);	
	
	//playerpew.reserve(4);
	//dumbie.reserve(4);

	////Text box and score stuff
	//font = TTF_OpenFont("fonts/font.ttf", 24);
	//White = { 255, 255, 255 };

	//textBoxRect = { 20, HEIGHT -190, 500, 50 };
	//textBoxBorder = { 10, HEIGHT - 200, WIDTH - 20, 190 };

	//scoreRect = { 800, 10, 150, 40 };
	//
	//surfaceMessage = TTF_RenderText_Solid(font, message, White);
	//dummyScore = TTF_RenderText_Solid(font, scoreMessage, White);
	//
	//Message = SDL_CreateTextureFromSurface(m_pRenderer, surfaceMessage);
	//Score = SDL_CreateTextureFromSurface(m_pRenderer, dummyScore);

	STMA::ChangeState(new TitleState());

	cout << "Initialization successful!" << endl;
	m_running = true;
	return true;

	return 0;
}

void Engine::Clean()
{
	cout << "Cleaning engine..." << endl;
	STMA::Quit();
	//for (unsigned i = 0; i < dumbie.size(); i++)
	//{
	//	delete dumbie[i];
	//	dumbie[i] = nullptr;
	//}
	//for (unsigned i = 0; i < playerpew.size(); i++)
	//{
	//	delete playerpew[i];
	//	playerpew[i] = nullptr;
	//}
	//playerpew.clear();
	//playerpew.shrink_to_fit();	
	//SDL_DestroyRenderer(m_pRenderer);
	//SDL_DestroyWindow(m_pWindow);
	//SDL_DestroyTexture(dumbieTxtr);
	//Mix_FreeChunk(stepSfx);
	//Mix_FreeChunk(deathSfx);
	//Mix_FreeChunk(turnSfx);
	//Mix_FreeMusic(maintheme);
	Mix_CloseAudio();
	TTF_Quit();
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
	//stepSoundTimer++; turnSoundTimer++;
	//dashCooldown++;
	//textBoxTimer++;
	//dumbieTimerMax -= 0.1;
	//bg1.bgDst.x -= speedx;
	//bg1.bgDst.y -= speedy;
	//plr1.Update();
	//catDude.Update();
	//rockCooldown++;
	//spcooldown++;
	//
	////NPC
	//catDude.npcDst.x = bg1.bgDst.x + 1000;
	//catDude.npcDst.y = bg1.bgDst.y + 1350;

	//if (plr1.plrDst.x < bg1.bgDst.x -50)
	//	bg1.bgDst.x = plr1.plrDst.x + 50;
	//if (plr1.plrDst.y < bg1.bgDst.y + 630)
	//	bg1.bgDst.y = plr1.plrDst.y - 630;

	//if (spawnDummies) {
	//	dummiesTimer++;
	//	if (dummiesTimer == 2000) {
	//		Mix_PlayChannel(-1, winscore, 0);
	//		tempStr = "Your Score is " + to_string(score);
	//		strcpy_s(message, tempStr.c_str());
	//		surfaceMessage = TTF_RenderText_Solid(font, message, White);
	//		Message = SDL_CreateTextureFromSurface(m_pRenderer, surfaceMessage);
	//		spawnDummies = false;
	//		renderTextBox = true;
	//		dummiesTimer = 0;
	//		score = 0;
	//		tempStr = "Score: " + to_string(score);
	//		strcpy_s(scoreMessage, tempStr.c_str());
	//		dummyScore = TTF_RenderText_Solid(font, scoreMessage, White);
	//		Score = SDL_CreateTextureFromSurface(m_pRenderer, dummyScore);
	//		dumbieTimerMax = 300;
	//	}
	//}

	//if (SDL_HasIntersection(&plr1.plrDst, &catDude.npcDst)) {
	//	if (KeyDown(SDL_SCANCODE_E)) {
	//		if (textBoxTimer > 10) {
	//			Mix_PlayChannel(-1, talk, 0);
	//			renderTextBox = true;
	//			if (textBoxCounter == 1) {
	//				strcpy_s(message, "I will start Spawning Dummies");
	//				surfaceMessage = TTF_RenderText_Solid(font, message, White);
	//				Message = SDL_CreateTextureFromSurface(m_pRenderer, surfaceMessage);
	//			}
	//			else if (textBoxCounter == 2) {
	//				strcpy_s(message, "Try and get the highest score!");
	//				surfaceMessage = TTF_RenderText_Solid(font, message, White);
	//				Message = SDL_CreateTextureFromSurface(m_pRenderer, surfaceMessage);
	//			}
	//			else if (textBoxCounter == 3) {
	//				spawnDummies = true;
	//				renderTextBox = false;
	//				textBoxCounter = 0;
	//				dumbieTimerMax = 300;
	//			}
	//			textBoxCounter++;
	//			textBoxTimer = 0;
	//		}
	//	}

	//}


	//	//For special Ability1
	//	if (KeyDown(SDL_SCANCODE_SPACE))
	//	{
	//		if (spcooldown > 200)
	//		{
	//			Mix_PlayChannel(-1, aoeSound, 0);
	//			spcooldown = 0;
	//			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, 10, 'y'));
	//			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, 10 * -1, 'y'));
	//			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, 10, 'x'));
	//			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, 10 * -1, 'x'));
	//			playerpew.shrink_to_fit();
	//		}
	//	}

	//	//For throwing Rock
	//	if (KeyDown(SDL_SCANCODE_UP))
	//	{
	//		if (rockCooldown > 50) {
	//			Mix_PlayChannel(-1, projectileRock, 0);
	//			rockCooldown = 0;
	//			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, rockSpeed * -1, 'y'));
	//			playerpew.shrink_to_fit();
	//		}
	//	}
	//	else if (KeyDown(SDL_SCANCODE_DOWN))
	//	{
	//		
	//		if (rockCooldown > 50) {
	//			Mix_PlayChannel(-1, projectileRock, 0);
	//			rockCooldown = 0;
	//			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, rockSpeed, 'y'));
	//			playerpew.shrink_to_fit();
	//		}
	//	}
	//	else if (KeyDown(SDL_SCANCODE_LEFT))
	//	{

	//		if (rockCooldown > 50) {
	//			Mix_PlayChannel(-1, projectileRock, 0);
	//			rockCooldown = 0;
	//			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, rockSpeed * -1, 'x'));
	//			playerpew.shrink_to_fit();
	//		}
	//	}
	//	else if (KeyDown(SDL_SCANCODE_RIGHT))
	//	{

	//		if (rockCooldown > 50) {
	//			Mix_PlayChannel(-1, projectileRock, 0);
	//			rockCooldown = 0;
	//			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, rockSpeed, 'x'));
	//			playerpew.shrink_to_fit();
	//		}
	//	}


	//	if (speedx > plr1.plrSpd)
	//		speedx = plr1.plrSpd;
	//	if (speedy > plr1.plrSpd)
	//		speedy = plr1.plrSpd;
	//	if (speedy * -1 > plr1.plrSpd)
	//		speedy = plr1.plrSpd * -1;
	//	if (speedx * -1 > plr1.plrSpd)
	//		speedx = plr1.plrSpd * -1;

	//	//Dash
	//	if (dashCooldown > 100) {
	//		if (KeyDown(SDL_SCANCODE_LSHIFT)) {
	//			Mix_PlayChannel(-1, dashing, 0);
	//			dashPressed = true;
	//			dashTimer = 0;
	//			dashCooldown = 0;
	//		}
	//	}
	//	dashTimer++;
	//	if (dashPressed) {
	//		plr1.plrSpd = plr1.plrDsh;
	//		if (dashTimer > 10) {
	//			dashPressed = false;
	//			dashTimer = 0;
	//			dashCooldown = 0;
	//			plr1.plrSpd = 5;
	//			cout << tempSpeed << endl;
	//		}

	//	}

	//	//YAXIS

	//	if (KeyDown(SDL_SCANCODE_S)) {

	//		speedy += speedAcc;
	//		plr1.state = 1;

	//	}

	//	if (KeyDown(SDL_SCANCODE_W)) {

	//		speedy -= speedAcc;
	//		plr1.state = 2;
	//	}

	//	//XAXIS
	//	if (KeyDown(SDL_SCANCODE_A)) {
	//		speedx -= speedAcc;
	//		plr1.state = 3;
	//	}

	//	if (KeyDown(SDL_SCANCODE_D)) {
	//		speedx += speedAcc;
	//		plr1.state = 4;
	//	}

	//	//Slow Down!
	//	if (!KeyDown(SDL_SCANCODE_D) && !KeyDown(SDL_SCANCODE_A)) {
	//		if (speedx > 0)
	//			speedx--;
	//		else if (speedx < 0) {
	//			speedx++;
	//		}
	//	}
	//	if (!KeyDown(SDL_SCANCODE_W) && !KeyDown(SDL_SCANCODE_S)) {
	//		if (speedy > 0)
	//			speedy--;
	//		else if (speedy < 0) {
	//			speedy++;
	//		}
	//	}
	//	if (!KeyDown(SDL_SCANCODE_W) && !KeyDown(SDL_SCANCODE_S) && !KeyDown(SDL_SCANCODE_D) && !KeyDown(SDL_SCANCODE_A)) {
	//		plr1.state = 0;

	//	}

	//	//delete rock after off screen and move rock
	//	for (unsigned i = 0; i < playerpew.size(); i++)
	//	{
	//		playerpew[i]->Update();
	//		playerpew[i]->rockDst.x -= speedx;
	//		playerpew[i]->rockDst.y -= speedy;

	//		if (playerpew[i]->rockDst.x >= WIDTH || playerpew[i]->rockDst.x <= -64 || playerpew[i]->rockDst.y >= HEIGHT || playerpew[i]->rockDst.y <= -64)
	//		{
	//			delete playerpew[i];
	//			playerpew[i] = nullptr;
	//			playerpew.erase(playerpew.begin() + i);
	//			playerpew.shrink_to_fit();
	//			break;
	//		}
	//	}

	//	//dumbie spawning stuff
	//	dumbietimer++;
	//	
	//	if (spawnDummies) {
	//		if (dumbietimer >= dumbieTimerMax)
	//		{
	//			dumbietimer = 0;

	//			dumbie.push_back(new Enemy(bg1.bgDst.x + rand() % 1000 + 200, bg1.bgDst.y + rand() % 500 + 750, 3));
	//			dumbie.shrink_to_fit();
	//			cout << "spawning dumbie" << endl;
	//		}
	//	}

	//	//hitbox stuff/Collision
	//	for (unsigned i = 0; i < playerpew.size(); i++)
	//	{
	//		for (unsigned j = 0; j < dumbie.size(); j++)
	//		{
	//			if (SDL_HasIntersection(&playerpew[i]->rockDst, &dumbie[j]->enemyDst)) //AABB Check
	//			{
	//				cout << "catboy hits dumbie" << endl;
	//				Mix_PlayChannel(-1, hurtSfx, 0);
	//				delete playerpew[i];
	//				playerpew[i] = nullptr;
	//				playerpew.erase(playerpew.begin() + i);
	//				playerpew.shrink_to_fit();
	//				//set dumbie hp
	//				dumbie[j]->setHp(dumbie[j]->getHp() - playerDamage);
	//				break;
	//			}
	//		}
	//	}
	//	//delete dumbie when at 0 hp
	//	for (unsigned i = 0; i < dumbie.size(); i++)
	//	{
	//		//updates healthbar
	//		dumbie[i]->update();
	//		dumbie[i]->enemyDst.x -= speedx;
	//		dumbie[i]->enemyDst.y -= speedy;

	//		//deletes enemy if dead
	//		if (dumbie[i]->getHp() <= 0) {
	//			Mix_PlayChannel(-1, deathSfx, 0);
	//			delete dumbie[i];
	//			dumbie[i] = nullptr;
	//			dumbie.erase(dumbie.begin() + i);
	//			dumbie.shrink_to_fit();
	//			score++;
	//			tempStr = "Score: " + to_string(score);
	//			strcpy_s(scoreMessage,tempStr.c_str());
	//			dummyScore = TTF_RenderText_Solid(font, scoreMessage, White);
	//			Score = SDL_CreateTextureFromSurface(m_pRenderer, dummyScore);
	//		}
	//	}
	//	
	//	
	//	cout << plr1.plrDst.x - bg1.bgDst.x << " - " << plr1.plrDst.y - bg1.bgDst.y << endl;
	//	//for items
	//	itemSpawnTimer++;
	//	if (itemSpawnTimer == 1000) {
	//		//itemSpawnTimer = 0;
	//		item1.push_back(new Items(1, bg1.bgDst.x + 1075, bg1.bgDst.y + 1550));
	//		item1.shrink_to_fit();
	//	}
	//	for (unsigned i = 0; i < item1.size(); i++)
	//	{
	//		item1[i]->item.x -= speedx;
	//		item1[i]->item.y -= speedy;

	//		if (SDL_HasIntersection(&plr1.plrDst, &item1[i]->item)) //AABB Check
	//		{
	//			Mix_PlayChannel(-1, powerSfx, 0);
	//			delete item1[i];
	//			item1[i] = nullptr;
	//			item1.erase(item1.begin() + i);
	//			item1.shrink_to_fit();
	//			playerDamage++;

	//		}
	//		
	//	}
		STMA::Update();
}

void Engine::Render()
{
	//SDL_SetRenderDrawColor(m_pRenderer, 0, 200, 200, 255);
	//SDL_RenderClear(m_pRenderer);
	//// Any drawing here...
	////SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
	////SDL_RenderFillRect(m_pRenderer, &plr1.plrDst);

	////Background
	//SDL_RenderCopy(m_pRenderer, bgTutorial, &bg1.bgSrcTutorial, &bg1.bgDst);

	//if (plr1.state == 0)
	//	SDL_RenderCopy(m_pRenderer, plrTxtr, &plr1.plrFrontIdle, &plr1.plrDst);
	//else if (plr1.state == 1)
	//	SDL_RenderCopy(m_pRenderer, plrTxtr, &plr1.plrMoveDown, &plr1.plrDst);
	//else if (plr1.state == 2)
	//	SDL_RenderCopy(m_pRenderer, plrTxtr, &plr1.plrMoveUp, &plr1.plrDst);
	//else if (plr1.state == 3)
	//	SDL_RenderCopy(m_pRenderer, plrTxtr, &plr1.plrMoveLeft, &plr1.plrDst);
	//else if (plr1.state == 4)
	//	SDL_RenderCopy(m_pRenderer, plrTxtr, &plr1.plrMoveRight, &plr1.plrDst);

	////NPC
	//SDL_RenderCopyEx(m_pRenderer, npcTxtr, &catDude.npcSrc, &catDude.npcDst, NULL, NULL, SDL_FLIP_HORIZONTAL);

	////rock	
	//for (unsigned i = 0; i < playerpew.size(); i++)
	//{
	//	SDL_RenderCopy(m_pRenderer, rockTxtr, 
	//		&(playerpew[i]->rockSrc), &(playerpew[i]->rockDst));
	//}
	//
	////item
	//for (unsigned i = 0; i < item1.size(); i++)
	//{
	//	SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
	//	SDL_RenderFillRect(m_pRenderer, &item1[i]->item);
	//}
	////dumbie
	//for (unsigned i = 0; i < dumbie.size();i++)
	//{
	//	SDL_RenderCopyEx(m_pRenderer, dumbieTxtr, &dumbie[i]->enemySrc, &dumbie[i]->enemyDst, 00.0, NULL, SDL_FLIP_NONE);
	//	//dumbie hp
	//	SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
	//	SDL_RenderFillRect(m_pRenderer, &dumbie[i]->healthBar);
	//}

	////text box
	//if (renderTextBox) {
	//	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	//	SDL_RenderFillRect(m_pRenderer, &textBoxBorder);
	//	SDL_RenderCopy(m_pRenderer, Message, NULL, &textBoxRect);
	//}

	////score text
	//if (spawnDummies) {
	//	SDL_RenderCopy(m_pRenderer, Score, NULL, &scoreRect);
	//}
	//
	//SDL_RenderPresent(m_pRenderer); // Flip buffers - send data to window.
	STMA::Render();
}

void Engine::Sleep()
{
	m_end = SDL_GetTicks();
	m_delta = m_end - m_start; // 1055 - 1050 = 5ms
	if (m_delta < m_fps)
		SDL_Delay(m_fps - m_delta);
}

Engine& Engine::Instance() // No static keyword required.
{
	static Engine instance; // Creating an object of Engine. Magic statics.
	return instance;
}

int Engine::Run()
{
	if (m_running == true)
	{
		return 1;
	}
	// Start and run the "engine"
	if (Init("Cat Nipped!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, NULL) == false)
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


