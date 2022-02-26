#include "States.h"
#include "StateManager.h"
#include "Engine.h"
#include "EventManager.h"
#include "Items.h"
#include "Background.h"
#include "NPC.h"
#include <iostream>
#include "enemy.h"

using namespace std;


void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

TitleState::TitleState(){}


void TitleState::Enter()
{	
		cout << "enter titlestate" << endl;	
		Titletheme = Mix_LoadMUS("aud/Titletheme.mp3");//gametheme
		Title = IMG_LoadTexture(Engine::Instance().GetRenderer(), "bgs/Title.png");
		//bgSrc = { 0,0,1024,768 };
		Mix_PlayMusic(Titletheme, -1);
		Mix_VolumeMusic(24); //0-128
}

void TitleState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_N))
	{

		cout << "changing to gamestate" << endl;
		STMA::ChangeState(new GameState());
		return;
	}
}

void TitleState::Render()
{
	SDL_RenderClear(Engine::Instance().GetRenderer());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), Title,NULL,NULL);	
	if (dynamic_cast<TitleState*>(STMA::GetStates().back()))//if current state is gamestate
	State::Render();
}

void TitleState::Exit()
{
	cout << "exiting titlestate" << endl;
	Mix_FreeMusic(Titletheme);
	SDL_DestroyTexture(Title);
}



PauseState::PauseState(){}



void PauseState::Enter()
{
	
	cout << "entering pausestate" << endl;
	
}

void PauseState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_R))
		STMA::PopState();
}

void PauseState::Render()
{
	//1st render the gamestate
	STMA::GetStates().front()->Render();
	//now render the rest of pausestate
	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 128);
	SDL_Rect rect = { 255,128,512,512 };
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rect);
	State::Render();
}

void PauseState::Exit()
{
	cout << "exiting pausestate" << endl;
	
}



GameState::GameState() {}

void GameState::Enter()
{
	cout << "entering gamestate" << endl;
	plrTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/catboy.png");
	DragonFlyTxt = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/dragonfly.png");
	rockTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/Rocko100.png");
	dumbieTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/Dumbie.png");
	bgTutorial = IMG_LoadTexture(Engine::Instance().GetRenderer(), "bgs/tutorial.png");
	npcTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/catDude.png");

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

	surfaceMessage = TTF_RenderText_Solid(font, message, White);
	dummyScore = TTF_RenderText_Solid(font, scoreMessage, White);

	Message = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), surfaceMessage);
	Score = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), dummyScore);
}

void GameState::Update()
{
	//debug
	//cout << plr1.plrDst.x - bg1.bgDst.x << " - " << plr1.plrDst.y - bg1.bgDst.y << endl;
	if (EVMA::KeyPressed(SDL_SCANCODE_P))
	{
		cout << "Changing to PauseState" << endl;
		//pause the music track
		STMA::PushState(new PauseState());
		Mix_PauseMusic();
	}
	
	if (EVMA::KeyPressed(SDL_SCANCODE_H))
	{

	    cout << "changing to gamestate" << endl;
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
	bg1.bgDst.x -= speedx;
	bg1.bgDst.y -= speedy;
	plr1.Update();
	catDude.Update();
	df.Update();
	rockCooldown++;
	spcooldown++;
	//NPC
	catDude.npcDst.x = bg1.bgDst.x + 1000;
	catDude.npcDst.y = bg1.bgDst.y + 1350;

	if (plr1.plrDst.x < bg1.bgDst.x - 50)
		bg1.bgDst.x = plr1.plrDst.x + 50;
	if (plr1.plrDst.y < bg1.bgDst.y + 630)
		bg1.bgDst.y = plr1.plrDst.y - 630;

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
	if (EVMA::KeyPressed(SDL_SCANCODE_UP))
	{
		if (rockCooldown > 50) {
			Mix_PlayChannel(-1, projectileRock, 0);
			rockCooldown = 0;
			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, rockSpeed * -1, 'y'));
			playerpew.shrink_to_fit();
		}
	}
	else if (EVMA::KeyPressed(SDL_SCANCODE_DOWN))
	{

		if (rockCooldown > 50) {
			Mix_PlayChannel(-1, projectileRock, 0);
			rockCooldown = 0;
			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, rockSpeed, 'y'));
			playerpew.shrink_to_fit();
		}
	}
	else if (EVMA::KeyPressed(SDL_SCANCODE_LEFT))
	{

		if (rockCooldown > 50) {
			Mix_PlayChannel(-1, projectileRock, 0);
			rockCooldown = 0;
			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, rockSpeed * -1, 'x'));
			playerpew.shrink_to_fit();
		}
	}
	else if (EVMA::KeyPressed(SDL_SCANCODE_RIGHT))
	{

		if (rockCooldown > 50) {
			Mix_PlayChannel(-1, projectileRock, 0);
			rockCooldown = 0;
			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, rockSpeed, 'x'));
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

	//hitbox stuff/Collision
	for (unsigned i = 0; i < playerpew.size(); i++)
	{
		for (unsigned j = 0; j < dumbie.size(); j++)
		{
			if (SDL_HasIntersection(&playerpew[i]->rockDst, &dumbie[j]->enemyDst)) //AABB Check
			{
				cout << "catboy hits dumbie" << endl;
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
	//delete dumbie when at 0 hp
	for (unsigned i = 0; i < dumbie.size(); i++)
	{
		//updates healthbar
		dumbie[i]->update();
		dumbie[i]->enemyDst.x -= speedx;
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
		item1[i]->item.x -= speedx;
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

void GameState::Render()
{
	
	SDL_RenderClear(Engine::Instance().GetRenderer());
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 200, 200, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	// Any drawing here...
	//SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
	//SDL_RenderFillRect(m_pRenderer, &plr1.plrDst);

	//Background
	SDL_RenderCopy(Engine::Instance().GetRenderer(),bgTutorial, &bg1.bgSrcTutorial, &bg1.bgDst);

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
	SDL_RenderCopy(Engine::Instance().GetRenderer(), DragonFlyTxt, &df.dfAni, &df.dfDst);

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

EndState::EndState(){}

void EndState::Enter()
{
	cout << "entering endstate" << endl;
}

void EndState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
	{

		cout << "changing to gamestate" << endl;
		STMA::ChangeState(new TitleState());
		return;
	}

}

void EndState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 69, 100, 200, 230);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	State::Render();

}

void EndState::Exit()
{
	cout << "exitinggamestate" << endl;
}
