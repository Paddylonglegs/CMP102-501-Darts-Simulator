/*
Author: Patrick Collins
©️license MIT
https://github.com/Paddylonglegs/
*/

#pragma once
class score
{
	private:

	int Pscore = 501; //Player score
	int miniScore = 0; //Mini game score
	int below0 = 0; //Used to add score back to the player if their 3 darts get below 0

	public:

	//functions

	int getScore(); //Returning player score

	int getminiScore(); //Returning player mini game score

	void addScore(int a); //Function used to add score back to player

	void reduceScore(int n); //Function used to reduce score of the player

	void addminiScore(int m); //Function used to add mini game score

	void changeBelow(int b); //Used to reset the below0 variable back to zero(Player did not go under 0 in their 3 dart throws)

	int getBelow(); //Returning the player's below value that will be added to player score

};

