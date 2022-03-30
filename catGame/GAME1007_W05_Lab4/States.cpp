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
#include "Boss.h"

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
	//SDL_RenderFillRectcock and balls
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
	//cock and balls
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
	npcTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/wizzy.png");
	DragonFlyTxt = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/dragonfly1.png");
	vineTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/vines.png");
	FrogTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/frogWalking7.png");
	frogbubble = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/bubblegreen.png");
	tree = IMG_LoadTexture(Engine::Instance().GetRenderer(), "bgs/Trees.png");
	portaltxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/portal2.png");
	cloudtxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/cloud.png");
	bosstxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/TheBoss.png");
	plant1 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/plant1.png");
	plant2 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/plant2.png");
	plant3 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/plant3.png");
	stepSfx = Mix_LoadWAV("sfx/step.wav");
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
	beepbeep = Mix_LoadWAV("sfx/beepbeep.wav");
	beeppew = Mix_LoadWAV("sfx/beeppew.mp3");
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
	Mix_Volume(2, 12);

	playerpew.reserve(4);
	dumbie.reserve(4);
	
	//Text box and score stuff
	font = TTF_OpenFont("fonts/font.ttf", 24);
	White = { 255, 255, 255 };

	textBoxRect = { 10, HEIGHT - 190, 1000, 50 };
	textBoxBorder = { 10, HEIGHT - 200, WIDTH - 20, 290 };

	scoreRect = { 800, 10, 150, 40 };
	blackRect = { 0 , 0 , 1024 , 768 };

	surfaceMessage = TTF_RenderText_Solid(font, message, White);
	dummyScore = TTF_RenderText_Solid(font, scoreMessage, White);

	Message = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), surfaceMessage);
	Score = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), dummyScore);
	//portalsrc = { 0,0,32,32 };
	//b.push_back(new Boss(bg1.bossbgDst.x + 600, bg1.bossbgDst.y , 1));
      b.push_back(new Boss(bg1.bgDst.x + 1000, bg1.bgDst.y + 900, 1));
	  b.shrink_to_fit();
}

void GameState::Update()
{
	//debug
	cout << plr1.plrDst.x - bg1.bgDst.x << " - " << plr1.plrDst.y - bg1.bgDst.y << endl;
	
	if (!titleLoading) {
		if (!(fadeMod == 0))
			fadeMod-=fadeSpeed;
		if (fadeMod == 0)
			fadeMod == 0;

		for (unsigned i = 0; i < b.size(); i++)
		{
			b[i]->Update();
			b[i]->BossDst.x -= speedx;
			b[i]->BossDst.y -= speedy;
		}
		for (unsigned i = 0; i < fb.size(); i++)
		{
			fb[i]->Update();
			fb[i]->fBossDst.x -= speedx;
			fb[i]->fBossDst.y -= speedy;
		}

		/*for (unsigned i = 0; i < b.size(); i++)
		{
			if (b[i]->getState() == 1)
			{
				fb.push_back(new Bossf(bg1.bgDst.x, bg1.bgDst.y, 0));
				fb.push_back(new Bossf(bg1.bgDst.x, bg1.bgDst.y, 0));
				fb.push_back(new Bossf(bg1.bgDst.x, bg1.bgDst.y, 0));
				fb.shrink_to_fit(); 
			}

		}*/
		cout << fb.size() << endl;

		for (unsigned i = 0; i < playerpew.size(); i++)
		{
			for (unsigned j = 0; j < b.size(); j++)
			{
				if (b[j]->getState() == 2)
				{
					if (SDL_HasIntersection(&playerpew[i]->rockDst, &b[j]->BossDst)) //AABB Check
					{
						Mix_PlayChannel(-1, hurtSfx, 0);
						delete playerpew[i];
						playerpew[i] = nullptr;
						playerpew.erase(playerpew.begin() + i);
						playerpew.shrink_to_fit();
						delete b[j];
						b[j] = nullptr;
						b.erase(b.begin() + j);
						b.shrink_to_fit();
						break;
					}
				}

			}
		}
		for (unsigned i = 0; i < playerpew.size(); i++)
		{
			for (unsigned j = 0; j < fb.size(); j++)
			{
				if (fb[j]->getState() == 2)
				{
					if (SDL_HasIntersection(&playerpew[i]->rockDst, &fb[j]->fBossDst)) //AABB Check
					{
						Mix_PlayChannel(-1, hurtSfx, 0);
						delete playerpew[i];
						playerpew[i] = nullptr;
						playerpew.erase(playerpew.begin() + i);
						playerpew.shrink_to_fit();
						delete fb[j];
						fb[j] = nullptr;
						fb.erase(fb.begin() + j);
						fb.shrink_to_fit();
						break;
					}
				}

			}
		}
		if (EVMA::KeyPressed(SDL_SCANCODE_TAB))
		{
			cout << "Changing to tabState" << endl;
			//pause the music track
			STMA::PushState(new TabState());
			Mix_PauseMusic();
		}
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
		if (EVMA::KeyPressed(SDL_SCANCODE_2))
		{

			cout << "changing to boss fight!" << endl;
			STMA::ChangeState(new BossState());
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
		/*bool wallHitx = false;
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
		}*/
		bg1.bgDst.x -= speedx;
		bg1.bgDst.y -= speedy;

		bg1.treedst.x -= speedx;
		bg1.treedst.y -= speedy;

		for (unsigned i = 0;i < portal.size();i++)
		{
			portal[i]->portalDst.x -= speedx;
			portal[i]->portalDst.y -= speedy;
		}
		

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
			fly[i]->HP.x -= speedx;
			fly[i]->HP.y -= speedy;
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
		}
		for (unsigned i = 0; i < fly.size(); i++) {
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
		for (unsigned i = 0; i < frog.size(); i++) 
		{
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
			if (SDL_HasIntersection(&frog[i]->frogDst, &plr1.plrDst))
			{
				plr1.takeDamage(2);
			}
			
			if ((Util::distanceOffset(plr1.plrDst, frog[i]->frogDst) < 550))
			{
				if (frog[i]->getShootTimer() == 0)
				{
					bub.push_back(new Bubble(frog[i]->frogDst.x + 40, frog[i]->frogDst.y + 40));
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
			if (Util::distanceOffset(plr1.plrDst, bub[i]->bubbleDst) < 100) {
				plr1.takeDamage(1);
				delete bub[i];
				bub[i] = nullptr;
				bub.erase(bub.begin() + i);
				bub.shrink_to_fit();
			}
			else if (Util::distanceOffset(plr1.plrDst, bub[i]->bubbleDst) > 800) {
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
						strcpy_s(message, "Press Tab for info on abilities & the objective");
						surfaceMessage = TTF_RenderText_Solid(font, message, White);
						Message = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), surfaceMessage);
					}
					else if (textBoxCounter == 2) {
						strcpy_s(message, "When youre ready just press 1, in a meantime ima spawn some dumbies");
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
		//freeze
		if (freezeCD > 700)
		{
			if (EVMA::KeyPressed(SDL_SCANCODE_F))
			{
				isfreezeActive = true;
				freezetimer = 0;
				freezeCD = 0;
			}
		}
		//freezetimer++;
		if (isfreezeActive)
		{
			if (freezetimer > 150)
			{
				isfreezeActive = false;
				freezetimer = 0;
				freezeCD = 0;
			}
		}
		//cout << "freezetimer" << freezetimer++ << " | " << freezeCD++ << "freezecd<-" << endl;
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

				dumbie.push_back(new Enemy(bg1.bgDst.x + rand() % 1000 + 800, bg1.bgDst.y + rand() % 500 + 800, 3));
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
	
	for (unsigned i = 0; i < portal.size();i++) 
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), portaltxtr, &(portal[i]->portalSrc), &(portal[i]->portalDst));
	}
	//for boss
	for (unsigned i = 0; i < b.size();i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), bosstxtr, &b[i]->BossSrc, &b[i]->BossDst);
		//health bar	
		/*SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
		if (isfreezeActive == false)
			SDL_RenderFillRect(Engine::Instance().GetRenderer(), &b[i]->HP);
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
		if (isfreezeActive == false)
			SDL_RenderFillRect(Engine::Instance().GetRenderer(), &b[i]->healthBar);*/
	}


	//fake boss
	for (unsigned i = 0; i < fb.size();i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), bosstxtr, &fb[i]->fBossSrc, &fb[i]->fBossDst);
		//health bar				
		//SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
		/*if (isfreezeActive == false)
			SDL_RenderFillRect(Engine::Instance().GetRenderer(), &fb[i]->HP);
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
		if (isfreezeActive == false)
			SDL_RenderFillRect(Engine::Instance().GetRenderer(), &fb[i]->healthBar);*/
	}
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
		
	
	

	
	//NPC
	SDL_RenderCopyEx(Engine::Instance().GetRenderer(), npcTxtr, &catDude.npcSrc, &catDude.npcDst, NULL, NULL, SDL_FLIP_HORIZONTAL);

	//rock	
	for (unsigned i = 0; i < playerpew.size(); i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), rockTxtr,
			&(playerpew[i]->rockSrc), &(playerpew[i]->rockDst));
	}
	for (unsigned i = 0; i < cloud.size(); i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), cloudtxtr,
			&(cloud[i]->cloudSrc), &(cloud[i]->cloudDst));
	}

	//bubble 
	for (unsigned i = 0; i < bub.size(); i++) 
	{
		//SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 255);
		SDL_RenderCopy(Engine::Instance().GetRenderer(), frogbubble,NULL,&(bub[i]->bubbleDst));
	}
	////item
	//for (unsigned i = 0; i < item1.size(); i++)
	//{
	//	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
	//	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &item1[i]->item);
	//}

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
		
		if (fly[i]->lookLeft)
			SDL_RenderCopyEx(Engine::Instance().GetRenderer(), DragonFlyTxt, &fly[i]->flySrc, &fly[i]->flyDst, NULL, NULL, SDL_FLIP_NONE);
		else if (!fly[i]->lookLeft)
			SDL_RenderCopyEx(Engine::Instance().GetRenderer(), DragonFlyTxt, &fly[i]->flySrc, &fly[i]->flyDst, NULL, NULL, SDL_FLIP_HORIZONTAL);
		//health bar
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &fly[i]->HP);
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

	

	//score text
	if (spawnDummies) {
		SDL_RenderCopy(Engine::Instance().GetRenderer(), Score, NULL, &scoreRect);
	}
	//SDL_RenderPresent(Engine::Instance().GetRenderer()); // Flip buffers - send data to window.
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, fadeMod);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &blackRect);

	SDL_RenderCopy(Engine::Instance().GetRenderer(), tree, &bg1.treesrc, &bg1.treedst);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &plr1.hpborder);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &plr1.plrHpBar);
	//text box
	if (renderTextBox) {
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &textBoxBorder);
		SDL_RenderCopy(Engine::Instance().GetRenderer(), Message, NULL, &textBoxRect);
	}
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
	fb.clear();
	fb.shrink_to_fit();
	b.clear();
	b.shrink_to_fit();
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
	SDL_DestroyTexture(frogbubble);
	SDL_DestroyTexture(tree);
	Mix_FreeChunk(beepbeep);
	Mix_FreeChunk(beeppew);
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
	SDL_DestroyTexture(bosstxtr);
	SDL_DestroyTexture(plant1);
	SDL_DestroyTexture(plant2);
	SDL_DestroyTexture(plant3);
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
	DragonFlyTxt = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/dragonfly1.png");
	vineTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/vines.png");
	FrogTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/frogWalking7.png");
	ShroomTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/mushroom.png");
	cloudtxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/cloud.png");
	portaltxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/portal2.png");
	frogbubble = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/bubblegreen.png");
	freezeui = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/freeze.png");
	aoe = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/aoeui.png");
	wpng = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/winStateBeta.png");
	heartTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/heart.png");
	wSrc = { 0,0,256,198 };

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
	swampSong = Mix_LoadMUS("Aud/swamp.mp3");
	Mix_PlayMusic(swampSong, -1);
	Mix_VolumeMusic(15); //0-128
	Mix_Volume(-1, 50);
	playerpew.reserve(4);
	freezeSrc = { 0,0,64,64 };
	freezeDst = { 10,700,64,64 };
	aoeSrc = { 0,0,64,64 };
	aoeDst = { 75,700,64,64 };
	mushrooms = mushroomsLeft = 1;
	mushAdjust = -1;

	font = TTF_OpenFont("fonts/font.ttf", 24);
	White = { 255, 255, 255 };
	mushScoreRect = { 700, 10, 300, 30 };
	mushScore = TTF_RenderText_Solid(font, mushMessage, White);
	mushLeft = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), mushScore);

	loadArea = true;

	areaNum = 0;

	blackRect = { 0 , 0 , 1024 , 768 };
	exitRect = { 0,0, 10, 10 };

	mushStr = "Mushrooms Left = " + to_string(mushroomsLeft);
	strcpy_s(mushMessage, mushStr.c_str());
	mushScore = TTF_RenderText_Solid(font, mushMessage, White);
	mushLeft = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), mushScore);
	
	for (int i = 0; i < 13; i++)
	{
		bg.push_back(new Level1Background(rand() % 5, 13));
	}
}



void Levelone::Update()
{
	
	//freeze
	if (freezeCD > 600)
	{
		if (EVMA::KeyPressed(SDL_SCANCODE_F))
		{
			isfreezeActive = true;
			freezetimer = 0;
			freezeCD = 0;
		}
	}
	freezetimer++;
	if (isfreezeActive)
	{
		if (freezetimer > 150)
		{
			isfreezeActive = false;
			freezetimer = 0;
			freezeCD = 0;
		}
	}
	if (!lvlLoading) {
		if (!(fadeMod == 0))
			fadeMod -= fadeSpeed;
		if (fadeMod == 0)
			fadeMod == 0;
		/*if (plr1.winbar >= 150)
		{
			STMA::ChangeState(new WState());
			return;
		}*/
		/*cout << exitRect.x << endl;
		cout << exitRect.y << endl;
		cout << bg[areaNum]->getBg() << endl;*/
		if (loadArea) {
			//clear vectors
			playerpew.clear();
			vine.clear();
			fly.clear();
			frog.clear();
			bub.clear();
			shroom.clear();
			levelRect.clear();
			cloud.clear();
			portal.clear();
			heart.clear();
			plr1.setPlrSpd(0);
			mushAdjust++;
			if (mushAdjust == 2) {
				mushrooms++;
				mushAdjust = 0;
			}
			mushroomsLeft = mushrooms;
			mushStr = "Mushrooms Left = " + to_string(mushroomsLeft);
			strcpy_s(mushMessage, mushStr.c_str());
			mushScore = TTF_RenderText_Solid(font, mushMessage, White);
			mushLeft = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), mushScore);
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
				//levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x -100,bg[areaNum]->swampDst.y + 420,10, 228 });

				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + -50,bg[areaNum]->swampDst.y + 510 + 128,1430,10 });
				
				mushroomSpot = rand() % 6;
				for (int i = 0; i < mushrooms; i++) {
					if (mushroomSpot == 0) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 380, bg[areaNum]->swampDst.y + 200, 3));
					}
					else if (mushroomSpot == 1) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 1500, bg[areaNum]->swampDst.y + 300, 3));
					}
					else if (mushroomSpot == 2) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 700, bg[areaNum]->swampDst.y + 200, 3));
					}
					else if (mushroomSpot == 3) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 600, bg[areaNum]->swampDst.y + 1050, 3));
					}
					else if (mushroomSpot == 4) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 1200, bg[areaNum]->swampDst.y + 900, 3));
					}
					else if (mushroomSpot == 5) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 300, bg[areaNum]->swampDst.y + 1050, 3));
					}
					mushroomSpot++;
					if (mushroomSpot > 5)
						mushroomSpot = 0;
				}	
				//enemy spawn
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 500, bg[areaNum]->swampDst.y + 450));
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 1400, bg[areaNum]->swampDst.y + 350));
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 1450, bg[areaNum]->swampDst.y + 1100));
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 450, bg[areaNum]->swampDst.y + 1200));


				for (int i = 0; i < rand()%mushrooms + 1; i++)
				{
					fly.push_back(new DragonFly(bg[areaNum]->swampDst.x + 500, bg[areaNum]->swampDst.y + 250, 1));
				}
				
				for (int i = 0; i < rand() % mushrooms; i++)
				{
					fly.push_back(new DragonFly(bg[areaNum]->swampDst.x + 450, bg[areaNum]->swampDst.y + 1000, 1));
				}

				if (mushrooms > 2) {
					if (rand()%2)
						frog.push_back(new Frog(bg[areaNum]->swampDst.x + 1400, bg[areaNum]->swampDst.y + 350, 4));
				}
				if (mushrooms > 4) {
					for (int i = 0; i < (rand() % (mushrooms / 2 + 1) + 1); i++)
					{
						fly.push_back(new DragonFly(bg[areaNum]->swampDst.x + 1550, bg[areaNum]->swampDst.y + 1100, 1));
					}
				}
				
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
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 700,bg[areaNum]->swampDst.y -90,600,10 });
				//levelRect.push_back(new SDL_Rect{ bg[areaNum]->swamp1Dst.x,bg[areaNum]->swamp1Dst.y });

				mushroomSpot = rand() % 6;
				for (int i = 0; i < mushrooms; i++) {
					if (mushroomSpot == 0) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 260, bg[areaNum]->swampDst.y + 350, 3));
					}
					else if (mushroomSpot == 1) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 1700, bg[areaNum]->swampDst.y + 1100, 3));
					}
					else if (mushroomSpot == 2) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 260, bg[areaNum]->swampDst.y + 1100, 3));
					}
					else if (mushroomSpot == 3) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 1700, bg[areaNum]->swampDst.y + 300, 3));
					}
					else if (mushroomSpot == 4) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 950, bg[areaNum]->swampDst.y + 500, 3));
					}
					else if (mushroomSpot == 5) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 950, bg[areaNum]->swampDst.y + 900, 3));
					}
					mushroomSpot++;
					if (mushroomSpot > 5)
						mushroomSpot = 0;
				}
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 700, bg[areaNum]->swampDst.y + 400));
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 1400, bg[areaNum]->swampDst.y + 400));
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 1750, bg[areaNum]->swampDst.y + 700));
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 200, bg[areaNum]->swampDst.y + 700));
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 650, bg[areaNum]->swampDst.y + 1000));
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 1300, bg[areaNum]->swampDst.y + 1000));

				frog.push_back(new Frog(bg[areaNum]->swampDst.x + 950, bg[areaNum]->swampDst.y + 900, 4));

				for (int i = 0; i < (rand() % (mushrooms)) + 1; i++)//middle bottom
				{
					fly.push_back(new DragonFly(bg[areaNum]->swampDst.x + 950, bg[areaNum]->swampDst.y + 1100, 1));
				}
				if (mushrooms > 1) {
					for (int i = 0; i < (rand() % (mushrooms)) + 1; i++)//top left
					{
						fly.push_back(new DragonFly(bg[areaNum]->swampDst.x + 400, bg[areaNum]->swampDst.y + 500, 1));
					}
				}
				if (mushrooms > 2) {
					if (rand() % 2)
						frog.push_back(new Frog(bg[areaNum]->swampDst.x + 650, bg[areaNum]->swampDst.y + 700, 4));
					for (int i = 0; i < (rand() % (mushrooms)) + 1; i++)//bottom left
					{
						fly.push_back(new DragonFly(bg[areaNum]->swampDst.x + 400, bg[areaNum]->swampDst.y + 1000, 1));
					}
				}
				if (mushrooms > 3) {
					for (int i = 0; i < (rand() % (mushrooms)) + 1; i++)// bottom right
					{
						fly.push_back(new DragonFly(bg[areaNum]->swampDst.x + 1700, bg[areaNum]->swampDst.y + 1000, 1));
					}
					for (int i = 0; i < (rand() % (mushrooms)) + 1; i++)//top right
					{
						fly.push_back(new DragonFly(bg[areaNum]->swampDst.x + 1700, bg[areaNum]->swampDst.y + 350, 1));
					}
				}
				if (mushrooms > 4) {
					if (rand() % 2)
						frog.push_back(new Frog(bg[areaNum]->swampDst.x + 1250, bg[areaNum]->swampDst.y + 700, 4));
				}
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
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x + 70,bg[areaNum]->swampDst.y -70 ,400,10 });

				mushroomSpot = rand() % 6;
				for (int i = 0; i < mushrooms; i++) {
					if (mushroomSpot == 0) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 1600, bg[areaNum]->swampDst.y + 400, 3));
					}
					else if (mushroomSpot == 1) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 800, bg[areaNum]->swampDst.y + 400, 3));
					}
					else if (mushroomSpot == 2) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 250, bg[areaNum]->swampDst.y + 1100, 3));
					}
					else if (mushroomSpot == 3) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 700, bg[areaNum]->swampDst.y + 800, 3));
					}
					else if (mushroomSpot == 4) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 1600, bg[areaNum]->swampDst.y + 800, 3));
					}
					else if (mushroomSpot == 5) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 1000, bg[areaNum]->swampDst.y + 1100, 3));
					}
					mushroomSpot++;
					if (mushroomSpot > 5)
						mushroomSpot = 0;
				}
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 300, bg[areaNum]->swampDst.y + 400));
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 600, bg[areaNum]->swampDst.y + 1000));
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 1000, bg[areaNum]->swampDst.y + 500));
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 1600, bg[areaNum]->swampDst.y + 750));

				for (int i = 0; i < (rand() % (mushrooms)) + 1; i++)
				{
					fly.push_back(new DragonFly(bg[areaNum]->swampDst.x + 1600, bg[areaNum]->swampDst.y + 500, 1));
				}
				if (rand()%2)
					frog.push_back(new Frog(bg[areaNum]->swampDst.x + 1550, bg[areaNum]->swampDst.y + 1100, 4));
				if (rand()%2) {
					for (int i = 0; i < (rand() % (mushrooms)) + 1; i++)
					{
						fly.push_back(new DragonFly(bg[areaNum]->swampDst.x + 1000, bg[areaNum]->swampDst.y + 1000, 1));
					}
				}
				if (mushrooms > 2) {
					for (int i = 0; i < (rand() % (mushrooms)) + 1; i++)
					{
						fly.push_back(new DragonFly(bg[areaNum]->swampDst.x + 400, bg[areaNum]->swampDst.y + 700, 1));
					}
				}
				if (mushrooms > 3) {
					frog.push_back(new Frog(bg[areaNum]->swampDst.x + 1200, bg[areaNum]->swampDst.y + 300, 4));
				}
				if (mushrooms > 4) {
					if (rand()%2)
						frog.push_back(new Frog(bg[areaNum]->swampDst.x + 200, bg[areaNum]->swampDst.y + 1000, 4));
				}
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
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x -10,bg[areaNum]->swampDst.y + 1009,10,400 });
				mushroomSpot = rand() % 6;
				for (int i = 0; i < mushrooms; i++) {
					if (mushroomSpot == 0) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 950, bg[areaNum]->swampDst.y + 200, 3));
					}
					else if (mushroomSpot == 1) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 300, bg[areaNum]->swampDst.y + 400, 3));
					}
					else if (mushroomSpot == 2) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 700, bg[areaNum]->swampDst.y + 700, 3));
					}
					else if (mushroomSpot == 3) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 1150, bg[areaNum]->swampDst.y + 600, 3));
					}
					else if (mushroomSpot == 4) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 1600, bg[areaNum]->swampDst.y + 250, 3));
					}
					else if (mushroomSpot == 5) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 1150, bg[areaNum]->swampDst.y + 1200, 3));
					}
					mushroomSpot++;
					if (mushroomSpot > 5)
						mushroomSpot = 0;
				}
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 700, bg[areaNum]->swampDst.y + 1250));
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 1100, bg[areaNum]->swampDst.y + 900));
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 500, bg[areaNum]->swampDst.y + 550));
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 1000, bg[areaNum]->swampDst.y + 350));
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 300, bg[areaNum]->swampDst.y + 800));
				
				frog.push_back(new Frog(bg[areaNum]->swampDst.x + 1450, bg[areaNum]->swampDst.y + 300, 4));
				for (int i = 0; i < (rand() % (mushrooms)) + 4; i++)
				{
					fly.push_back(new DragonFly(bg[areaNum]->swampDst.x + 700, bg[areaNum]->swampDst.y + 850, 1));
				}
				if (mushrooms > 2)
				for (int i = 0; i < rand() % 3; i++)
				{
					fly.push_back(new DragonFly(bg[areaNum]->swampDst.x + 1000, bg[areaNum]->swampDst.y + 1100, 1));
				}
				if (mushrooms > 3) {
					if (rand() % 2)
						frog.push_back(new Frog(bg[areaNum]->swampDst.x + 350, bg[areaNum]->swampDst.y + 400, 4));
				}
				if (mushrooms > 4) {
					for (int i = 0; i < (rand() % (mushrooms)) + 1; i++)
					{
						fly.push_back(new DragonFly(bg[areaNum]->swampDst.x + 1000, bg[areaNum]->swampDst.y + 350, 1));
					}
				}

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
				levelRect.push_back(new SDL_Rect{ bg[areaNum]->swampDst.x -10,bg[areaNum]->swampDst.y +630,10,400 });

				mushroomSpot = rand() % 6;
				for (int i = 0; i < mushrooms; i++) {
					if (mushroomSpot == 0) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 500, bg[areaNum]->swampDst.y + 200, 3));
					}
					else if (mushroomSpot == 1) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 1600, bg[areaNum]->swampDst.y + 200, 3));
					}
					else if (mushroomSpot == 2) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 1300, bg[areaNum]->swampDst.y + 1150, 3));
					}
					else if (mushroomSpot == 3) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 500, bg[areaNum]->swampDst.y + 1200, 3));
					}
					else if (mushroomSpot == 4) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 1000, bg[areaNum]->swampDst.y + 700, 3));
					}
					else if (mushroomSpot == 5) {
						shroom.push_back(new Shroom(bg[areaNum]->swampDst.x + 1200, bg[areaNum]->swampDst.y + 1200, 3));
					}
					mushroomSpot++;
					if (mushroomSpot > 5)
						mushroomSpot = 0;
				}
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 700, bg[areaNum]->swampDst.y + 800));
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 1200, bg[areaNum]->swampDst.y + 800));
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 1200, bg[areaNum]->swampDst.y + 200));
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 750, bg[areaNum]->swampDst.y + 200));
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 800, bg[areaNum]->swampDst.y + 500));
				if (rand() % 2)
					vine.push_back(new Vines(bg[areaNum]->swampDst.x + 600, bg[areaNum]->swampDst.y + 1200));

				frog.push_back(new Frog(bg[areaNum]->swampDst.x + 750, bg[areaNum]->swampDst.y + 1000, 4));
				for (int i = 0; i < (rand() % 2) + 2; i++)
				{
					fly.push_back(new DragonFly(bg[areaNum]->swampDst.x + 1600, bg[areaNum]->swampDst.y + 150, 1));
				}
				if (mushrooms > 2)
					frog.push_back(new Frog(bg[areaNum]->swampDst.x + 1100, bg[areaNum]->swampDst.y + 1000, 4));
				if (mushrooms > 3) {
					if (rand()%2)
						frog.push_back(new Frog(bg[areaNum]->swampDst.x + 1100, bg[areaNum]->swampDst.y + 300, 4));
				}
				if (mushrooms > 5) {
					if (rand() % 2)
						frog.push_back(new Frog(bg[areaNum]->swampDst.x + 750, bg[areaNum]->swampDst.y + 300, 4));
				}
			}

			loadArea = false;
		}
		{
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
				//if (SDL_HasIntersection(levelRect[26], &plr1.plrDst)) {//right
				//	//speedx = 0;
				//	//speedy = 0;
				//	//speedx++;
				//}

				for (int i = 0; i < levelRect.size(); i++)
				{
					if (!wallHitx)
						levelRect[i]->x -= speedx;
					if (!wallHity)
						levelRect[i]->y -= speedy;
				}
				if (mushroomsLeft == 0) {
					mushroomsLeft--;
					portal.push_back(new Portal(bg[areaNum]->swampDst.x + 80, bg[areaNum]->swampDst.y + 1241));
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
				if (SDL_HasIntersection(levelRect[11], &plr1.plrDst)) {//
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
				if (mushroomsLeft == 0) {
					mushroomsLeft--;
					portal.push_back(new Portal(bg[areaNum]->swampDst.x + 980, bg[areaNum]->swampDst.y + 1286));
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
				if (SDL_HasIntersection(levelRect[6], &plr1.plrDst)) {//
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
				if (mushroomsLeft == 0) {
					mushroomsLeft--;
					portal.push_back(new Portal(bg[areaNum]->swampDst.x + 1559, bg[areaNum]->swampDst.y + 1295));
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
				if (SDL_HasIntersection(levelRect[8], &plr1.plrDst)) {//
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
				if (mushroomsLeft == 0) {
					mushroomsLeft--;
					portal.push_back(new Portal(bg[areaNum]->swampDst.x + 1837, bg[areaNum]->swampDst.y + 246));
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
				if (SDL_HasIntersection(levelRect[10], &plr1.plrDst)) {//
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
				if (mushroomsLeft == 0) {
					mushroomsLeft--;
					portal.push_back(new Portal(bg[areaNum]->swampDst.x + 1850, bg[areaNum]->swampDst.y + 146));
				}
			}
		}
		bg[areaNum]->swampDst.x -= speedx;
		bg[areaNum]->swampDst.y -= speedy;
		if (!wallHitx)
			exitRect.x -= speedx;
		if (!wallHity)
			exitRect.y -= speedy;

		for (int i = 0; i < portal.size(); i++)
		{
			if (Util::distance(portal[i]->portalDst, plr1.plrDst) < 80) {
				loadArea = true;
				areaNum++;
				cout << "hit" << endl;
			}
		}

		if (mushrooms > 6)
		{
			STMA::PushState(new WState());
			Mix_PauseMusic();
			return;
		}
		if (plr1.plrHp <= 0)
		{
			STMA::ChangeState(new EndState());
			return;
		}
		freezeCD++;
		//cout <<"noobtimer"<< Noobtimer++ <<" | "<<ezModeCD++ << "ezmodecd<-" << endl;
		//cout << "freezetimer" << freezetimer++ << " | " << freezeCD << "freezecd<-" << endl;
		//cout << plr1.plrDst.x - bg[areaNum]->swampDst.x << " - " << plr1.plrDst.y - bg[areaNum]->swampDst.y << endl; // for spawning things on bg
		// cout << plr1.plrDst.x << " , " << plr1.plrDst.y  << endl;
		//cout << bg[areaNum]->swampDst.x << "||" << bg[areaNum]->swampDst.y << endl; // for spawning player on bg
		
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

		//shroom
		for (unsigned i = 0; i < shroom.size(); i++)
		{
			shroom[i]->shroomDst.x -= speedx;
			shroom[i]->shroomDst.y -= speedy;
			if (isfreezeActive == false)
				shroom[i]->Update();
				if (Util::distanceOffset(plr1.plrDst, shroom[i]->shroomDst) < 550) {
					if (shroom[i]->shootTimer == 0) {
						cloud.push_back(new Cloud(shroom[i]->shroomDst.x + 45, shroom[i]->shroomDst.y + 30, 5, 'y'));
						cloud.push_back(new Cloud(shroom[i]->shroomDst.x + 45, shroom[i]->shroomDst.y + 30, 5 * -1, 'y'));
						cloud.push_back(new Cloud(shroom[i]->shroomDst.x + 45, shroom[i]->shroomDst.y + 30, 5, 'x'));
						cloud.push_back(new Cloud(shroom[i]->shroomDst.x + 45, shroom[i]->shroomDst.y + 30, 5 * -1, 'x'));
						cloud.shrink_to_fit();
					}
				}
			
			if (shroom[i]->getHp() <= 0)
			{
				plr1.points(10);
				Mix_PlayChannel(-1, deathSfx, 0);
				delete shroom[i];
				shroom[i] = nullptr;
				shroom.erase(shroom.begin() + i);
				shroom.shrink_to_fit();
				mushroomsLeft--;
				mushStr = "Mushrooms Left = " + to_string(mushroomsLeft);
				strcpy_s(mushMessage, mushStr.c_str());
				mushScore = TTF_RenderText_Solid(font, mushMessage, White);
				mushLeft = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), mushScore);
			}
		}
		// shroom cloud
		for (unsigned i = 0; i < cloud.size(); i++)
		{
			cloud[i]->cloudDst.x -= speedx;
			cloud[i]->cloudDst.y -= speedy;
			if (isfreezeActive == false)
			cloud[i]->Update();
			if (Util::distanceOffset(plr1.plrDst, cloud[i]->cloudDst) < 100) {
				plr1.takeDamage(0.5);
				delete cloud[i];
				cloud[i] = nullptr;
				cloud.erase(cloud.begin() + i);
				cloud.shrink_to_fit();
			}
		}
		//DragonFly
		for (unsigned i = 0; i < fly.size(); i++)
		{
			if (isfreezeActive == false)
			fly[i]->Update();
			if (!wallHitx)
				fly[i]->flyDst.x -= speedx;
			if (!wallHity)
				fly[i]->flyDst.y -= speedy;

			if (SDL_HasIntersection(&fly[i]->flyDst, &plr1.plrDst)) {
				plr1.takeDamage(0.5);
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
					//move this to health function if health is > 1
					if (rand() % 20 == 0)
						heart.push_back(new Heart(fly[i]->flyDst.x + 30, fly[i]->flyDst.y + 30));
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

		for (unsigned i = 0; i < portal.size();i++)
		{
			portal[i]->portalDst.x -= speedx;
			portal[i]->portalDst.y -= speedy;
		}
		//heart
		for (unsigned i = 0; i < heart.size(); i++)
		{
			heart[i]->heartDst.x -= speedx;
			heart[i]->heartDst.y -= speedy;

			if (plr1.plrHp <= 9) {
				if (SDL_HasIntersection(&plr1.plrDst, &heart[i]->heartDst)) {
					Mix_PlayChannel(-1, powerSfx, 0);
					delete heart[i];
					heart[i] = nullptr;
					heart.erase(heart.begin() + i);
					heart.shrink_to_fit();
					plr1.gainHealth(1);
				}
			}
			else if (plr1.plrHp < 10 && plr1.plrHp > 9) {
				if (SDL_HasIntersection(&plr1.plrDst, &heart[i]->heartDst)) {
					Mix_PlayChannel(-1, powerSfx, 0);
					delete heart[i];
					heart[i] = nullptr;
					heart.erase(heart.begin() + i);
					heart.shrink_to_fit();
					plr1.plrHp = plr1.maxHp - plr1.plrHp;
				}
			}
		}
		 
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
		if (EVMA::KeyPressed(SDL_SCANCODE_TAB))
		{
			cout << "Changing to tabState" << endl;
			//pause the music track
			STMA::PushState(new TabState());
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

			if (Util::distanceOffset(plr1.plrDst, playerpew[i]->rockDst) > 600)
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
		
		//frog
		for (unsigned i = 0; i < frog.size(); i++)
		{
			if (isfreezeActive == false)
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
			if (SDL_HasIntersection(&frog[i]->frogDst, &plr1.plrDst))
			{
				plr1.takeDamage(1);
			}

			if ((Util::distanceOffset(plr1.plrDst, frog[i]->frogDst) < 550))
			{
				if (frog[i]->getShootTimer() == 0)
				{
					bub.push_back(new Bubble(frog[i]->frogDst.x + 40, frog[i]->frogDst.y + 40));
				}
			}
			if (frog[i]->getHp() <= 0) {
				Mix_PlayChannel(-1, deathSfx, 0);
				if (rand() % 5 == 0)
					heart.push_back(new Heart(frog[i]->frogDst.x + 30, frog[i]->frogDst.y + 30));
				delete frog[i];
				frog[i] = nullptr;
				frog.erase(frog.begin() + i);
				frog.shrink_to_fit();
			}

		}
		//bubble
		for (int i = 0; i < bub.size(); i++)
		{
			if (isfreezeActive == false)
			bub[i]->Update(plr1.plrDst);
			if (!wallHitx)
				bub[i]->bubbleDst.x -= speedx;
			if (!wallHity)
				bub[i]->bubbleDst.y -= speedy;
			if (Util::distanceOffset(plr1.plrDst, bub[i]->bubbleDst) < 100) {
				plr1.takeDamage(0.5);
				delete bub[i];
				bub[i] = nullptr;
				bub.erase(bub.begin() + i);
				bub.shrink_to_fit();
			}
			else if (Util::distanceOffset(plr1.plrDst, bub[i]->bubbleDst) > 800) {
				delete bub[i];
				bub[i] = nullptr;
				bub.erase(bub.begin() + i);
				bub.shrink_to_fit();
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
					if (isfreezeActive == false)
					shroom[j]->setHp(shroom[j]->getHp() - playerDamage);
					break;					
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
	
	
	for (unsigned i = 0; i < portal.size();i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), portaltxtr, &portal[i]->portalSrc, &portal[i]->portalDst);
	}
	//rock	
	for (unsigned i = 0; i < playerpew.size(); i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), rockTxtr,
			&(playerpew[i]->rockSrc), &(playerpew[i]->rockDst));
	}
	for (unsigned i = 0; i < cloud.size(); i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), cloudtxtr,
			&(cloud[i]->cloudSrc), &(cloud[i]->cloudDst));
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
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);	
		if (isfreezeActive == false)
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &frog[i]->HP);		
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
		if (isfreezeActive == false)
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &frog[i]->healthBar);
	}
	//bubble 
	for (unsigned i = 0; i < bub.size(); i++)
	{
		//SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 255);
		SDL_RenderCopy(Engine::Instance().GetRenderer(), frogbubble, NULL, &(bub[i]->bubbleDst));
	}
	
	//dragoon fly
	for (unsigned i = 0; i < fly.size(); i++)
	{
		if (fly[i]->lookLeft)
			SDL_RenderCopyEx(Engine::Instance().GetRenderer(), DragonFlyTxt, &fly[i]->flySrc, &fly[i]->flyDst, NULL, NULL, SDL_FLIP_NONE);
		else if (!fly[i]->lookLeft)
			SDL_RenderCopyEx(Engine::Instance().GetRenderer(), DragonFlyTxt, &fly[i]->flySrc, &fly[i]->flyDst, NULL, NULL, SDL_FLIP_HORIZONTAL);
		//health bar			
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
		if (isfreezeActive == false)
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &fly[i]->HP);		
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
		if (isfreezeActive == false)
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &fly[i]->healthBar);
	}
	//shroom
	for (unsigned i = 0; i < shroom.size(); i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), ShroomTxtr, &shroom[i]->shroomSrc, &shroom[i]->shroomDst);
		//health bar				
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
		if (isfreezeActive == false)
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &shroom[i]->HP);		
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
		if (isfreezeActive == false)
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &shroom[i]->healthBar);
	}
	//Heart
	for (unsigned i = 0; i < heart.size(); i++) {
		SDL_RenderCopy(Engine::Instance().GetRenderer(), heartTxtr, &heart[i]->heartSrc, &heart[i]->heartDst);
	}
	
	//score
	SDL_RenderCopy(Engine::Instance().GetRenderer(), mushLeft, NULL, &mushScoreRect);

	/*for (unsigned i = 0; i < levelRect.size(); i++)
	{
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 255, 255);
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), levelRect[i]);
	}*/

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
	//SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 255, 255);
	//SDL_RenderFillRect(Engine::Instance().GetRenderer(), &plr1.plrwinbar);
	if (freezeCD > 600)
	SDL_RenderCopy(Engine::Instance().GetRenderer(),freezeui,&freezeSrc,&freezeDst);

	if (spcooldown > 200)
	SDL_RenderCopy(Engine::Instance().GetRenderer(),aoe,&aoeSrc,&aoeDst);	
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &plr1.hpborder);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &plr1.plrHpBar);
	

	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, fadeMod);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &blackRect);

	if (dynamic_cast<Levelone*>(STMA::GetStates().back()))//if current state is gamestate	
		State::Render();
	
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
	
	shroom.clear();
	shroom.shrink_to_fit();
	fly.clear();
	fly.shrink_to_fit();
	frog.clear();
	frog.shrink_to_fit();
	playerpew.clear();
	playerpew.shrink_to_fit();
	dumbie.clear();
	dumbie.shrink_to_fit();
	item1.clear();
	item1.shrink_to_fit();
	heart.clear();
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
	SDL_DestroyTexture(cloudtxtr);
	SDL_DestroyTexture(portaltxtr);
	SDL_DestroyTexture(heartTxtr);
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
	wpng= IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/winStateBeta.png");
	wSrc = { 0,0,256,198 };
	//Mix_PlayMusic(Titletheme, -1);
	//Mix_VolumeMusic(24); //0-128
}

void WState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_RETURN))
	{

		cout << "changing to titlestate" << endl;
		STMA::ChangeState(new TitleState());
		return;
	}
}

void WState::Render()
{
      SDL_RenderClear(Engine::Instance().GetRenderer());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), wpng, NULL, NULL);
	//if (dynamic_cast<TitleState*>(STMA::GetStates().back()))//if current state is gamestate
		State::Render();
}

void WState::Exit()
{
	//cout << "exiting titlestate" << endl;
	//Mix_FreeMusic(Titletheme);
	SDL_DestroyTexture(wpng);
}


TabState::TabState(){}

void TabState::Enter()
{
	cout << "enter tabstate" << endl;
	// = Mix_LoadMUS("aud/.mp3");//gametheme
	tab = IMG_LoadTexture(Engine::Instance().GetRenderer(), "bgs/tabState.png");
	tabsrc = { 0,0,484,368 };
	tabdst = { 300,200,484,368 };
	//Mix_PlayMusic(Titletheme, -1);
	//Mix_VolumeMusic(24); //0-128
}

void TabState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_TAB))
		STMA::PopState();
}

void TabState::Render()
{
	STMA::GetStates().front()->Render();
	//now render the rest of pausestate
	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(Engine::Instance().GetRenderer(), tab, &tabsrc,&tabdst);
	//if (dynamic_cast<TitleState*>(STMA::GetStates().back()))//if current state is gamestate
		State::Render();
}

void TabState::Exit()
{
	cout << "exiting tabstate" << endl;
	//Mix_FreeMusic(Titletheme);
	SDL_DestroyTexture(tab);
}

BossState::BossState(){}


void BossState::Enter()
{
	plrTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/catboy.png");
	rockTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/Rocko100.png");
	bossbg = IMG_LoadTexture(Engine::Instance().GetRenderer(), "bgs/boss.png");
	npcTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/wizzy.png");
	DragonFlyTxt = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/dragonfly1.png");
	vineTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/vines.png");
	FrogTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/frogWalking7.png");
	frogbubble = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/bubblegreen.png");
	tree = IMG_LoadTexture(Engine::Instance().GetRenderer(), "bgs/Trees.png");
	portaltxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/portal2.png");
	cloudtxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/cloud.png");
	bosstxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/TheBoss.png");
	plant1 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/plant1.png");
	plant2 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/plant2.png");
	plant3 = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/plant3.png");
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
	beepbeep = Mix_LoadWAV("sfx/beepbeep.wav");
	beeppew = Mix_LoadWAV("sfx/beeppew.mp3");
	//dashMeow = Mix_LoadWAV("sfx/dashMeow.wav");
	Mix_VolumeChunk(dashing, 25);
	Mix_VolumeChunk(aoeSound, 50);
	Mix_VolumeChunk(projectileRock, 50);
	//Mix_VolumeChunk(hehe, 20);
	maintheme = Mix_LoadMUS("Aud/Gametheme.mp3");

	//sounds
	Mix_PlayMusic(maintheme, -1);
	Mix_VolumeMusic(0); //0-128
	Mix_Volume(-1, 50);
	//Mix_Volume(2, 12);
	b.push_back(new Boss(bg1.bossbgDst.x+ 600, bg1.bossbgDst.y + 600,0));
	//b.push_back(new Boss(bg1.bossbgDst.x + 600, bg1.bossbgDst.y + 1000, 1));
	b.shrink_to_fit();
}

void BossState::Update()
{
	
	//freeze
	bg1.bossbgDst.x -= speedx;
	bg1.bossbgDst.y -= speedy;
	
	for (unsigned i = 0; i < b.size(); i++)
	{
		b[i]->Update();
		b[i]->BossDst.x -= speedx;
		b[i]->BossDst.y -= speedy;
	}
	for (unsigned i = 0; i < fb.size(); i++)
	{
		fb[i]->Update();
		fb[i]->fBossDst.x -= speedx;
		fb[i]->fBossDst.y -= speedy;
	}

	for (unsigned i = 0; i < b.size(); i++)
	{
		if (b[i]->getState() == 1)
			{
			    b.clear();
				fb.push_back(new Bossf(bg1.bossbgDst.x + 300 ,bg1.bossbgDst.y + 900, 0));
				fb.push_back(new Bossf(bg1.bossbgDst.x + 900 ,bg1.bossbgDst.y + 900, 0));
				fb.push_back(new Bossf(bg1.bossbgDst.x + 600 ,bg1.bossbgDst.y + 1200, 0));
				fb.push_back(new Bossf(bg1.bossbgDst.x + 300, bg1.bossbgDst.y + 700, 0));
				fb.push_back(new Bossf(bg1.bossbgDst.x + 300, bg1.bossbgDst.y + 1200, 0));
				fb.push_back(new Bossf(bg1.bossbgDst.x + 900, bg1.bossbgDst.y + 700, 0));
				fb.push_back(new Bossf(bg1.bossbgDst.x + 900, bg1.bossbgDst.y + 1200, 0));
				fb.shrink_to_fit();
			
			}				
		
	}
	//cout << fb.size()<<endl;
	
	for (unsigned i = 0; i < playerpew.size(); i++)
	{
		for (unsigned j = 0; j < b.size(); j++)
		{
			if (b[j]->getState() == 2)
			{
				if (SDL_HasIntersection(&playerpew[i]->rockDst, &b[j]->BossDst)) //AABB Check
				{
					Mix_PlayChannel(-1, hurtSfx, 0);
					delete playerpew[i];
					playerpew[i] = nullptr;
					playerpew.erase(playerpew.begin() + i);
					playerpew.shrink_to_fit();
					delete b[j];
					b[j] = nullptr;
					b.erase(b.begin() + j);
					b.shrink_to_fit();
					break;
				}
			}
			
		}
	}
	for (unsigned i = 0; i < playerpew.size(); i++)
	{
		for (unsigned j = 0; j < fb.size(); j++)
		{
			//if (fb[j]->getState() == 2)
			{
				if (SDL_HasIntersection(&playerpew[i]->rockDst, &fb[j]->fBossDst)) //AABB Check
				{
					Mix_PlayChannel(-1, hurtSfx, 0);
					delete playerpew[i];
					playerpew[i] = nullptr;
					playerpew.erase(playerpew.begin() + i);
					playerpew.shrink_to_fit();
					delete fb[j];
					fb[j] = nullptr;
					fb.erase(fb.begin() + j);
					fb.shrink_to_fit();
					break;
				}
			}

		}
	}
	/*for (unsigned int i = 0; i < b.size(); i++)
	{
		if (b[i]->getHp() <= 0)
		{
			delete b[i];
			b[i] = nullptr;
			b.erase(b.begin() + i);
			b.shrink_to_fit();
		}
	}
	for (unsigned int i = 0; i < fb.size(); i++)
	{
		if (fb[i]->getHp() <= 0)
		{
			delete fb[i];
			fb[i] = nullptr;
			fb.erase(fb.begin() + i);
			fb.shrink_to_fit();
		}
	}*/
	
	if (freezeCD > 600)
	{
		if (EVMA::KeyPressed(SDL_SCANCODE_F))
		{
			isfreezeActive = true;
			freezetimer = 0;
			freezeCD = 0;
		}
	}
	freezetimer++;
	if (isfreezeActive)
	{
		if (freezetimer > 150)
		{
			isfreezeActive = false;
			freezetimer = 0;
			freezeCD = 0;
		}
	}
	if (!lvlLoading) {
		if (!(fadeMod == 0))
			fadeMod -= fadeSpeed;
		if (fadeMod == 0)
			fadeMod == 0;
		/*if (plr1.winbar >= 150)
		{
			STMA::ChangeState(new WState());
			return;
		}*/
		/*cout << exitRect.x << endl;
		cout << exitRect.y << endl;
		cout << bg[areaNum]->getBg() << endl;*/
		
		if (plr1.plrHp <= 0)
		{
			STMA::ChangeState(new EndState());
			return;
		}
		//cout <<"noobtimer"<< Noobtimer++ <<" | "<<ezModeCD++ << "ezmodecd<-" << endl;
		//cout << "freezetimer" << freezetimer++ << " | " << freezeCD++ << "freezecd<-" << endl;
		//cout << plr1.plrDst.x - bg1.bossbgDst.x << " - " << plr1.plrDst.y - bg1.bossbgDst.y << endl; // for spawning things on bg
		// cout << plr1.plrDst.x << " , " << plr1.plrDst.y  << endl;
		//cout <<bg1.bossbgDst.x << "||" <<bg1.bossbgDst.y << endl; // for spawning player on bg

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

		//shroom
		for (unsigned i = 0; i < shroom.size(); i++)
		{
			shroom[i]->shroomDst.x -= speedx;
			shroom[i]->shroomDst.y -= speedy;
			if (isfreezeActive == false)
				shroom[i]->Update();
			if (Util::distanceOffset(plr1.plrDst, shroom[i]->shroomDst) < 550) {
				if (shroom[i]->shootTimer == 0) {
					cloud.push_back(new Cloud(shroom[i]->shroomDst.x + 45, shroom[i]->shroomDst.y + 30, 5, 'y'));
					cloud.push_back(new Cloud(shroom[i]->shroomDst.x + 45, shroom[i]->shroomDst.y + 30, 5 * -1, 'y'));
					cloud.push_back(new Cloud(shroom[i]->shroomDst.x + 45, shroom[i]->shroomDst.y + 30, 5, 'x'));
					cloud.push_back(new Cloud(shroom[i]->shroomDst.x + 45, shroom[i]->shroomDst.y + 30, 5 * -1, 'x'));
					cloud.shrink_to_fit();
				}
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
		// shroom cloud
		for (unsigned i = 0; i < cloud.size(); i++)
		{
			cloud[i]->cloudDst.x -= speedx;
			cloud[i]->cloudDst.y -= speedy;
			if (isfreezeActive == false)
				cloud[i]->Update();
			if (Util::distanceOffset(plr1.plrDst, cloud[i]->cloudDst) < 100) {
				plr1.takeDamage(0.5);
				delete cloud[i];
				cloud[i] = nullptr;
				cloud.erase(cloud.begin() + i);
				cloud.shrink_to_fit();
			}
		}
		

		for (unsigned i = 0; i < portal.size();i++)
		{
			portal[i]->portalDst.x -= speedx;
			portal[i]->portalDst.y -= speedy;
		}

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
		if (EVMA::KeyPressed(SDL_SCANCODE_TAB))
		{
			cout << "Changing to tabState" << endl;
			//pause the music track
			STMA::PushState(new TabState());
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

			if (Util::distanceOffset(plr1.plrDst, playerpew[i]->rockDst) > 600)
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
					if (isfreezeActive == false)
						shroom[j]->setHp(shroom[j]->getHp() - playerDamage);
					break;
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

void BossState::Render()
{
	SDL_RenderClear(Engine::Instance().GetRenderer());
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 100, 11, 169, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	// Any drawing here...
	//SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
	//SDL_RenderFillRect(m_pRenderer, &plr1.plrDst);
	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);

	//Background
		SDL_RenderCopy(Engine::Instance().GetRenderer(), bossbg, &bg1.bossbgSrc, &bg1.bossbgDst);
	for (unsigned i = 0; i < portal.size();i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), portaltxtr, &portal[i]->portalSrc, &portal[i]->portalDst);
	}
	
	//for boss
	for (unsigned i = 0; i < b.size();i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), bosstxtr, &b[i]->BossSrc, &b[i]->BossDst);
		//health bar	
		/*SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
		if (isfreezeActive == false)
			SDL_RenderFillRect(Engine::Instance().GetRenderer(), &b[i]->HP);
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
		if (isfreezeActive == false)
			SDL_RenderFillRect(Engine::Instance().GetRenderer(), &b[i]->healthBar);*/
	}


	//fake boss
	for (unsigned i = 0; i < fb.size();i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), bosstxtr, &fb[i]->fBossSrc, &fb[i]->fBossDst);
		//health bar				
		//SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
		/*if (isfreezeActive == false)
			SDL_RenderFillRect(Engine::Instance().GetRenderer(), &fb[i]->HP);
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
		if (isfreezeActive == false)
			SDL_RenderFillRect(Engine::Instance().GetRenderer(), &fb[i]->healthBar);*/
	}


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


	//shroom
	for (unsigned i = 0; i < shroom.size(); i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), ShroomTxtr, &shroom[i]->shroomSrc, &shroom[i]->shroomDst);
		//health bar				
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 255, 255);
		if (isfreezeActive == false)
			SDL_RenderFillRect(Engine::Instance().GetRenderer(), &shroom[i]->HP);
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
		if (isfreezeActive == false)
			SDL_RenderFillRect(Engine::Instance().GetRenderer(), &shroom[i]->healthBar);
	}
	for (unsigned i = 0; i < cloud.size(); i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), cloudtxtr,
			&(cloud[i]->cloudSrc), &(cloud[i]->cloudDst));
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
	//SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 255, 255);
	//SDL_RenderFillRect(Engine::Instance().GetRenderer(), &plr1.plrwinbar);
	if (freezeCD > 600)
		SDL_RenderCopy(Engine::Instance().GetRenderer(), freezeui, &freezeSrc, &freezeDst);

	if (spcooldown > 200)
		SDL_RenderCopy(Engine::Instance().GetRenderer(), aoe, &aoeSrc, &aoeDst);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &plr1.hpborder);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &plr1.plrHpBar);


	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, fadeMod);
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &blackRect);

	if (dynamic_cast<BossState*>(STMA::GetStates().back()))//if current state is gamestate	
		State::Render();

}

void BossState::Exit()
{
	SDL_DestroyTexture(plrTxtr);
	SDL_DestroyTexture(rockTxtr);
	SDL_DestroyTexture(ShroomTxtr);
	SDL_DestroyTexture(DragonFlyTxt);
	SDL_DestroyTexture(vineTexture);
	SDL_DestroyTexture(FrogTxtr);
	SDL_DestroyTexture(cloudtxtr);
	SDL_DestroyTexture(portaltxtr);
	SDL_DestroyTexture(bosstxtr);
	SDL_DestroyTexture(plant1);
	SDL_DestroyTexture(plant2);
	SDL_DestroyTexture(plant3);
	Mix_FreeChunk(hurtSfx);
	Mix_FreeChunk(powerSfx);;
	Mix_FreeChunk(projectileRock);
	Mix_FreeChunk(aoeSound);
	Mix_FreeChunk(dashing);
	Mix_FreeChunk(stepSfx);
	Mix_FreeChunk(deathSfx);
	Mix_FreeChunk(turnSfx);
	shroom.clear();
	shroom.shrink_to_fit();
	fly.clear();
	fly.shrink_to_fit();
	frog.clear();
	frog.shrink_to_fit();
	playerpew.clear();
	playerpew.shrink_to_fit();
	b.clear();
	b.shrink_to_fit();
	fb.clear();
	fb.shrink_to_fit();
}

void BossState::Resume()
{
}
