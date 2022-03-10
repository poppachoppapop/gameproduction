#include "States.h"
#include "StateManager.h"
#include "Engine.h"
#include "EventManager.h"
#include "Items.h"
#include "Background.h"
#include "NPC.h"
#include <iostream>
#include "enemy.h"
#include "player1.h"

using namespace std;


void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

TitleState::TitleState() :bg1Ani({ 0,0,256,198 }), frameCtr(0), frameMax(7), spriteIdx(0), spriteMax(4) {}


void TitleState::Enter()
{	
		cout << "enter titlestate" << endl;	
		Titletheme = Mix_LoadMUS("aud/Titletheme.mp3");//gametheme
		TitleScreen = IMG_LoadTexture(Engine::Instance().GetRenderer(), "bgs/raftscreen.png");
		//bgSrc = { 0,0,1024,768 };
		Mix_PlayMusic(Titletheme, -1);
		Mix_VolumeMusic(24); //0-128
		
}

void TitleState::Update()
{
	
	//bg1Ani = { 0,0,256,198 };
	if (state == 0)
	{	
		spriteMax = 4;
		if (spriteIdx > 4)
			spriteIdx = 0;
		if (frameCtr++ == frameMax)
		{
			frameCtr = 0;
			if (++spriteIdx == spriteMax)
			{
				spriteIdx = 0;
			}
			bg1Ani.x = 0 + bg1Ani.w * spriteIdx;
		}
	}
	
	if (Engine::Instance().KeyDown(SDL_SCANCODE_RETURN))
	{

		cout << "changing to gamestate" << endl;
		STMA::ChangeState(new GameState());
		return;
	}
}

void TitleState::Render()
{
	SDL_RenderClear(Engine::Instance().GetRenderer());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), TitleScreen,&bg1Ani,NULL);	
	if (dynamic_cast<TitleState*>(STMA::GetStates().back()))//if current state is gamestate
	State::Render();
}

void TitleState::Exit()
{
	cout << "exiting titlestate" << endl;
	Mix_FreeMusic(Titletheme);
	SDL_DestroyTexture(TitleScreen);
}



PauseState::PauseState(){}



void PauseState::Enter()
{
	
	cout << "entering pausestate" << endl;
	sleepingMaki = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/sleepingMaki.png");
	resumeButton = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/resumeButton.png");
	restartButton = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/restartButton.png");
	exitButton = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/exitButton.png");
	paused = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/paused.png");
	pauseBg = IMG_LoadTexture(Engine::Instance().GetRenderer(), "bgs/pauseBg.png");
	

	resumeButtonSrc = { 0 , 0, 92, 32 };
	restartButtonSrc = { 0 , 0, 92, 32 };
	exitButtonSrc = { 0 , 0, 92, 32 };
	pausedSrc = { 0, 0, 92, 32 };
	pausedBgSrc = { 0, 0, 128, 128 };

	resumeButtonDst = { 450, 475, 120, 48 };
	restartButtonDst = {450, 525, 120, 48};
	exitButtonDst = { 450, 575, 120, 48 };
	pausedDst = { 370, 165, 280, 128 };
	pausedBgDst = { 255, 128, 512, 512 };
}

void PauseState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_P))
		STMA::PopState();
	//resume button
	if (SDL_GetMouseState(&g_mousePos.x, &g_mousePos.y) == true && g_mousePos.x > resumeButtonDst.x && g_mousePos.x < resumeButtonDst.x + resumeButtonDst.w
		&& g_mousePos.y > resumeButtonDst.y && g_mousePos.y < resumeButtonDst.y + resumeButtonDst.h)
	{
		STMA::PopState();
	}
	//restart button
	if (SDL_GetMouseState(&g_mousePos.x, &g_mousePos.y) == true && g_mousePos.x > restartButtonDst.x && g_mousePos.x < restartButtonDst.x + restartButtonDst.w
		&& g_mousePos.y > restartButtonDst.y && g_mousePos.y < restartButtonDst.y + restartButtonDst.h)
	{
		STMA::ChangeState(new GameState());
	}
	//exit button
	if (SDL_GetMouseState(&g_mousePos.x, &g_mousePos.y) == true && g_mousePos.x > exitButtonDst.x && g_mousePos.x < exitButtonDst.x + exitButtonDst.w
		&& g_mousePos.y > exitButtonDst.y && g_mousePos.y < exitButtonDst.y + exitButtonDst.h)
	{
		Engine::Instance().Running() = false;
	}
}

void PauseState::Render()
{
	//1st render the gamestate
	STMA::GetStates().front()->Render();
	//now render the rest of pausestate
	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);

	//transparent background (filled rect)
	//SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 200);
	//SDL_Rect rect = { 255,128,512,512 };
	//SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rect);
	
	//SDL_RenderCopy(Engine::Instance().GetRenderer(), sleepingMaki, &plr1.plrFrontIdle, &plr1.plrDst);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), pauseBg, &pausedBgSrc, &pausedBgDst);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), sleepingMaki, &plr1.plrFrontIdle, &plr1.plrDst);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), resumeButton, &resumeButtonSrc, &resumeButtonDst);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), restartButton, &restartButtonSrc, &restartButtonDst);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), exitButton, &exitButtonSrc, &exitButtonDst);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), paused, &pausedSrc, &pausedDst);
	State::Render();
}

void PauseState::Exit()
{
	cout << "exiting pausestate" << endl;
	/*isPauseActive = false;*/
}



GameState::GameState() {}

void GameState::Enter()
{
	cout << "entering gamestate" << endl;
	plrTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/catboy.png");	
	rockTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/Rocko100.png");
	dumbieTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/Dumbie.png");
	bgTutorial = IMG_LoadTexture(Engine::Instance().GetRenderer(), "bgs/tutorial.png");
	npcTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/catDude.png");
	DragonFlyTxt = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/dragonfly.png");
	vineTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/vines.png");
	FrogTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/frogWalking7.png");



	stepSfx = Mix_LoadWAV("sfx/step.wav");
	turnSfx = Mix_LoadWAV("sfx/turn.wav");
	deathSfx = Mix_LoadWAV("sfx/dedEnemy.wav");
	hurtSfx = Mix_LoadWAV("sfx/enemyHurt.wav");
	powerSfx = Mix_LoadWAV("sfx/powerUp.wav");
	talk = Mix_LoadWAV("sfx/texttalk.wav");
	winscore = Mix_LoadWAV("sfx/scorewin.wav");
	hehe = Mix_LoadWAV("sfx/killsound.wav");
	projectileRock = Mix_LoadWAV("sfx/rocksound.wav");
	aoeSound = Mix_LoadWAV("sfx/aoeAbility.wav");
	dashing = Mix_LoadWAV("sfx/dashSound.wav");
	//dashMeow = Mix_LoadWAV("sfx/dashMeow.wav");
	Mix_VolumeChunk(dashing, 25);
	Mix_VolumeChunk(aoeSound, 50);
	Mix_VolumeChunk(projectileRock, 50);
	//Mix_VolumeChunk(hehe, 20);
	maintheme = Mix_LoadMUS("Aud/Gametheme.mp3");

	//sounds
	Mix_PlayMusic(maintheme, -1);
	Mix_VolumeMusic(12); //0-128
	Mix_Volume(-1, 50);

	playerpew.reserve(4);
	dumbie.reserve(4);

	//Text box and score stuff
	font = TTF_OpenFont("fonts/font.ttf", 24);
	White = { 255, 255, 255 };

	textBoxRect = { 20, HEIGHT - 190, 500, 50 };
	textBoxBorder = { 10, HEIGHT - 200, WIDTH - 20, 190 };

	scoreRect = { 800, 10, 150, 40 };
	blackRect = { 0 , 0 , 1024 , 768 };

	surfaceMessage = TTF_RenderText_Solid(font, message, White);
	dummyScore = TTF_RenderText_Solid(font, scoreMessage, White);

	Message = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), surfaceMessage);
	Score = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), dummyScore);

	vine.push_back(new Vines(bg1.bgDst.x + 400, bg1.bgDst.y + 1000));
	vine.push_back(new Vines(bg1.bgDst.x + 400, bg1.bgDst.y + 1200));
	vine.push_back(new Vines(bg1.bgDst.x + 400, bg1.bgDst.y + 1400));
	vine.shrink_to_fit();
	fly.push_back(new DragonFly(bg1.bgDst.x + 650, bg1.bgDst.y + 1000, 2));
	fly.shrink_to_fit();
	frog.push_back(new Frog(bg1.bgDst.x + 800, bg1.bgDst.y + 1000, 5));
	frog.shrink_to_fit();
}

void GameState::Update()
{
	//debug
	//cout << plr1.plrDst.x - bg1.bgDst.x << " - " << plr1.plrDst.y - bg1.bgDst.y << endl;
	if (!titleLoading) {
		if (!(fadeMod == 0))
			fadeMod-=fadeSpeed;
		if (fadeMod == 0)
			fadeMod == 0;

		if (plr1.plrHp <= 0)
		{
			STMA::ChangeState(new EndState());
			return;
		}
		if (EVMA::KeyPressed(SDL_SCANCODE_P))
		{
			cout << "Changing to PauseState" << endl;
			//pause the music track
			STMA::PushState(new PauseState());
			Mix_PauseMusic();
		}
		if (EVMA::KeyPressed(SDL_SCANCODE_1))
		{

			cout << "changing to lv1" << endl;
			STMA::ChangeState(new Levelone());
			return;
		}

		if (EVMA::KeyPressed(SDL_SCANCODE_X))
		{

			cout << "changing to endstate" << endl;
			STMA::ChangeState(new EndState());
			return;
		}

		if (EVMA::KeyHeld(SDL_SCANCODE_W))
		{
			if (!Mix_Playing(7))
			{
				Mix_PlayChannel(7, stepSfx, -1);
			}
		}
		if (EVMA::KeyHeld(SDL_SCANCODE_A))
		{
			if (!Mix_Playing(7))
			{
				Mix_PlayChannel(7, stepSfx, -1);
			}
		}
		if (EVMA::KeyHeld(SDL_SCANCODE_S))
		{
			if (!Mix_Playing(7))
			{
				Mix_PlayChannel(7, stepSfx, -1);
			}
		}
		if (EVMA::KeyHeld(SDL_SCANCODE_D))
		{
			if (!Mix_Playing(7))
			{
				Mix_PlayChannel(7, stepSfx, -1);
			}
		}

		//HALT!
		if (EVMA::KeyReleased(SDL_SCANCODE_S)) {
			Mix_HaltChannel(7);
		}

		if (EVMA::KeyReleased(SDL_SCANCODE_W)) {
			Mix_HaltChannel(7);
		}

		if (EVMA::KeyReleased(SDL_SCANCODE_A)) {
			Mix_HaltChannel(7);
		}

		if (EVMA::KeyReleased(SDL_SCANCODE_D)) {
			Mix_HaltChannel(7);
		}

		stepSoundTimer++; turnSoundTimer++;
		dashCooldown++;
		textBoxTimer++;
		dumbieTimerMax -= 0.1;
		plr1.Update();
		catDude.Update();
		rockCooldown++;
		spcooldown++;
		//NPC
		catDude.npcDst.x = bg1.bgDst.x + 1000;
		catDude.npcDst.y = bg1.bgDst.y + 1350;

		//wallcollision
		bool wallHitx = false;
		bool wallHity = false;
		if (plr1.plrDst.x < bg1.bgDst.x - 50)
		{
			bg1.bgDst.x = plr1.plrDst.x + 50;
			wallHitx = true;
			titleLoading = true;
		}
		if (plr1.plrDst.y < bg1.bgDst.y + 630) 
		{
			bg1.bgDst.y = plr1.plrDst.y - 630;
			wallHity = true;
		}
		bg1.bgDst.x -= speedx;
		bg1.bgDst.y -= speedy;

		//player
		if (!dashPressed)
			plr1.plrSpd = plr1.plrMaxSpd;
		//vines
		for (unsigned i = 0; i < vine.size(); i++)
		{
			if (!wallHitx)
				vine[i]->vineDst.x -= speedx;
			if (!wallHity)
				vine[i]->vineDst.y -= speedy;
			if (!dashPressed) {
				if (Util::distanceOffset(plr1.plrDst, vine[i]->vineDst) < 80) {
					plr1.plrSpd = 1;
				}
			}
		}
		//DragonFly
		for (unsigned i = 0; i < fly.size(); i++)
		{
			fly[i]->Update();
			if (!wallHitx)
				fly[i]->flyDst.x -= speedx;
			if (!wallHity)
				fly[i]->flyDst.y -= speedy;

			if (SDL_HasIntersection(&fly[i]->flyDst, &plr1.plrDst)) {
				plr1.takeDamage(1);
			}

			if (fly[i]->getHp() <= 0) {
				Mix_PlayChannel(-1, deathSfx, 0);
				delete fly[i];
				fly[i] = nullptr;
				fly.erase(fly.begin() + i);
				fly.shrink_to_fit();
			}
			for (unsigned j = 0; j < playerpew.size(); j++)
			{
				if (SDL_HasIntersection(&playerpew[j]->rockDst, &fly[i]->flyDst)) //AABB Check
				{
					Mix_PlayChannel(-1, hurtSfx, 0);
					delete playerpew[j];
					playerpew[j] = nullptr;
					playerpew.erase(playerpew.begin() + j);
					playerpew.shrink_to_fit();
					//set dumbie hp
					fly[i]->setHp(fly[i]->getHp() - playerDamage);
					break;
				}
			}

		}

		//frog
		for (unsigned i = 0; i < frog.size(); i++) {
			frog[i]->Update(plr1.plrDst);
			if (!wallHitx)
				frog[i]->frogDst.x -= speedx;
			if (!wallHity)
				frog[i]->frogDst.y -= speedy;
			for (unsigned j = 0; j < playerpew.size(); j++)
			{
				if (SDL_HasIntersection(&playerpew[j]->rockDst, &frog[i]->frogDst)) //AABB Check
				{
					Mix_PlayChannel(-1, hurtSfx, 0);
					delete playerpew[j];
					playerpew[j] = nullptr;
					playerpew.erase(playerpew.begin() + j);
					playerpew.shrink_to_fit();
					//set dumbie hp
					frog[i]->setHp(frog[i]->getHp() - playerDamage);
					break;
				}
			}
			if (SDL_HasIntersection(&frog[i]->frogDst, &plr1.plrDst)) {
				plr1.takeDamage(2);
			}
			if ((Util::distanceOffset(plr1.plrDst, frog[i]->frogDst) < 550)) {
				if (frog[i]->getShootTimer() == 0) {
					if (frog[i]->getDir() == 0)
						bub.push_back(new Bubble(frog[i]->frogDst.x, frog[i]->frogDst.y));
					if (frog[i]->getDir() == 1)
						bub.push_back(new Bubble(frog[i]->frogDst.x, frog[i]->frogDst.y));
					if (frog[i]->getDir() == 2)
						bub.push_back(new Bubble(frog[i]->frogDst.x, frog[i]->frogDst.y));
					if (frog[i]->getDir() == 3)
						bub.push_back(new Bubble(frog[i]->frogDst.x, frog[i]->frogDst.y));
				}
			}
			if (frog[i]->getHp() <= 0) {
				Mix_PlayChannel(-1, deathSfx, 0);
				delete frog[i];
				frog[i] = nullptr;
				frog.erase(frog.begin() + i);
				frog.shrink_to_fit();
			}
		}
		//bubble
		for (int i = 0; i < bub.size(); i++)
		{
			bub[i]->Update(plr1.plrDst);
			if (!wallHitx)
				bub[i]->bubbleDst.x -= speedx;
			if (!wallHity)
				bub[i]->bubbleDst.y -= speedy;
			if (Util::distanceOffset(plr1.plrDst, bub[i]->bubbleDst) < 50) {
				plr1.takeDamage(1);
				delete bub[i];
				bub[i] = nullptr;
				bub.erase(bub.begin() + i);
				bub.shrink_to_fit();
			}
		}


		//dummie
		for (unsigned i = 0; i < playerpew.size(); i++)
		{
			for (unsigned j = 0; j < dumbie.size(); j++)
			{
				if (SDL_HasIntersection(&playerpew[i]->rockDst, &dumbie[j]->enemyDst)) //AABB Check
				{
					//cout << "catboy hits dumbie" << endl;
					Mix_PlayChannel(-1, hurtSfx, 0);
					delete playerpew[i];
					playerpew[i] = nullptr;
					playerpew.erase(playerpew.begin() + i);
					playerpew.shrink_to_fit();
					//set dumbie hp
					dumbie[j]->setHp(dumbie[j]->getHp() - playerDamage);
					break;
				}
			}
		}

		if (spawnDummies) {
			dummiesTimer++;
			if (dummiesTimer == 2000) {
				Mix_PlayChannel(-1, winscore, 0);
				tempStr = "Your Score is " + to_string(score);
				strcpy_s(message, tempStr.c_str());
				surfaceMessage = TTF_RenderText_Solid(font, message, White);
				Message = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), surfaceMessage);
				spawnDummies = false;
				renderTextBox = true;
				dummiesTimer = 0;
				score = 0;
				tempStr = "Score: " + to_string(score);
				strcpy_s(scoreMessage, tempStr.c_str());
				dummyScore = TTF_RenderText_Solid(font, scoreMessage, White);
				Score = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), dummyScore);
				dumbieTimerMax = 300;
			}
		}

		if (SDL_HasIntersection(&plr1.plrDst, &catDude.npcDst)) {
			if (EVMA::KeyPressed(SDL_SCANCODE_E)) {
				if (textBoxTimer > 10) {
					Mix_PlayChannel(-1, talk, 0);
					renderTextBox = true;
					if (textBoxCounter == 1) {
						strcpy_s(message, "I will start Spawning Dummies");
						surfaceMessage = TTF_RenderText_Solid(font, message, White);
						Message = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), surfaceMessage);
					}
					else if (textBoxCounter == 2) {
						strcpy_s(message, "Try and get the highest score!");
						surfaceMessage = TTF_RenderText_Solid(font, message, White);
						Message = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), surfaceMessage);
					}
					else if (textBoxCounter == 3) {
						spawnDummies = true;
						renderTextBox = false;
						textBoxCounter = 0;
						dumbieTimerMax = 300;
					}
					textBoxCounter++;
					textBoxTimer = 0;
				}
			}

		}

		//For special Ability1
		if (EVMA::KeyPressed(SDL_SCANCODE_SPACE))
		{
			if (spcooldown > 200)
			{
				Mix_PlayChannel(-1, aoeSound, 0);
				spcooldown = 0;
				playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, 10, 'y'));
				playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, 10 * -1, 'y'));
				playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, 10, 'x'));
				playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, 10 * -1, 'x'));
				playerpew.shrink_to_fit();
			}
		}

		//For throwing Rock
		if (EVMA::KeyHeld(SDL_SCANCODE_UP))
		{
			if (rockCooldown > 50) {
				Mix_PlayChannel(-1, projectileRock, 0);
				rockCooldown = 0;
				playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, rockSpeed * -1, 'y'));
				playerpew.shrink_to_fit();
			}
		}
		else if (EVMA::KeyHeld(SDL_SCANCODE_DOWN))
		{

			if (rockCooldown > 50) {
				Mix_PlayChannel(-1, projectileRock, 0);
				rockCooldown = 0;
				playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, rockSpeed, 'y'));
				playerpew.shrink_to_fit();
			}
		}
		else if (EVMA::KeyHeld(SDL_SCANCODE_LEFT))
		{

			if (rockCooldown > 50) {
				Mix_PlayChannel(-1, projectileRock, 0);
				rockCooldown = 0;
				playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, rockSpeed * -1, 'x'));
				playerpew.shrink_to_fit();
			}
		}
		else if (EVMA::KeyHeld(SDL_SCANCODE_RIGHT))
		{

			if (rockCooldown > 50) {
				Mix_PlayChannel(-1, projectileRock, 0);
				rockCooldown = 0;
				playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, rockSpeed, 'x'));
				playerpew.shrink_to_fit();
			}
		}

		//Player Movement

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
			if (EVMA::KeyPressed(SDL_SCANCODE_LSHIFT)) {
				Mix_PlayChannel(-1, dashing, 0);
				dashPressed = true;
				dashTimer = 0;
				dashCooldown = 0;
			}
		}
		dashTimer++;
		if (dashPressed) {
			plr1.plrSpd = plr1.plrDsh;
			if (dashTimer > 15) {
				dashPressed = false;
				dashTimer = 0;
				dashCooldown = 0;
				plr1.plrSpd = 5;
			}

		}

		//YAXIS

		if (EVMA::KeyHeld(SDL_SCANCODE_S)) {

			speedy += speedAcc;
			plr1.state = 1;

		}

		if (EVMA::KeyHeld(SDL_SCANCODE_W)) {

			speedy -= speedAcc;
			plr1.state = 2;
		}

		//XAXIS
		if (EVMA::KeyHeld(SDL_SCANCODE_A)) {
			speedx -= speedAcc;
			plr1.state = 3;
		}

		if (EVMA::KeyHeld(SDL_SCANCODE_D)) {
			speedx += speedAcc;
			plr1.state = 4;
		}

		//Slow Down!
		if (!EVMA::KeyHeld(SDL_SCANCODE_D) && !EVMA::KeyHeld(SDL_SCANCODE_A)) {
			if (speedx > 0)
				speedx--;
			else if (speedx < 0) {
				speedx++;
			}
		}
		if (!EVMA::KeyHeld(SDL_SCANCODE_W) && !EVMA::KeyHeld(SDL_SCANCODE_S)) {
			if (speedy > 0)
				speedy--;
			else if (speedy < 0) {
				speedy++;
			}
		}
		if (!EVMA::KeyHeld(SDL_SCANCODE_W) && !EVMA::KeyHeld(SDL_SCANCODE_S) && !EVMA::KeyHeld(SDL_SCANCODE_D) && !EVMA::KeyHeld(SDL_SCANCODE_A)) {
			plr1.state = 0;
		}

		//delete rock after off screen and move rock
		for (unsigned i = 0; i < playerpew.size(); i++)
		{
			playerpew[i]->Update();
			if (!wallHitx)
				playerpew[i]->rockDst.x -= speedx;
			if (!wallHity)
				playerpew[i]->rockDst.y -= speedy;

			if (playerpew[i]->rockDst.x >= WIDTH || playerpew[i]->rockDst.x <= -64 || playerpew[i]->rockDst.y >= HEIGHT || playerpew[i]->rockDst.y <= -64)
			{
				delete playerpew[i];
				playerpew[i] = nullptr;
				playerpew.erase(playerpew.begin() + i);
				playerpew.shrink_to_fit();
				break;
			}
		}

		//dumbie spawning stuff
		dumbietimer++;

		if (spawnDummies) {
			if (dumbietimer >= dumbieTimerMax)
			{
				dumbietimer = 0;

				dumbie.push_back(new Enemy(bg1.bgDst.x + rand() % 1000 + 200, bg1.bgDst.y + rand() % 500 + 750, 3));
				dumbie.shrink_to_fit();
				cout << "spawning dumbie" << endl;
			}
		}

		//delete dumbie when at 0 hp
		for (unsigned i = 0; i < dumbie.size(); i++)
		{
			//updates healthbar
			dumbie[i]->update();
			if (!wallHitx)
				dumbie[i]->enemyDst.x -= speedx;
			if (!wallHity)
				dumbie[i]->enemyDst.y -= speedy;


			//deletes enemy if dead
			if (dumbie[i]->getHp() <= 0) {
				Mix_PlayChannel(-1, deathSfx, 0);
				delete dumbie[i];
				dumbie[i] = nullptr;
				dumbie.erase(dumbie.begin() + i);
				dumbie.shrink_to_fit();
				score++;
				tempStr = "Score: " + to_string(score);
				strcpy_s(scoreMessage, tempStr.c_str());
				dummyScore = TTF_RenderText_Solid(font, scoreMessage, White);
				Score = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), dummyScore);
			}
		}

		//for items
		itemSpawnTimer++;
		if (itemSpawnTimer == 1000) {
			//itemSpawnTimer = 0;
			item1.push_back(new Items(1, bg1.bgDst.x + 1075, bg1.bgDst.y + 1550));
			item1.shrink_to_fit();
		}
		for (unsigned i = 0; i < item1.size(); i++)
		{
			if (!wallHitx)
				item1[i]->item.x -= speedx;
			if (!wallHity)
				item1[i]->item.y -= speedy;


			if (SDL_HasIntersection(&plr1.plrDst, &item1[i]->item)) //AABB Check
			{
				Mix_PlayChannel(-1, powerSfx, 0);
				delete item1[i];
				item1[i] = nullptr;
				item1.erase(item1.begin() + i);
				item1.shrink_to_fit();
				playerDamage++;

			}

		}
	}
	else {
		if (!(fadeMod == 255))
			fadeMod += fadeSpeed;
		if (fadeMod == 255) {
			fadeMod == 255;
			cout << "changing to lv1" << endl;
			STMA::ChangeState(new Levelone());
			return;
		}
	}
}

void GameState::Render()
{
	
	SDL_RenderClear(Engine::Instance().GetRenderer());
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 200, 200, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	// Any drawing here...
	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);

	//Background
	SDL_RenderCopy(Engine::Instance().GetRenderer(),bgTutorial, &bg1.bgSrcTutorial, &bg1.bgDst);
	
	//vines
	for (unsigned i = 0; i < vine.size(); i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), vineTexture, &(vine[i]->vineSrc), &(vine[i]->vineDst));
	}

		if (plr1.state == 0)
			SDL_RenderCopy(Engine::Instance().GetRenderer(), plrTxtr, &plr1.plrFrontIdle, &plr1.plrDst);
		else if (plr1.state == 1)
			SDL_RenderCopy(Engine::Instance().GetRenderer(), plrTxtr, &plr1.plrMoveDown, &plr1.plrDst);
		else if (plr1.state == 2)
			SDL_RenderCopy(Engine::Instance().GetRenderer(), plrTxtr, &plr1.plrMoveUp, &plr1.plrDst);
		else if (plr1.state == 3)
			SDL_RenderCopy(Engine::Instance().GetRenderer(), plrTxtr, &plr1.plrMoveLeft, &plr1.plrDst);
		else if (plr1.state == 4)
			SDL_RenderCopy(Engine::Instance().GetRenderer(), plrTxtr, &plr1.plrMoveRight, &plr1.plrDst);

	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &plr1.plrHpBar);

	
	//NPC
	SDL_RenderCopyEx(Engine::Instance().GetRenderer(), npcTxtr, &catDude.npcSrc, &catDude.npcDst, NULL, NULL, SDL_FLIP_HORIZONTAL);

	//rock	
	for (unsigned i = 0; i < playerpew.size(); i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), rockTxtr,
			&(playerpew[i]->rockSrc), &(playerpew[i]->rockDst));
	}

	//bubble 
	for (unsigned i = 0; i < bub.size(); i++) 
	{
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 255);
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &bub[i]->bubbleDst);
	}
	//item
	for (unsigned i = 0; i < item1.size(); i++)
	{
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &item1[i]->item);
	}

	//dumbie
	for (unsigned i = 0; i < dumbie.size();i++)
	{
		SDL_RenderCopyEx(Engine::Instance().GetRenderer(), dumbieTxtr, &dumbie[i]->enemySrc, &dumbie[i]->enemyDst, 00.0, NULL, SDL_FLIP_NONE);
		//dumbie hp
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &dumbie[i]->healthBar);
	}
	//dragoon fly
	for (unsigned i = 0; i < fly.size(); i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), DragonFlyTxt, &fly[i]->flySrc, &fly[i]->flyDst);
		//health bar
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &fly[i]->healthBar);
	}
	//frog
	for (unsigned i = 0; i < frog.size(); i++) {
		SDL_RenderCopy(Engine::Instance().GetRenderer(), FrogTxtr, &frog[i]->frogSrc, &frog[i]->frogDst);
		//health bar
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &frog[i]->healthBar);
	}

	//text box
	if (renderTextBox) {
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &textBoxBorder);
		SDL_RenderCopy(Engine::Instance().GetRenderer(), Message, NULL, &textBoxRect);
	}

	//score text
	if (spawnDummies) {
		SDL_RenderCopy(Engine::Instance().GetRenderer(), Score, NULL, &scoreRect);
	}
	//SDL_RenderPresent(Engine::Instance().GetRenderer()); // Flip buffers - send data to window.
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, fadeMod);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &blackRect);

	if(dynamic_cast<GameState*>(STMA::GetStates().back() ) )//if current state is gamestate	
	State::Render();

}

void GameState::Exit()
{
	cout << "exiting gamestate" << endl;
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
	for (unsigned i = 0; i < item1.size();i++)
	{
		delete item1[i];
		item1[i] = nullptr;
	}
	playerpew.clear();
	playerpew.shrink_to_fit();
	dumbie.clear();
	dumbie.shrink_to_fit();
	item1.clear();
	item1.shrink_to_fit();
	SDL_DestroyTexture(dumbieTxtr);
	SDL_DestroyTexture(plrTxtr );
	SDL_DestroyTexture(rockTxtr);
	SDL_DestroyTexture(bgTutorial);
	SDL_DestroyTexture(npcTxtr);
	SDL_DestroyTexture(DragonFlyTxt);
	SDL_DestroyTexture(vineTexture);


Mix_FreeChunk(hurtSfx);
Mix_FreeChunk(powerSfx);
Mix_FreeChunk(talk);
Mix_FreeChunk(winscore);
Mix_FreeChunk(hehe);
Mix_FreeChunk(projectileRock);
Mix_FreeChunk(aoeSound);
Mix_FreeChunk(dashing);
Mix_FreeChunk(stepSfx);
Mix_FreeChunk(deathSfx);
Mix_FreeChunk(turnSfx);

Mix_FreeMusic(maintheme);
}

void GameState::Resume()
{
	cout << "resuming gamestate" << endl;
	if (Mix_PausedMusic() == true)
		Mix_ResumeMusic();
	//resume music track

}



Levelone::Levelone() {}

void Levelone::Enter()
{
	cout << "entering lv1" << endl;
	swamp = IMG_LoadTexture(Engine::Instance().GetRenderer(), "bgs/swamp.png");
	swamp1 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "bgs/swamp1.png");
	swamp2 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "bgs/swamp2.png");
	swamp3 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "bgs/swamp3.png");
	swamp4 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "bgs/swamp4.png");
	swamp5 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "bgs/swamp5.png");

	plrTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/catboy.png");
	rockTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/Rocko100.png");
	DragonFlyTxt = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/dragonfly.png");
	vineTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/vines.png");
	FrogTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/frogWalking7.png");
	ShroomTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/mushroom.png");
	stepSfx = Mix_LoadWAV("sfx/step.wav");
	turnSfx = Mix_LoadWAV("sfx/turn.wav");
	deathSfx = Mix_LoadWAV("sfx/dedEnemy.wav");
	hurtSfx = Mix_LoadWAV("sfx/enemyHurt.wav");
	powerSfx = Mix_LoadWAV("sfx/powerUp.wav");
	hehe = Mix_LoadWAV("sfx/killsound.wav");
	projectileRock = Mix_LoadWAV("sfx/rocksound.wav");
	aoeSound = Mix_LoadWAV("sfx/aoeAbility.wav");
	dashing = Mix_LoadWAV("sfx/dashSound.wav");
	Mix_VolumeChunk(dashing, 25);
	Mix_VolumeChunk(aoeSound, 50);
	Mix_VolumeChunk(projectileRock, 50);
	swampSong = Mix_LoadMUS("Aud/swampLVL.mp3");
	Mix_PlayMusic(swampSong, 5);
	Mix_VolumeMusic(5); //0-128
	Mix_Volume(-1, 50);
	playerpew.reserve(4);

	loadArea = true;

	areaNum = 0;

	blackRect = { 0 , 0 , 1024 , 768 };
	exitRect = { 0,0, 10, 10 };
	
	for (int i = 0; i < 15; i++)
	{
		bg.push_back(new Level1Background(rand()%5, 10));
	}


}



void Levelone::Update()
{
	if (!lvlLoading) {
		if (!(fadeMod == 0))
			fadeMod -= fadeSpeed;
		if (fadeMod == 0)
			fadeMod == 0;
		if (plr1.winbar >= 150)
		{
			STMA::ChangeState(new WState());
			return;
		}
		cout << exitRect.x << endl;
		cout << exitRect.y << endl;
		cout << bg[areaNum]->getBg() << endl;
		if (loadArea) {
			//clear vectors
			playerpew.clear();
			vine.clear();
			fly.clear();
			frog.clear();
			levelRect.clear();
			plr1.setPlrSpd(0);

			for (int i = 0; i < 255 / fadeSpeed; i++)
			{
				if (!(fadeMod == 255))
					fadeMod += fadeSpeed;
			}
			entrance = rand() % 2;
			cout << entrance << endl;
			if (bg[areaNum]->getBg() == 0) {
				/*if (entrance == 0) {
					bg[areaNum]->swampDst.x = 350;
					bg[areaNum]->swampDst.y = -150;
					exitRect.x = bg[areaNum]->swampDst.x;
					exitRect.y = bg[areaNum]->swampDst.y + 1280;
				}
				else if (entrance == 1) {
					bg[areaNum]->swampDst.x = 350;
					bg[areaNum]->swampDst.y = -820;
					exitRect.x = bg[areaNum]->swampDst.x;
					exitRect.y = bg[areaNum]->swampDst.y + 550;
				}*/
				//spawn position
				bg[areaNum]->swampDst.x = 350;
				bg[areaNum]->swampDst.y = -150;
				//exit position
				exitRect.x = bg[areaNum]->swampDst.x + 50;
				exitRect.y = bg[areaNum]->swampDst.y + 1280;

				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + -50,bg[areaNum]->swampDst.y + 370,240,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 190,bg[areaNum]->swampDst.y + 0,10,380 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 190,bg[areaNum]->swampDst.y + -10,640 + 128,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 830 + 128,bg[areaNum]->swampDst.y + 0,10,380 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 830 + 128,bg[areaNum]->swampDst.y + 370,390 - 128,10 });

				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1210,bg[areaNum]->swampDst.y + 130,10,250 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1220,bg[areaNum]->swampDst.y + 120,380 + 128,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1600 + 128,bg[areaNum]->swampDst.y + 130,10,380 + 128 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1500 + 128,bg[areaNum]->swampDst.y + 510 + 128,100,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1500 + 128,bg[areaNum]->swampDst.y + 510 + 128,10,250 - 128 });

				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1500 + 128,bg[areaNum]->swampDst.y + 750,100,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1600 + 128,bg[areaNum]->swampDst.y + 760,10,400 + 128 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 940 + 128,bg[areaNum]->swampDst.y + 1160 + 128,660,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 940 + 128,bg[areaNum]->swampDst.y + 1160 + 128,10,120 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + -50 + 128,bg[areaNum]->swampDst.y + 1280 + 128,990,10 });

				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + -50,bg[areaNum]->swampDst.y + 1140,240,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 180,bg[areaNum]->swampDst.y + 750,10,390 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 190,bg[areaNum]->swampDst.y + 750,510 + 128,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 700 + 128,bg[areaNum]->swampDst.y + 750,10,390 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 700 + 128,bg[areaNum]->swampDst.y + 1145,30,10 });

				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 860,bg[areaNum]->swampDst.y + 1030,10,120 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 840 + 30,bg[areaNum]->swampDst.y + 1025,240 - 64,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1070,bg[areaNum]->swampDst.y + 760,10,270 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1080,bg[areaNum]->swampDst.y + 750,300,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1370,bg[areaNum]->swampDst.y + 510 + 128,10,250 - 128 });

				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + -50,bg[areaNum]->swampDst.y + 510 + 128,1430,10 });

				//fly.push_back(new DragonFly)
			}
			if (bg[areaNum]->getBg() == 1)
			{
				bg[areaNum]->swampDst.x = -520;
				bg[areaNum]->swampDst.y = 320;
				
				exitRect.x = bg[areaNum]->swampDst.x + 960;
				exitRect.y = bg[areaNum]->swampDst.y + 1360;
				
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 70,bg[areaNum]->swampDst.y + 100,10,1210 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 65,bg[areaNum]->swampDst.y + 100 ,630,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 695,bg[areaNum]->swampDst.y - 150,10,200 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1365,bg[areaNum]->swampDst.y + 100 ,630,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1365,bg[areaNum]->swampDst.y - 150,10,200 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 2000,bg[areaNum]->swampDst.y + 100,10,1210 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 2000,bg[areaNum]->swampDst.y + 300,10,910 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1355,bg[areaNum]->swampDst.y + 1300,630,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 75,bg[areaNum]->swampDst.y + 1300,630,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 695,bg[areaNum]->swampDst.y + 1300,10,240 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1355,bg[areaNum]->swampDst.y + 1300,10,240 });
				//levelRect.push_back(new SDL_Rect{ bg[areaNum]->swamp1Dst.x,bg[areaNum]->swamp1Dst.y });
			}

			if (bg[areaNum]->getBg() == 2)
			{
				bg[areaNum]->swampDst.x = 200;
				bg[areaNum]->swampDst.y = 300;

				exitRect.x = bg[areaNum]->swampDst.x + 1550;
				exitRect.y = bg[areaNum]->swampDst.y + 1400;
				
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 50,bg[areaNum]->swampDst.y - 20,10,1300 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 570,bg[areaNum]->swampDst.y - 20,10,270 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 600,bg[areaNum]->swampDst.y + 250,1280,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1860,bg[areaNum]->swampDst.y + 250,10,1300 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 40,bg[areaNum]->swampDst.y + 1330,1280,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1340,bg[areaNum]->swampDst.y + 1360,10,200 });
			}

			if (bg[areaNum]->getBg() == 3)
			{
				bg[areaNum]->swampDst.x = 400;
				bg[areaNum]->swampDst.y = -850;

				exitRect.x = bg[areaNum]->swampDst.x + 1900;
				exitRect.y = bg[areaNum]->swampDst.y + 230;
				
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x - 10,bg[areaNum]->swampDst.y + 998,150,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 170,bg[areaNum]->swampDst.y + 320,10,650 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 170,bg[areaNum]->swampDst.y + 230,580,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 800,bg[areaNum]->swampDst.y + 20 ,10,200 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 900,bg[areaNum]->swampDst.y - 20,1100,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x - 10 ,bg[areaNum]->swampDst.y + 1420,1300,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1330,bg[areaNum]->swampDst.y + 590,10,800 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1350,bg[areaNum]->swampDst.y + 560,700,10 });

			}

			if (bg[areaNum]->getBg() == 4)
			{
				bg[areaNum]->swampDst.x = 430;
				bg[areaNum]->swampDst.y = -430;

				exitRect.x = bg[areaNum]->swampDst.x + 1920;
				exitRect.y = bg[areaNum]->swampDst.y + 130;
				
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x,bg[areaNum]->swampDst.y + 1060,280,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 320,bg[areaNum]->swampDst.y + 1090,10,380 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 360,bg[areaNum]->swampDst.y + 1440,1070,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1470,bg[areaNum]->swampDst.y + 1370,10,100 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1500,bg[areaNum]->swampDst.y + 1330,50,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1600,bg[areaNum]->swampDst.y + 470,10,800 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 1650,bg[areaNum]->swampDst.y + 440,400,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x,bg[areaNum]->swampDst.y + 620,280,10 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 320,bg[areaNum]->swampDst.y,10,580 });
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 320,bg[areaNum]->swampDst.y - 20,1720,10 });
			}


			loadArea = false;
		}
		if (bg[areaNum]->getBg() == 0) {
			//wallcollision
			bool wallHitx = false;
			bool wallHity = false;
			if (SDL_HasIntersection(levelRect[0], &plr1.plrDst)) {//down
				speedx = 0;
				speedy = 0;
				speedy++;
			}
			if (SDL_HasIntersection(levelRect[1], &plr1.plrDst)) { //right
				speedx = 0;
				speedx++;
				speedy = 0;
			}
			if (SDL_HasIntersection(levelRect[2], &plr1.plrDst)) { //down
				speedx = 0;
				speedy = 0;
				speedy++;
			}

			if (SDL_HasIntersection(levelRect[3], &plr1.plrDst)) { //left
				speedx = 0;
				speedy = 0;
				speedx--;
			}

			if (SDL_HasIntersection(levelRect[4], &plr1.plrDst)) {//down
				speedx = 0;
				speedy = 0;
				speedy++;
			}

			if (SDL_HasIntersection(levelRect[5], &plr1.plrDst)) {//right
				speedx = 0;
				speedy = 0;
				speedx++;
			}

			if (SDL_HasIntersection(levelRect[6], &plr1.plrDst)) {//down
				speedx = 0;
				speedy = 0;
				speedy++;
			}

			if (SDL_HasIntersection(levelRect[7], &plr1.plrDst)) {//left
				speedx = 0;
				speedy = 0;
				speedx--;
			}

			if (SDL_HasIntersection(levelRect[8], &plr1.plrDst)) {//up
				speedx = 0;
				speedy = 0;
				speedy--;
			}

			if (SDL_HasIntersection(levelRect[9], &plr1.plrDst)) {//left
				speedx = 0;
				speedy = 0;
				speedx--;
			}

			if (SDL_HasIntersection(levelRect[10], &plr1.plrDst)) {//down
				speedx = 0;
				speedy = 0;
				speedy++;
			}

			if (SDL_HasIntersection(levelRect[11], &plr1.plrDst)) {//left
				speedx = 0;
				speedy = 0;
				speedx--;
			}

			if (SDL_HasIntersection(levelRect[12], &plr1.plrDst)) {//up
				speedx = 0;
				speedy = 0;
				speedy--;
			}

			if (SDL_HasIntersection(levelRect[13], &plr1.plrDst)) {//left
				speedx = 0;
				speedy = 0;
				speedx--;
			}

			if (SDL_HasIntersection(levelRect[14], &plr1.plrDst)) {//up
				speedx = 0;
				speedy = 0;
				speedy--;
			}

			if (SDL_HasIntersection(levelRect[15], &plr1.plrDst)) {//down
				speedx = 0;
				speedy = 0;
				speedy++;
			}

			if (SDL_HasIntersection(levelRect[16], &plr1.plrDst)) {//down
				speedx = 0;
				speedy = 0;
				speedy++;
			}

			if (SDL_HasIntersection(levelRect[17], &plr1.plrDst)) {//down
				speedx = 0;
				speedy = 0;
				speedy++;
			}

			if (SDL_HasIntersection(levelRect[18], &plr1.plrDst)) {//left
				speedx = 0;
				speedy = 0;
				speedx--;
			}

			if (SDL_HasIntersection(levelRect[19], &plr1.plrDst)) {//down
				speedx = 0;
				speedy = 0;
				speedy++;
			}
			if (SDL_HasIntersection(levelRect[20], &plr1.plrDst)) {//left
				speedx = 0;
				speedy = 0;
				speedx++;
			}
			if (SDL_HasIntersection(levelRect[21], &plr1.plrDst)) {//down
				speedx = 0;
				speedy = 0;
				speedy++;
			}

			if (SDL_HasIntersection(levelRect[22], &plr1.plrDst)) {//right
				speedx = 0;
				speedy = 0;
				speedx++;
			}

			if (SDL_HasIntersection(levelRect[23], &plr1.plrDst)) {//right
				speedx = 0;
				speedy = 0;
				speedy++;
			}

			if (SDL_HasIntersection(levelRect[24], &plr1.plrDst)) {//right
				speedx = 0;
				speedy = 0;
				speedx++;
			}

			if (SDL_HasIntersection(levelRect[25], &plr1.plrDst)) {//right
				speedx = 0;
				speedy = 0;
				speedy--;
			}

			for (int i = 0; i < levelRect.size(); i++)
			{
				if (!wallHitx)
					levelRect[i]->x -= speedx;
				if (!wallHity)
					levelRect[i]->y -= speedy;
			}


		}
		

		if (bg[areaNum]->getBg() == 1)
		{
			//wallcollision
			bool wallHitx = false;
			bool wallHity = false;
			if (SDL_HasIntersection(levelRect[0], &plr1.plrDst)) {//right
				speedx = 0;
				speedy = 0;
				speedx++;
			}
			if (SDL_HasIntersection(levelRect[1], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedy++;
			}
			if (SDL_HasIntersection(levelRect[2], &plr1.plrDst)) {//right
				speedx = 0;
				speedy = 0;
				speedx++;
			}
			if (SDL_HasIntersection(levelRect[3], &plr1.plrDst)) {//right
				speedx = 0;
				speedy = 0;
				speedy++;
			}
			if (SDL_HasIntersection(levelRect[4], &plr1.plrDst)) {//right
				speedx = 0;
				speedy = 0;
				speedx--;
			}
			if (SDL_HasIntersection(levelRect[5], &plr1.plrDst)) {//right
				speedx = 0;
				speedy = 0;
				speedx--;
			}
			if (SDL_HasIntersection(levelRect[6], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedx--;
			}
			if (SDL_HasIntersection(levelRect[7], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedy--;
			}
			if (SDL_HasIntersection(levelRect[8], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedy--;
			}
			if (SDL_HasIntersection(levelRect[9], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedx++;
			}
			if (SDL_HasIntersection(levelRect[10], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedx--;
			}
			for (int i = 0; i < levelRect.size(); i++)
			{
				if (!wallHitx)
					levelRect[i]->x -= speedx;
				if (!wallHity)
					levelRect[i]->y -= speedy;
			}
		
		}	

		if (bg[areaNum]->getBg() == 2)
		{
			//wallcollision
			bool wallHitx = false;
			bool wallHity = false;
			if (SDL_HasIntersection(levelRect[0], &plr1.plrDst)) {//right
				speedx = 0;
				speedy = 0;
				speedx++;
			}
			if (SDL_HasIntersection(levelRect[1], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedx--;
			}
			if (SDL_HasIntersection(levelRect[2], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedy++;
			}
			if (SDL_HasIntersection(levelRect[3], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedx--;
			}
			if (SDL_HasIntersection(levelRect[4], &plr1.plrDst)) {//up
				speedx = 0;
				speedy = 0;
				speedy--;
			}
			if (SDL_HasIntersection(levelRect[5], &plr1.plrDst)) {//right
				speedx = 0;
				speedy = 0;
				speedx++;
			}
			for (int i = 0; i < levelRect.size(); i++)
			{
				if (!wallHitx)
					levelRect[i]->x -= speedx;
				if (!wallHity)
					levelRect[i]->y -= speedy;
			}
		}
		if (bg[areaNum]->getBg() == 3)
		{
			//wallcollision
			bool wallHitx = false;
			bool wallHity = false;
			if (SDL_HasIntersection(levelRect[0], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedy++;
			}
			if (SDL_HasIntersection(levelRect[1], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedx++;
			}
			if (SDL_HasIntersection(levelRect[2], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedy++;
			}
			if (SDL_HasIntersection(levelRect[3], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedx++;
			}
			if (SDL_HasIntersection(levelRect[4], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedy++;
			}
			if (SDL_HasIntersection(levelRect[5], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedy--;
			}
			if (SDL_HasIntersection(levelRect[6], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedx--;

			}
			if (SDL_HasIntersection(levelRect[7], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedy--;
			}
			for (int i = 0; i < levelRect.size(); i++)
			{
				if (!wallHitx)
					levelRect[i]->x -= speedx;
				if (!wallHity)
					levelRect[i]->y -= speedy;
			}
		}
		if (bg[areaNum]->getBg() == 4)
		{
			//wallcollision
			bool wallHitx = false;
			bool wallHity = false;
			if (SDL_HasIntersection(levelRect[0], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedy--;
			}
			if (SDL_HasIntersection(levelRect[1], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedx++;
			}
			if (SDL_HasIntersection(levelRect[2], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedy--;
			}
			if (SDL_HasIntersection(levelRect[3], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedx--;
			}
			if (SDL_HasIntersection(levelRect[4], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedy--;
			}
			if (SDL_HasIntersection(levelRect[5], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedx--;
			}
			if (SDL_HasIntersection(levelRect[6], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedy--;
			}
			if (SDL_HasIntersection(levelRect[7], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedy++;
			}
			if (SDL_HasIntersection(levelRect[8], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedx++;
			}
			if (SDL_HasIntersection(levelRect[9], &plr1.plrDst)) {//
				speedx = 0;
				speedy = 0;
				speedy++;
			}
			for (int i = 0; i < levelRect.size(); i++)
			{
				if (!wallHitx)
					levelRect[i]->x -= speedx;
				if (!wallHity)
					levelRect[i]->y -= speedy;
			}
		}
		bg[areaNum]->swampDst.x -= speedx;
		bg[areaNum]->swampDst.y -= speedy;
		if (!wallHitx)
			exitRect.x -= speedx;
		if (!wallHity)
			exitRect.y -= speedy;

		
		if (SDL_HasIntersection(&exitRect, &plr1.plrDst)) {
			loadArea = true;
			areaNum++;
			cout << "hit" << endl;
		}

		if (plr1.plrHp <= 0)
		{
			STMA::ChangeState(new EndState());
			return;
		}
		//cout <<"noobtimer"<< Noobtimer++ <<" | "<<ezModeCD++ << "ezmodecd<-" << endl;
		//cout << "freezetimer" << freezetimer++ << " | " << freezeCD++ << "freezecd<-" << endl;
		cout << plr1.plrDst.x - bg[areaNum]->swampDst.x << " - " << plr1.plrDst.y - bg[areaNum]->swampDst.y << endl;
		// cout << plr1.plrDst.x << " , " << plr1.plrDst.y  << endl;
		cout << bg[areaNum]->swampDst.x << "||" << bg[areaNum]->swampDst.y << endl;
		
		//player
		if (!dashPressed)
			plr1.plrSpd = plr1.plrMaxSpd;
		 
		 //Dash
		if (dashCooldown > 100) {
			if (EVMA::KeyPressed(SDL_SCANCODE_LSHIFT)) {
				Mix_PlayChannel(-1, dashMeow, 0);
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
		if (EVMA::KeyPressed(SDL_SCANCODE_P))
		{
			cout << "Changing to PauseState" << endl;
			//pause the music track
			STMA::PushState(new PauseState());
			Mix_PauseMusic();
		}

		stepSoundTimer++; turnSoundTimer++;
		dashCooldown++;
		plr1.Update();
		rockCooldown++;
		spcooldown++;

		if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
		{

			cout << "changing to gamestate" << endl;
			STMA::ChangeState(new TitleState());
			return;
		}
		if (EVMA::KeyHeld(SDL_SCANCODE_W))
		{
			if (!Mix_Playing(7))
			{
				Mix_PlayChannel(7, stepSfx, -1);
			}
		}
		if (EVMA::KeyHeld(SDL_SCANCODE_A))
		{
			if (!Mix_Playing(7))
			{
				Mix_PlayChannel(7, stepSfx, -1);
			}
		}
		if (EVMA::KeyHeld(SDL_SCANCODE_S))
		{
			if (!Mix_Playing(7))
			{
				Mix_PlayChannel(7, stepSfx, -1);
			}
		}
		if (EVMA::KeyHeld(SDL_SCANCODE_D))
		{
			if (!Mix_Playing(7))
			{
				Mix_PlayChannel(7, stepSfx, -1);
			}
		}

		//HALT!
		if (EVMA::KeyReleased(SDL_SCANCODE_S)) {
			Mix_HaltChannel(7);
		}

		if (EVMA::KeyReleased(SDL_SCANCODE_W)) {
			Mix_HaltChannel(7);
		}

		if (EVMA::KeyReleased(SDL_SCANCODE_A)) {
			Mix_HaltChannel(7);
		}

		if (EVMA::KeyReleased(SDL_SCANCODE_D)) {
			Mix_HaltChannel(7);
		}


		//For special Ability1
		if (EVMA::KeyPressed(SDL_SCANCODE_SPACE))
		{
			if (spcooldown > 200)
			{
				Mix_PlayChannel(-1, aoeSound, 0);
				spcooldown = 0;
				playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, 10, 'y'));
				playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, 10 * -1, 'y'));
				playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, 10, 'x'));
				playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, 10 * -1, 'x'));
				playerpew.shrink_to_fit();
			}
		}

		//For throwing Rock
		if (EVMA::KeyHeld(SDL_SCANCODE_UP))
		{
			if (rockCooldown > plr1.fireRate) {
				Mix_PlayChannel(-1, projectileRock, 0);
				rockCooldown = 0;
				playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, rockSpeed * -1, 'y'));
				playerpew.shrink_to_fit();
			}
		}
		else if (EVMA::KeyHeld(SDL_SCANCODE_DOWN))
		{

			if (rockCooldown > plr1.fireRate) {
				Mix_PlayChannel(-1, projectileRock, 0);
				rockCooldown = 0;
				playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, rockSpeed, 'y'));
				playerpew.shrink_to_fit();
			}
		}
		else if (EVMA::KeyHeld(SDL_SCANCODE_LEFT))
		{

			if (rockCooldown > plr1.fireRate) {
				Mix_PlayChannel(-1, projectileRock, 0);
				rockCooldown = 0;
				playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, rockSpeed * -1, 'x'));
				playerpew.shrink_to_fit();
			}
		}
		else if (EVMA::KeyHeld(SDL_SCANCODE_RIGHT))
		{

			if (rockCooldown > plr1.fireRate) {
				Mix_PlayChannel(-1, projectileRock, 0);
				rockCooldown = 0;
				playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, rockSpeed, 'x'));
				playerpew.shrink_to_fit();
			}
		}
		//delete rock after off screen and move rock
		for (unsigned i = 0; i < playerpew.size(); i++)
		{
			playerpew[i]->Update();
			playerpew[i]->rockDst.x -= speedx;
			playerpew[i]->rockDst.y -= speedy;

			if (playerpew[i]->rockDst.x >= WIDTH || playerpew[i]->rockDst.x <= -64 || playerpew[i]->rockDst.y >= HEIGHT || playerpew[i]->rockDst.y <= -64)
			{
				delete playerpew[i];
				playerpew[i] = nullptr;
				playerpew.erase(playerpew.begin() + i);
				playerpew.shrink_to_fit();
				break;
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
		//YAXIS

		if (EVMA::KeyHeld(SDL_SCANCODE_S)) {

			speedy += speedAcc;
			plr1.state = 1;

		}

		if (EVMA::KeyHeld(SDL_SCANCODE_W)) {

			speedy -= speedAcc;
			plr1.state = 2;
		}

		//XAXIS
		if (EVMA::KeyHeld(SDL_SCANCODE_A)) {
			speedx -= speedAcc;
			plr1.state = 3;
		}

		if (EVMA::KeyHeld(SDL_SCANCODE_D)) {
			speedx += speedAcc;
			plr1.state = 4;
		}



		//Slow Down!
		if (!EVMA::KeyHeld(SDL_SCANCODE_D) && !EVMA::KeyHeld(SDL_SCANCODE_A)) {
			if (speedx > 0)
				speedx--;
			else if (speedx < 0) {
				speedx++;
			}
		}
		if (!EVMA::KeyHeld(SDL_SCANCODE_W) && !EVMA::KeyHeld(SDL_SCANCODE_S)) {
			if (speedy > 0)
				speedy--;
			else if (speedy < 0) {
				speedy++;
			}
		}
		if (!EVMA::KeyHeld(SDL_SCANCODE_W) && !EVMA::KeyHeld(SDL_SCANCODE_S) && !EVMA::KeyHeld(SDL_SCANCODE_D) && !EVMA::KeyHeld(SDL_SCANCODE_A)) {
			plr1.state = 0;
		}		
		/*for (unsigned i = 0; i < shroom.size(); i++)
		{
			shroom[i]->shroomDst.x -= speedx;
			shroom[i]->shroomDst.y -= speedy;
		}*/
		/*for (unsigned i = 0; i < ushroomatk.size(); i++)
		{
			ushroomatk[i]->ushroomAtkDst.x -= speedx;
			ushroomatk[i]->ushroomAtkDst.y -= speedy;

		}
		for (unsigned i = 0; i < lshroomatk.size(); i++)
		{
			lshroomatk[i]->lshroomAtkDst.x -= speedx;
			lshroomatk[i]->lshroomAtkDst.y -= speedy;
		}
		for (unsigned i = 0; i < rshroomatk.size(); i++)
		{
			rshroomatk[i]->rshroomAtkDst.x -= speedx;
			rshroomatk[i]->rshroomAtkDst.y -= speedy;
		}
		for (unsigned i = 0; i < dshroomatk.size(); i++)
		{
			dshroomatk[i]->dshroomAtkDst.x -= speedx;
			dshroomatk[i]->dshroomAtkDst.y -= speedy;
		}*/

		//frog
		for (unsigned i = 0; i < frog.size(); i++) {
			frog[i]->Update(plr1.plrDst);
			if (!wallHitx)
				frog[i]->frogDst.x -= speedx;
			if (!wallHity)
				frog[i]->frogDst.y -= speedy;
			for (unsigned j = 0; j < playerpew.size(); j++)
			{
				if (SDL_HasIntersection(&playerpew[j]->rockDst, &frog[i]->frogDst)) //AABB Check
				{
					Mix_PlayChannel(-1, hurtSfx, 0);
					delete playerpew[j];
					playerpew[j] = nullptr;
					playerpew.erase(playerpew.begin() + j);
					playerpew.shrink_to_fit();
					//set dumbie hp
					frog[i]->setHp(frog[i]->getHp() - playerDamage);
					break;
				}
			}
			if (SDL_HasIntersection(&frog[i]->frogDst, &plr1.plrDst)) {
				plr1.takeDamage(2);
			}
			if ((Util::distanceOffset(plr1.plrDst, frog[i]->frogDst) < 550)) {
				if (frog[i]->getShootTimer() == 0) {
					if (frog[i]->getDir() == 0)
						bub.push_back(new Bubble(frog[i]->frogDst.x, frog[i]->frogDst.y));
					if (frog[i]->getDir() == 1)
						bub.push_back(new Bubble(frog[i]->frogDst.x, frog[i]->frogDst.y));
					if (frog[i]->getDir() == 2)
						bub.push_back(new Bubble(frog[i]->frogDst.x, frog[i]->frogDst.y));
					if (frog[i]->getDir() == 3)
						bub.push_back(new Bubble(frog[i]->frogDst.x, frog[i]->frogDst.y));
				}
			}
			if (frog[i]->getHp() <= 0) {
				plr1.points(10);
				Mix_PlayChannel(-1, deathSfx, 0);
				delete frog[i];
				frog[i] = nullptr;
				frog.erase(frog.begin() + i);
				frog.shrink_to_fit();
			}
		}
		//bubble
		for (int i = 0; i < bub.size(); i++)
		{
			bub[i]->Update(plr1.plrDst);
			if (!wallHitx)
				bub[i]->bubbleDst.x -= speedx;
			if (!wallHity)
				bub[i]->bubbleDst.y -= speedy;
			if (Util::distanceOffset(plr1.plrDst, bub[i]->bubbleDst) < 50) {
				plr1.takeDamage(1);
				delete bub[i];
				bub[i] = nullptr;
				bub.erase(bub.begin() + i);
				bub.shrink_to_fit();
			}
		}
		//vines
		for (unsigned i = 0; i < vine.size(); i++)
		{
			if (!wallHitx)
				vine[i]->vineDst.x -= speedx;
			if (!wallHity)
				vine[i]->vineDst.y -= speedy;
			if (!dashPressed) {
				if (Util::distanceOffset(plr1.plrDst, vine[i]->vineDst) < 80) {
					plr1.plrSpd = 1;
				}
			}
		}
				
		//DragonFly
		for (unsigned i = 0; i < fly.size(); i++)
		{
			fly[i]->Update();
			if (!wallHitx)
				fly[i]->flyDst.x -= speedx;
			if (!wallHity)
				fly[i]->flyDst.y -= speedy;

			if (SDL_HasIntersection(&fly[i]->flyDst, &plr1.plrDst)) {
				plr1.takeDamage(1);
			}

			if (fly[i]->getHp() <= 0) {
				Mix_PlayChannel(-1, deathSfx, 0);
				delete fly[i];
				fly[i] = nullptr;
				fly.erase(fly.begin() + i);
				fly.shrink_to_fit();
			}
			for (unsigned j = 0; j < playerpew.size(); j++)
			{
				if (SDL_HasIntersection(&playerpew[j]->rockDst, &fly[i]->flyDst)) //AABB Check
				{
					Mix_PlayChannel(-1, hurtSfx, 0);
					delete playerpew[j];
					playerpew[j] = nullptr;
					playerpew.erase(playerpew.begin() + j);
					playerpew.shrink_to_fit();
					//set dumbie hp
					fly[i]->setHp(fly[i]->getHp() - playerDamage);
					break;
				}
			}

		}

		if (isfreezeActive == false)
		{
			for (unsigned i = 0; i < fly.size(); i++)
			{
				fly[i]->Update();
				if (SDL_HasIntersection(&fly[i]->flyDst, &plr1.plrDst)) {
					plr1.takeDamage(1);
				}

				if (fly[i]->getHp() <= 0) {
					plr1.points(10);
					Mix_PlayChannel(-1, deathSfx, 0);
					delete fly[i];
					fly[i] = nullptr;
					fly.erase(fly.begin() + i);
					fly.shrink_to_fit();
				}
			}
		}

		//shroom
		for (unsigned i = 0; i < playerpew.size(); i++)
		{
			for (unsigned j = 0; j < shroom.size(); j++)
			{
				if (SDL_HasIntersection(&playerpew[i]->rockDst, &shroom[j]->shroomDst)) //AABB Check
				{

					Mix_PlayChannel(-1, hurtSfx, 0);
					delete playerpew[i];
					playerpew[i] = nullptr;
					playerpew.erase(playerpew.begin() + i);
					playerpew.shrink_to_fit();
					//set dumbie hp					
					shroom[j]->setHp(shroom[j]->getHp() - playerDamage);
					break;					
				}
			}
		}
		if (isfreezeActive == false)
		{
			for (unsigned i = 0; i < shroom.size(); i++)
			{
				shroom[i]->Update();


				if (shroom[i]->frames >= FPS * CLOUDRATE / 2)
				{
					shroom[i]->resetFrames();
					cout << "shroom pew" << endl;
					ushroomatk.push_back(new Attack(shroom[i]->shroomDst.x + 17, shroom[i]->shroomDst.y + 23));
					ushroomatk.shrink_to_fit();
					lshroomatk.push_back(new Attack(shroom[i]->shroomDst.x + 17, shroom[i]->shroomDst.y + 23));
					lshroomatk.shrink_to_fit();
					rshroomatk.push_back(new Attack(shroom[i]->shroomDst.x + 17, shroom[i]->shroomDst.y + 23));
					rshroomatk.shrink_to_fit();
					dshroomatk.push_back(new Attack(shroom[i]->shroomDst.x + 17, shroom[i]->shroomDst.y + 23));
					dshroomatk.shrink_to_fit();
				}
				if (shroom[i]->getHp() <= 0)
				{
					plr1.points(10);
					Mix_PlayChannel(-1, deathSfx, 0);
					delete shroom[i];
					shroom[i] = nullptr;
					shroom.erase(shroom.begin() + i);
					shroom.shrink_to_fit();
				}
			}
		}
		if (isfreezeActive == false)
		{
			for (unsigned i = 0; i < ushroomatk.size(); i++)
			{
				ushroomatk[i]->Update(-1);

				if (SDL_HasIntersection(&ushroomatk[i]->ushroomAtkDst, &plr1.plrDst)) {
					plr1.takeDamage(0.5);
				}

			}

		}
		if (isfreezeActive == false)
		{
			for (unsigned i = 0; i < lshroomatk.size(); i++)
			{
				lshroomatk[i]->Update(-1);

				if (SDL_HasIntersection(&lshroomatk[i]->lshroomAtkDst, &plr1.plrDst)) {
					plr1.takeDamage(0.5);
				}
			}
		}
		if (isfreezeActive == false)
		{
			for (unsigned i = 0; i < rshroomatk.size(); i++)
			{
				rshroomatk[i]->Update(1);

				if (SDL_HasIntersection(&rshroomatk[i]->rshroomAtkDst, &plr1.plrDst)) {
					plr1.takeDamage(0.5);
				}
			}
		}
		if (isfreezeActive == false)
		{
			for (unsigned i = 0; i < dshroomatk.size(); i++)
			{
				dshroomatk[i]->Update(1);

				if (SDL_HasIntersection(&dshroomatk[i]->dshroomAtkDst, &plr1.plrDst)) {
					plr1.takeDamage(0.5);
				}
			}
		}
		
	}
	else {
		if (!(fadeMod == 255))
			fadeMod += fadeSpeed;
		if (fadeMod == 255) {
			fadeMod == 255;
			lvlLoading = false;
		}
	}

}
void Levelone::Render()
{
	SDL_RenderClear(Engine::Instance().GetRenderer());
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(),100,11,169,255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	// Any drawing here...
	//SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
	//SDL_RenderFillRect(m_pRenderer, &plr1.plrDst);
	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);

	//Background
	if (bg[areaNum]->getBg() == 0)
		SDL_RenderCopy(Engine::Instance().GetRenderer(), swamp, &bg[areaNum]->swampSrc,&bg[areaNum]->swampDst);
	if (bg[areaNum]->getBg() == 1)
		SDL_RenderCopy(Engine::Instance().GetRenderer(), swamp1, &bg[areaNum]->swampSrc, &bg[areaNum]->swampDst);
	if (bg[areaNum]->getBg() == 2)
		SDL_RenderCopy(Engine::Instance().GetRenderer(), swamp2, &bg[areaNum]->swampSrc, &bg[areaNum]->swampDst);
	if (bg[areaNum]->getBg() == 3)
		SDL_RenderCopy(Engine::Instance().GetRenderer(), swamp3, &bg[areaNum]->swampSrc, &bg[areaNum]->swampDst);
	if (bg[areaNum]->getBg() == 4)
		SDL_RenderCopy(Engine::Instance().GetRenderer(), swamp4, &bg[areaNum]->swampSrc, &bg[areaNum]->swampDst);
	
	//rock	
	for (unsigned i = 0; i < playerpew.size(); i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), rockTxtr,
			&(playerpew[i]->rockSrc), &(playerpew[i]->rockDst));
	}
	
	//item
	for (unsigned i = 0; i < item1.size(); i++)
	{
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &item1[i]->item);
	}
	
	//vines
	for (unsigned i = 0; i < vine.size(); i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), vineTexture, &(vine[i]->vineSrc), &(vine[i]->vineDst));
	}

	//frog
	for(unsigned i =0; i <frog.size(); i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), FrogTxtr,&frog[i]->frogSrc,&frog[i]->frogDst);
		//health bar
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
		if (isfreezeActive == false)
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &frog[i]->healthBar);
	}
	//bubble 
	for (unsigned i = 0; i < bub.size(); i++)
	{
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 255);
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &bub[i]->bubbleDst);
	}
	
	//dragoon fly
	for (unsigned i = 0; i < fly.size(); i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), DragonFlyTxt, &fly[i]->flySrc, &fly[i]->flyDst);
		//health bar		
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
		if (isfreezeActive == false)
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &fly[i]->healthBar);
	}
	//shroom
	for (unsigned i = 0; i < shroom.size(); i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), ShroomTxtr, &shroom[i]->shroomSrc, &shroom[i]->shroomDst);
		//health bar		
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
		if (isfreezeActive == false)
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &shroom[i]->healthBar);
	}
	//shroom atk stufff
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 100, 230);
	for (unsigned i = 0; i < ushroomatk.size(); i++)
	{
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &(ushroomatk[i]->ushroomAtkDst));
	}
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 100, 230);
	for (unsigned i = 0; i < lshroomatk.size(); i++)
	{
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &(lshroomatk[i]->lshroomAtkDst));
	}
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 100, 230);
	for (unsigned i = 0; i < rshroomatk.size(); i++)
	{
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &(rshroomatk[i]->rshroomAtkDst));
	}
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 100, 230);
	for (unsigned i = 0; i < dshroomatk.size(); i++)
	{
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &(dshroomatk[i]->dshroomAtkDst));
	}

	for (unsigned i = 0; i < levelRect.size(); i++)
	{
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 255, 255);
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), levelRect[i]);
	}

	if (plr1.state == 0)
		SDL_RenderCopy(Engine::Instance().GetRenderer(), plrTxtr, &plr1.plrFrontIdle, &plr1.plrDst);
	else if (plr1.state == 1)
		SDL_RenderCopy(Engine::Instance().GetRenderer(), plrTxtr, &plr1.plrMoveDown, &plr1.plrDst);
	else if (plr1.state == 2)
		SDL_RenderCopy(Engine::Instance().GetRenderer(), plrTxtr, &plr1.plrMoveUp, &plr1.plrDst);
	else if (plr1.state == 3)
		SDL_RenderCopy(Engine::Instance().GetRenderer(), plrTxtr, &plr1.plrMoveLeft, &plr1.plrDst);
	else if (plr1.state == 4)
		SDL_RenderCopy(Engine::Instance().GetRenderer(), plrTxtr, &plr1.plrMoveRight, &plr1.plrDst);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 255, 255);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &plr1.plrwinbar);

	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &plr1.plrHpBar);


	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, fadeMod);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &blackRect);

	if (dynamic_cast<Levelone*>(STMA::GetStates().back()))//if current state is gamestate	
		State::Render();
	//old frog attack left
	/*SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 255, 255);
	for (unsigned i = 0; i < attack.size(); i++)
	{
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &(attack[i]->frogAttackDst));
	}*/
	//old frog attack root
	/*SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 255, 255);
	for (unsigned i = 0; i < rattack.size(); i++)
	{
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &(rattack[i]->rfrogAttackDst));
	}	*/
}

void Levelone::Exit()
{
	for (unsigned i = 0; i < frog.size(); i++)
	{
		delete frog[i];
		frog[i] = nullptr;
	}
	for (unsigned i = 0; i < fly.size(); i++)
	{
		delete fly[i];
		fly[i] = nullptr;
	}
	for (unsigned i = 0; i < playerpew.size(); i++)
	{
		delete playerpew[i];
		playerpew[i] = nullptr;
	}
	for (unsigned i = 0; i < item1.size();i++)
	{
		delete item1[i];
		item1[i] = nullptr;
	}
	for (unsigned i = 0; i < attack.size();i++)
	{
		delete attack[i];
		attack[i] = nullptr;
	}
	for (unsigned i = 0; i < rattack.size();i++)
	{
		delete rattack[i];
		rattack[i] = nullptr;
	}
	for (unsigned i = 0; i < shroom.size();i++)
	{
		delete shroom[i];
		shroom[i] = nullptr;
	}
	for (unsigned i = 0; i < ushroomatk.size();i++)
	{
		delete ushroomatk[i];
		ushroomatk[i] = nullptr;
	}
	for (unsigned i = 0; i < lshroomatk.size();i++)
	{
		delete lshroomatk[i];
		lshroomatk[i] = nullptr;
	}
	for (unsigned i = 0; i < rshroomatk.size();i++)
	{
		delete rshroomatk[i];
		rshroomatk[i] = nullptr;
	}
	for (unsigned i = 0; i < dshroomatk.size();i++)
	{
		delete dshroomatk[i];
		dshroomatk[i] = nullptr;
	}
	shroom.clear();
	shroom.shrink_to_fit();
	ushroomatk.clear();
	ushroomatk.shrink_to_fit();
	lshroomatk.clear();
	lshroomatk.shrink_to_fit();
	rshroomatk.clear();
	rshroomatk.shrink_to_fit();
	dshroomatk.clear();
	dshroomatk.shrink_to_fit();
	fly.clear();
	fly.shrink_to_fit();
	attack.clear();
	attack.shrink_to_fit();
	frog.clear();
	frog.shrink_to_fit();
	playerpew.clear();
	playerpew.shrink_to_fit();
	dumbie.clear();
	dumbie.shrink_to_fit();
	item1.clear();
	item1.shrink_to_fit();
	SDL_DestroyTexture(swamp);
	SDL_DestroyTexture(swamp1);
	SDL_DestroyTexture(swamp2);
	SDL_DestroyTexture(swamp3);
	SDL_DestroyTexture(swamp4);
	SDL_DestroyTexture(swamp5);
	SDL_DestroyTexture(plrTxtr);
	SDL_DestroyTexture(rockTxtr);
	SDL_DestroyTexture(ShroomTxtr);
	SDL_DestroyTexture(DragonFlyTxt);
	SDL_DestroyTexture(vineTexture);
	SDL_DestroyTexture(FrogTxtr);
	Mix_FreeChunk(hurtSfx);
	Mix_FreeChunk(powerSfx);;
	Mix_FreeChunk(projectileRock);
	Mix_FreeChunk(aoeSound);
	Mix_FreeChunk(dashing);
	Mix_FreeChunk(stepSfx);
	Mix_FreeChunk(deathSfx);
	Mix_FreeChunk(turnSfx);
    Mix_FreeMusic(swampSong);
}

void Levelone::Resume()
{
	Mix_ResumeMusic();
}

EndState::EndState() :makiFlying({ 0,0,48,74 }), frameCtr(0), frameMax(9), spriteIdx(0), spriteMax(6) {}

void EndState::Enter()
{
	cout << "entering endstate\npress R to return to title state" << endl;
	gameOverScreen = IMG_LoadTexture(Engine::Instance().GetRenderer(), "bgs/gameOverScreen2.png");
	flyingMaki = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/makigameover.png");
	mainMenuButton = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/mainMenuButton.png");
	exitButton = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/exitButton.png");


	exitButtonSrc = { 0 , 0, 92, 32 };
	mainMenuButtonSrc = { 0, 0, 92, 32 };

	exitButtonDst = { 450, 625, 120, 48 };
	mainMenuButtonDst = {450, 575, 120, 48};
	makiFlyingDst = {375, 265, 256, 256};
}

void EndState::Update()
{
	//if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
	//{

	//	cout << "changing to endstate" << endl;
	//	STMA::ChangeState(new TitleState());
	//	return;
	//}
	if (SDL_GetMouseState(&g_mousePos.x, &g_mousePos.y) == true && g_mousePos.x > exitButtonDst.x && g_mousePos.x < exitButtonDst.x + exitButtonDst.w
		&& g_mousePos.y > exitButtonDst.y && g_mousePos.y < exitButtonDst.y + exitButtonDst.h)
	{
		Engine::Instance().Running() = false;
	}
	if (SDL_GetMouseState(&g_mousePos.x, &g_mousePos.y) == true && g_mousePos.x > mainMenuButtonDst.x && g_mousePos.x < mainMenuButtonDst.x + mainMenuButtonDst.w
		&& g_mousePos.y > mainMenuButtonDst.y && g_mousePos.y < mainMenuButtonDst.y + mainMenuButtonDst.h)
	{
		STMA::ChangeState(new TitleState());
	}
	if (state == 0)
	{
		spriteMax = 6;
		if (spriteIdx > 6)
			spriteIdx = 0;
		if (frameCtr++ == frameMax)
		{
			frameCtr = 0;
			if (++spriteIdx == spriteMax)
			{
				spriteIdx = 0;
			}
			makiFlying.x = 0 + makiFlying.w * spriteIdx;
		}
	}

}

void EndState::Render()
{
	SDL_RenderClear(Engine::Instance().GetRenderer());
	// Any drawing here...
	//Background
	SDL_RenderCopy(Engine::Instance().GetRenderer(), gameOverScreen, NULL, NULL);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), exitButton, &exitButtonSrc, &exitButtonDst);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), mainMenuButton, &mainMenuButtonSrc, &mainMenuButtonDst);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), flyingMaki, &makiFlying, &makiFlyingDst);

	State::Render();

}

void EndState::Exit()
{
	cout << "exiting end state" << endl;
	SDL_DestroyTexture(gameOverScreen);
	SDL_DestroyTexture(flyingMaki);
	SDL_DestroyTexture(mainMenuButton);
	SDL_DestroyTexture(exitButton);
}

WState::WState(){}

void WState::Enter()
{
	cout << "enter winstate" << endl;
	// = Mix_LoadMUS("aud/.mp3");//gametheme
	// = IMG_LoadTexture(Engine::Instance().GetRenderer(), "bgs/.png");
	//bgSrc = { 0,0,1024,768 };
	//Mix_PlayMusic(Titletheme, -1);
	//Mix_VolumeMusic(24); //0-128
}

void WState::Update()
{
	/*if (Engine::Instance().KeyDown(SDL_SCANCODE_N))
	{

		cout << "changing to titlestate" << endl;
		STMA::ChangeState(new TitleState());
		return;
	}*/
}

void WState::Render()
{
	//SDL_RenderClear(Engine::Instance().GetRenderer());
	//SDL_RenderCopy(Engine::Instance().GetRenderer(), Title, NULL, NULL);
	//if (dynamic_cast<TitleState*>(STMA::GetStates().back()))//if current state is gamestate
	//	State::Render();
}

void WState::Exit()
{
	//cout << "exiting titlestate" << endl;
	//Mix_FreeMusic(Titletheme);
	//SDL_DestroyTexture(Title);
}

	
////frog stuff
		//for (unsigned i = 0; i < attack.size(); i++)
		//{
		//	if (attack[i]->frogAttackDst.x >= WIDTH || attack[i]->frogAttackDst.x <= -64 || attack[i]->frogAttackDst.y >= HEIGHT || attack[i]->frogAttackDst.y <= -64)
		//	{
		//		delete attack[i];
		//		attack[i] = nullptr;
		//		attack.erase(attack.begin() + i);
		//		attack.shrink_to_fit();
		//		break;
		//	}
		//}
		//for (unsigned i = 0; i < rattack.size(); i++)
		//{
		//	if (rattack[i]->rfrogAttackDst.x >= WIDTH || rattack[i]->rfrogAttackDst.x <= -64 || rattack[i]->rfrogAttackDst.y >= HEIGHT || rattack[i]->rfrogAttackDst.y <= -64)
		//	{
		//		delete rattack[i];
		//		rattack[i] = nullptr;
		//		rattack.erase(rattack.begin() + i);
		//		rattack.shrink_to_fit();
		//		break;
		//	}
		//}
		//if (isfreezeActive == false)
		//{
		//	for (unsigned i = 0; i < frog.size(); i++)
		//	{
		//		frog[i]->Update(plr1.plrDst);


		//		if (frog[i]->frames >= FPS * ATTACKRATE / 2)
		//		{
		//			frog[i]->resetFrames();
		//			cout << "frog attack!" << endl;
		//			cout << "frog 2nd attack\wow!" << endl;
		//			rattack.push_back(new Attack(frog[i]->frogDst.x, frog[i]->frogDst.y));
		//			rattack.shrink_to_fit();
		//			attack.push_back(new Attack(frog[i]->frogDst.x, frog[i]->frogDst.y));
		//			attack.shrink_to_fit();
		//		}


		//		if (frog[i]->getHp() <= 0) {
		//			plr1.points(10);
		//			//Mix_PlayChannel(-1,, 0);
		//			delete frog[i];
		//			frog[i] = nullptr;
		//			frog.erase(frog.begin() + i);
		//			frog.shrink_to_fit();
		//			break;
		//		}
		//	}
		//}


		//for (unsigned i = 0; i < playerpew.size(); i++)
		//{
		//	for (unsigned j = 0; j < frog.size(); j++)
		//	{

		//		if (SDL_HasIntersection(&playerpew[i]->rockDst, &frog[j]->frogDst)) { //AABB Check

		//			Mix_PlayChannel(-1, hurtSfx, 0);
		//			delete playerpew[i];
		//			playerpew[i] = nullptr;
		//			playerpew.erase(playerpew.begin() + i);
		//			playerpew.shrink_to_fit();
		//			//set frog hp					
		//			frog[j]->setHp(frog[j]->getHp() - playerDamage);
		//			break;
		//		}
		//	}
		//}

		////left
		//for (unsigned i = 0; i < attack.size(); i++)
		//{
		//	if (SDL_HasIntersection(&attack[i]->frogAttackDst, &plr1.plrDst))
		//	{
		//		delete attack[i];
		//		attack[i] = nullptr;
		//		attack.erase(attack.begin() + i);
		//		attack.shrink_to_fit();
		//		plr1.takeDamage(5);
		//		break;
		//	}
		//}
		////root
		//for (unsigned i = 0; i < rattack.size(); i++)
		//{
		//	if (SDL_HasIntersection(&rattack[i]->rfrogAttackDst, &plr1.plrDst))
		//	{
		//		delete rattack[i];
		//		rattack[i] = nullptr;
		//		rattack.erase(rattack.begin() + i);
		//		rattack.shrink_to_fit();
		//		plr1.takeDamage(5);
		//		break;

		//	}
		//}
		//if (isfreezeActive == false)
		//{
		//	for (unsigned i = 0; i < attack.size(); i++)
		//	{

		//		attack[i]->Update(-1);
		//	}

		//}
		//if (isfreezeActive == false)
		//{
		//	for (unsigned i = 0; i < rattack.size(); i++)
		//	{

		//		rattack[i]->Update(1);
		//	}
		//}