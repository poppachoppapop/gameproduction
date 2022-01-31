#include "States.h"
#include "StateManager.h"
#include "Engine.h"
#include <iostream>
using namespace std;


void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

TitleState::TitleState() {}

void TitleState::Enter()
{
	cout << "Entering Title State..." << endl;
	// Load music track, add it to map and play it.
}

void TitleState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_N))
	{
		cout << "Changing to GameState!" << endl;
		STMA::ChangeState(new GameState());
	}
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 255, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	State::Render();
}

void TitleState::Exit()
{
	cout << "Exiting TitleState..." << endl;
	//Call Mix_FreeMusic on your music track.
}

PauseState::PauseState() {}

void PauseState::Enter()
{
	cout << "Entering PauseState..." << endl;
}

void PauseState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
	{
		STMA::PopState();
	}
}

void PauseState::Render()
{
	// first render the gamestate.
	STMA::GetStates().front()->Render();
	//Render the rest of pause state.
	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 128);
	SDL_Rect rect = { 255, 128, 512, 512 };
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rect);
	State::Render();
}

void PauseState::Exit()
{
	cout << "Exiting PauseState..." << endl;
}

GameState::GameState() {}

void GameState::Enter()
{
	cout << "Entering GameState..." << endl;
	// Load music sfx, add them to map.
	stepSfx = Mix_LoadWAV("sfx/step.wav");
	turnSfx = Mix_LoadWAV("sfx/turn.wav");
	deathSfx = Mix_LoadWAV("sfx/dedEnemy.wav");
	hurtSfx = Mix_LoadWAV("sfx/enemyHurt.wav");
	powerSfx = Mix_LoadWAV("sfx/powerUp.wav");
	m_sfx.emplace("steps", stepSfx);
	m_sfx.emplace("turn", turnSfx);
	m_sfx.emplace("death", deathSfx);
	m_sfx.emplace("hurt", hurtSfx);
	m_sfx.emplace("power", powerSfx);
	// Load music track, add it to map, and play it.
	maintheme = Mix_LoadMUS("Aud/TitleTheme.mp3");
	m_gamemusic.emplace("gamemusic", maintheme);
	Mix_PlayMusic(m_gamemusic["gamemusic"], -1);
	//Load in sprites and background
	plrTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/catboy.png");
	rockTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/Rocko100.png");
	dumbieTxtr = IMG_LoadTexture(Engine::Instance().GetRenderer(), "art/Dumbie.png");
	bgTutorial = IMG_LoadTexture(Engine::Instance().GetRenderer(), "bgs/tutorial.png");
}

void GameState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
	{
		cout << "Changing to PauseState!" << endl;
		// pause the music track.
		Mix_PauseMusic();
		STMA::PushState(new PauseState());
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_X))
	{
		cout << "Changing to EndState!" << endl;
		// pause the music track.
		Mix_PauseMusic();
		STMA::ChangeState(new EndState());
	}
	stepSoundTimer++; turnSoundTimer++;
	dashCooldown++;
	dumbieTimerMax -= 0.01;
	bg1.bgDst.x -= speedx;
	bg1.bgDst.y -= speedy;
	plr1.Update();
	rockCooldown++;
	spcooldown++;



	//For special Ability1
	if (Engine::Instance().KeyDown(SDL_SCANCODE_SPACE))
	{
		if (spcooldown > 200)
		{
			spcooldown = 0;
			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, 10, 'y'));
			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, 10 * -1, 'y'));
			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, 10, 'x'));
			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, 10 * -1, 'x'));
			playerpew.shrink_to_fit();
		}


	}

	//For throwing Rock
	if (Engine::Instance().KeyDown(SDL_SCANCODE_UP))
	{
		if (rockCooldown > 50) {
			rockCooldown = 0;
			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, rockSpeed * -1, 'y'));
			playerpew.shrink_to_fit();
		}
	}
	else if (Engine::Instance().KeyDown(SDL_SCANCODE_DOWN))
	{
		if (rockCooldown > 50) {
			rockCooldown = 0;
			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, rockSpeed, 'y'));
			playerpew.shrink_to_fit();
		}
	}
	else if (Engine::Instance().KeyDown(SDL_SCANCODE_LEFT))
	{
		if (rockCooldown > 50) {
			rockCooldown = 0;
			playerpew.push_back(new Rock(plr1.plrDst.x + 10, plr1.plrDst.y + 30, rockSpeed * -1, 'x'));
			playerpew.shrink_to_fit();
		}
	}
	else if (Engine::Instance().KeyDown(SDL_SCANCODE_RIGHT))
	{
		if (rockCooldown > 50) {
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
		if (Engine::Instance().KeyDown(SDL_SCANCODE_LSHIFT)) {
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

	if (Engine::Instance().KeyDown(SDL_SCANCODE_S)) {

		speedy += speedAcc;
		plr1.state = 1;

	}

	if (Engine::Instance().KeyDown(SDL_SCANCODE_W)) {

		speedy -= speedAcc;
		plr1.state = 2;
	}

	//XAXIS
	if (Engine::Instance().KeyDown(SDL_SCANCODE_A)) {
		speedx -= speedAcc;
		plr1.state = 3;
	}

	if (Engine::Instance().KeyDown(SDL_SCANCODE_D)) {
		speedx += speedAcc;
		plr1.state = 4;
	}

	//Slow Down!
	if (!Engine::Instance().KeyDown(SDL_SCANCODE_D) && !Engine::Instance().KeyDown(SDL_SCANCODE_A)) {
		if (speedx > 0)
			speedx--;
		else if (speedx < 0) {
			speedx++;
		}
	}
	if (!Engine::Instance().KeyDown(SDL_SCANCODE_W) && !Engine::Instance().KeyDown(SDL_SCANCODE_S)) {
		if (speedy > 0)
			speedy--;
		else if (speedy < 0) {
			speedy++;
		}
	}
	if (!Engine::Instance().KeyDown(SDL_SCANCODE_W) && !Engine::Instance().KeyDown(SDL_SCANCODE_S) && !Engine::Instance().KeyDown(SDL_SCANCODE_D) && !Engine::Instance().KeyDown(SDL_SCANCODE_A)) {
		plr1.state = 0;

	}

	//delete rock after off screen and move rock
	for (unsigned i = 0; i < playerpew.size(); i++)
	{
		playerpew[i]->Update();
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
	if (dumbietimer >= dumbieTimerMax)
	{
		dumbietimer = 0;
		dumbie.push_back(new Enemy(rand() % bg1.bgDst.x + 300, rand() % bg1.bgDst.y + 300, 3));
		dumbie.shrink_to_fit();
		cout << "spawning dumbie" << endl;
	}

	//hitbox stuff/Collision
	for (unsigned i = 0; i < playerpew.size(); i++)
	{
		for (unsigned j = 0; j < dumbie.size(); j++)
		{
			if (SDL_HasIntersection(&playerpew[i]->rockDst, &dumbie[j]->enemyDst)) //AABB Check
			{
				cout << "catboy hits dumbie" << endl;
				Mix_PlayChannel(-1, m_sfx["hurt"], 0);
				delete playerpew[i];
				playerpew[i] = nullptr;
				playerpew.erase(playerpew.begin() + i);
				playerpew.shrink_to_fit();
				//set dumbie hp
				dumbie[j]->setHp(dumbie[j]->getHp() - playerDamage);
				textBoxOpen = true;
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
			Mix_PlayChannel(-1, m_sfx["death"], 0);
			delete dumbie[i];
			dumbie[i] = nullptr;
			dumbie.erase(dumbie.begin() + i);
			dumbie.shrink_to_fit();
			surfaceMessage = TTF_RenderText_Solid(font, message, White);
			Message = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), surfaceMessage);
			strcpy_s(message, "MEANIE!");
		}
	}


	//for items
	itemSpawnTimer++;
	if (itemSpawnTimer > 1000) {
		itemSpawnTimer = 0;
		item1.push_back(new Items(1));
		item1.shrink_to_fit();
	}
	for (unsigned i = 0; i < item1.size(); i++)
	{
		item1[i]->item.x -= speedx;
		item1[i]->item.y -= speedy;

		if (SDL_HasIntersection(&plr1.plrDst, &item1[i]->item)) //AABB Check
		{
			Mix_PlayChannel(-1, m_sfx["power"], 0);
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
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 200, 200, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	// Any drawing here...
	//SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
	//SDL_RenderFillRect(m_pRenderer, &plr1.plrDst);

	//Background
	SDL_RenderCopy(Engine::Instance().GetRenderer(), bgTutorial, &bg1.bgSrcTutorial, &bg1.bgDst);

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
	for (unsigned i = 0; i < dumbie.size(); i++)
	{
		SDL_RenderCopyEx(Engine::Instance().GetRenderer(), dumbieTxtr, &dumbie[i]->enemySrc, &dumbie[i]->enemyDst, 00.0, NULL, SDL_FLIP_NONE);
		//dumbie hp
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 255);
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &dumbie[i]->healthBar);
	}

	//text box
	if (textBoxOpen) {
		SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
		SDL_RenderFillRect(Engine::Instance().GetRenderer(), &textBoxBorder);
		SDL_RenderCopy(Engine::Instance().GetRenderer(), Message, NULL, &textBoxRect);
	}

	SDL_RenderPresent(Engine::Instance().GetRenderer()); // Flip buffers - send data to window.

}

void GameState::Exit()
{
	cout << "Exiting GameState..." << endl;
}

void GameState::Resume()
{
	cout << "Resuming GameState..." << endl;
	// Resume music track.
}

EndState::EndState() {}

void EndState::Enter()
{
	cout << "Entering EndState..." << endl;
}

void EndState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
	{
		cout << "Changing to TitleState!" << endl;
		STMA::ChangeState(new TitleState());
	}
}

void EndState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	State::Render();
}

void EndState::Exit()
{
	cout << "Exiting EndState..." << endl;
}
