/*
Author: Patrick Collins
©️license MIT
https://github.com/Paddylonglegs/
*/

#pragma once
#include <ctime>
#include <iostream>
#include "dartboard.h" //to use dartboard
class player
{

public:
	//attributes
	int percentage = 0; //How well player hits the target
	int bulls_hit = 0; //How many bulls the player hits
	int outerbulls_hit = 0; //How many outer bulls the player hits
	int dartsThrown = 0; //How many darts the player has thrown in a round
	int Totaldarts = 0; //How many darts the player has thrown in all matches
	int numGames = 0; //How many games the two players want to plays
	int won = 0; // How many wins the player has in a set
	int Totalwins = 0; //How many wins the player has in all matches
	int miniWon = 0; //Who won the mini game

	//functions
	
	dartboard dart; //used for player functions returning a value on the dartboard

	int getWon(); //Returning player wins in a set

	int getPerc(); //Returing player success rate

	int throw_bull(int percentage); //Player throwing for a bullseye function

	int throw_single(int d, int p); //Player throwing for a single function

	int throw_double(int d, int p); //Player throwing for a double function

	int throw_treble(int d, int p); //Player throwing for a treble function


};

