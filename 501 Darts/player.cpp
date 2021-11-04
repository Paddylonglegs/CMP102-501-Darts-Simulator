/*
Author: Patrick Collins
©️license MIT
https://github.com/Paddylonglegs/
*/

#include "player.h"

int player::getWon()
{
	return won;
}

int player::getPerc()
{
	return percentage;
}

int player::throw_bull(int percentage)
{
	//  Throw for the bull with percent accuracy (20<p<85)
	int random = rand() % 100;

	if (random < (percentage - 20))
	{
		return 50;
	}
	else if (random < 85)
	{
		return 25;
	}
	else
	{
		return 1 + rand() % 20;
	}

}

int player::throw_single(int d, int p)
{
	// return result of throwing for single d with accuracy p of the player success rate
	//d is the score that the player is aiming for

	int r = rand() % 100;

	     // 1 to 20 single
		if (r < p)
		{
			return d; //return aimed taregt score
		} 
		else if (r < 92)
		{
			return dart.board[0][d]; //return score to the left
		} 
		else if (r < 96)
		{
			return dart.board[1][d]; //return score to the right
		} 
}

int player::throw_double(int d, int p)
{
	//  return result of throwing for double d with accuracy of player success rate


	int r = rand() % 100;

	if (r < p)
	{
		return 2 * d; //return aimed target score multiplied by 2
	} //double hit
	else if (r < 93)
	{
		return 2 * dart.board[0][d]; //double of left hand score hit
	}
	else if (r < 96)
	{
		return 2 * dart.board[1][d]; //double of right hand score hit
	}
}

int player::throw_treble(int d, int p)
{
	//  return result of throwing for treble d with accuracy p%  (o<90)

	int r = rand() % 100;

	if (r < p)
	{
		return 3 * d; //return aimed target score multiplied by 3
	} //treble hit
	else if (r < 93)
	{
		return 3 * dart.board[0][d]; //treble of left hand score hit
	} 
	else if (r < 96)
	{
		return 3 * dart.board[1][d]; //treble of right hand score hit
	}
}

