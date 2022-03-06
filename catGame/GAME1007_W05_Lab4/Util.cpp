#include "Util.h"
#include <iostream>

using namespace std;

double Util::distance(SDL_Rect a, SDL_Rect b)
{
    float x = a.x - b.x;
    float y = a.y - b.y;
    float distance;
    distance = pow(x, 2) + pow(y, 2);
    distance = sqrt(distance);
    
    return distance;
}

double Util::distanceOffset(SDL_Rect a, SDL_Rect b) // b is enemy
{
    float x = ((a.x + a.w/2) - (b.x + b.w/2));
    float y = ((a.y + a.h - 15) - (b.y + b.h/2));
    float distance;
    distance = pow(x, 2) + pow(y, 2);
    distance = sqrt(distance);
    
    return distance;
}




