/*
Author: Patrick Collins
©️license MIT
https://github.com/Paddylonglegs/
*/

#include "score.h"
#include "player.h"
using namespace std;

int score::getScore()
{
	return Pscore;
}

int score::getminiScore()
{
	return miniScore;
}
void score::addScore(int a)
{
	Pscore = Pscore + a;
}

void score::reduceScore(int n)
{
	Pscore = Pscore - n; //Reducing the player's score
	below0 = below0 + n; //Also adding this reduction incase the player score goes below zero
}

void score::addminiScore(int m)
{
	miniScore = miniScore + m;
}

void score::changeBelow(int b)
{
	below0 = b;
}

int score::getBelow()
{
	return below0;
}
