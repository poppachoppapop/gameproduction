#pragma once
#include <SDL.h>
#include <cmath>

class Util
{
private:
	int change;
public:
	static double distance(SDL_Rect a, SDL_Rect b);
	static double distanceOffset(SDL_Rect a, SDL_Rect b);
	static int fadeToBlack();
};


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
