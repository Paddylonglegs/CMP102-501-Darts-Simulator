/*
Author: Patrick Collins
©️license MIT
https://github.com/Paddylonglegs/
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "player.h"
#include "score.h"
#include "dartboard.h"
using namespace std;

//Globals
int Jset = 0; //Player one's set counter
int Sset = 0; //Player two's set counter
int Smatch = 0; //John's number of matches won
int Jmatch = 0; //Sid's number of matches won
int numGames = 0; //Variable to store user inputted number of games
bool Game = true; //To stop Game while loop
bool minGame = true; //To stop mini Game while loop
string player1 = "John"; //Player one's name
string player2 = "Sid"; //Player two's name
int e = 0;
//Outcomes
double jOutcome1 = 0; //Set outcomes for John
double jOutcome2 = 0; //Set outcomes for John
double jOutcome3 = 0; //Set outcomes for John
double jOutcome4 = 0; //Set outcomes for John
double jOutcome5 = 0; //Set outcomes for John
double jOutcome6 = 0; //Set outcomes for John
double jOutcome7 = 0; //Set outcomes for John

double sOutcome1 = 0; //Set outcomes for Sid
double sOutcome2 = 0; //Set outcomes for Sid
double sOutcome3 = 0; //Set outcomes for Sid
double sOutcome4 = 0; //Set outcomes for Sid
double sOutcome5 = 0; //Set outcomes for Sid
double sOutcome6 = 0; //Set outcomes for Sid
double sOutcome7 = 0; //Set outcomes for Sid

//Initialising Classes
player John; //Player one's score
player Sid; //Player two's score
score JS; //John's Score
score SS; //Sid's Score

//Functions

void miniGame() //mini game to see who starts first game of 501 darts (throwing nearest the bullseye)
{
	while (minGame == true) //incase the two players score is the same, this makes the mini game continue until a winner is found
	{
		cout << "Mini game beginning..." << endl;

		JS.addminiScore(John.throw_bull(John.percentage)); //John aims for the bullseye, the score is then saved
		cout << "John aimed for a bullseye" << endl;
		SS.addminiScore(Sid.throw_bull(Sid.percentage)); //Sid aims for the bullseye, the score is then saved.
		cout << "Sid aimed for a bullseye" << endl;

		if (JS.getminiScore() > SS.getminiScore()) //Checking to see if John hit closest to the bullseye
		{
			cout << "John has hit closest to the bullseye" << endl;
			John.miniWon++; //Incrementing the win for John
			minGame = false; //Stopping the mini game
			cout << "John won the mini game and will start first" << endl;
			break; //extra measurement to break out of loop
		}
		else if(SS.getminiScore() > JS.getminiScore()) //Checking to see if Sid hit closest to the bullseye 
		{
			cout << "Sid has hit closest to the bullseye" << endl;
			Sid.miniWon++; //Incrementing the win for Sid
			minGame = false; //Stopping the mini game
			cout << "Sid won the mini game and will start first" << endl;
			break; //extra measurement to break out of loop
		}
	}
}


int main()
{					
	srand(time(0));	//initialise random number generator using time

	cout << "501 Darts Simulator" << endl;
	cout << "Enter John's success rate: ";
	cin >> John.percentage; //Storing John's success rate
	cout << "Enter Sid's success rate: ";
	cin >> Sid.percentage; //Storing Sid's success rate
	cout << "How many games would you like to simulate?: ";
	cin >> numGames; //Storing number of simulations

	miniGame(); //mini game to see who starts first game of 501 darts
	cout << "Beginning 501 Darts..." << endl;

	for (int t = 0; t <=numGames; t++) //For loop that will do the amount of simulations requested by player
	{
		Jset = 0; //Resetting player one's Set count from previous game
		Sset = 0; //Resetting player two's Set count from previous game

		for (int m = 0; m <= 13; m++) //Playing one match (13 sets)
		{

			if (Jset == 7) //checking has player one won the set
			{
				Jmatch++; //John won a match, adds one
				Game = false; //To stop Game while loop
				break; //Extra measurement to break out of loop
			}
			else if (Sset == 7) //checking has player two won the set
			{
				Smatch++; //Sid won a match, adds one
				Game = false; //To stop Game while loop
				break; //Extra measurement to break out of loop
			}

			Game = true; //To restart the Game while loop 
			John.won = 0; //Resetting player one's win count
			Sid.won = 0; //Resetting player two's win count
			
			for (int set = 0; set < 5; set++)
			{

				score JS; //setting | resetting John's score
				score SS; //setting | resetting Sid's score
				Game = true; //To restart Game while loop


				while (Game == true) //Game loop
				{

						if (John.miniWon == 1) //////////////////////////////////JOHN WINS THE MINIGAME, JOHN STARTS FIRST/////////////////////////////////////
						{
							John.dartsThrown = 0; //Resetting player one's dart count(used as boundary in Game loop)
							Sid.dartsThrown = 0; //Resetting player two's dart count(used as boundary in Game loop)
							JS.changeBelow(0); //This is to reset John's 3 thrown darts score
							SS.changeBelow(0); //This is to reset Sid's 3 thrown darts score

								for (int d = 0; d < 3; d++) //John throws 3 darts
								{
									////////Scoring section of the game loop////

									if (JS.getScore() >= 70 && John.dartsThrown <= 3) //Players simply aiming for treble 20 to get below or equal to 70 and hasn't thrown three darts already.
									{
										JS.reduceScore(John.throw_treble(20, John.percentage)); //Score is recuded by number that's returned from throwing dart at treble 20 area.
										John.dartsThrown++; //Incrementing the thrown darts boundary
										John.Totaldarts++; //Incrementing the Total darts player one has thrown. 
										//cout << player1 << " threw for a treble 20! " << player1 << "'s score: " << JS.getScore() << endl;
									}

									/////////Focus section of Game loop////////////

									if (JS.getScore() <= 70 && JS.getScore() >= 41 && John.dartsThrown <= 3) // If player score is in range of 41-70 and hasn't thrown three darts already.
									{
										if (JS.getScore() % 2 == 0) //checking is the number even
										{
											//number is even
											int Jeven = JS.getScore() % 10; //Getting right most number of player one's score
											//cout << "Jeven is: " << Jeven << endl;

											if (Jeven == 8)
											{
												JS.reduceScore(John.throw_single(8, John.percentage)); //Player aims for 8 on the dartboard, can miss and return 11 or 16
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " hit 8 " << player1 << "'s score: "  << JS.getScore() << endl;
											}
											else if (Jeven == 6)
											{
												JS.reduceScore(John.throw_single(6, John.percentage)); //Player aims for 6 on the dartboard, can miss and return 13 or 10
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " hit 6 " << player1 << "'s score: " << JS.getScore() << endl;

											}
											else if (Jeven == 4)
											{
												JS.reduceScore(John.throw_single(4, John.percentage)); //Player aims for 4 on the dartboard, can miss and return 18 or 13
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " hit 4 " << player1 << "'s score: " << JS.getScore() << endl;
											}
											else if (Jeven == 2)
											{
												JS.reduceScore(John.throw_single(2, John.percentage)); //Player aims for 2 on the dartboard, can miss and return 17 or 15
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " hit 2 " << player1 << "'s score: " << JS.getScore() << endl;
											}
										}
										else
										{
											//number is odd
											int j_Odd = JS.getScore() % 10;

											if (j_Odd == 9)
											{
												JS.reduceScore(John.throw_single(9, John.percentage)); //Player aims for 9 on the dartboard, can miss and return 14 or 12
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " hit 9 " << player1 << "'s score: " << JS.getScore() << endl;
											}
											else if (j_Odd == 7)
											{
												JS.reduceScore(John.throw_single(7, John.percentage)); //Player aims for 7 on the dartboard, can miss and return 16 or 19
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " hit 7 " << player1 << "'s score: " << JS.getScore() << endl;
											}
											else if (j_Odd == 5)
											{
												JS.reduceScore(John.throw_single(5, John.percentage)); //Player aims for 5 on the dartboard, can miss and return 12 or 20
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " hit 5 " << player1 << "'s score: " << JS.getScore() << endl;
											}
											else if (j_Odd == 3)
											{
												JS.reduceScore(John.throw_single(3, John.percentage)); //Player aims for 3 on the dartboard, can miss and return 19 or 17
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " hit 3 " << player1 << " score: " << JS.getScore() << endl;
											}
											else if (j_Odd == 1)
											{
												JS.reduceScore(John.throw_single(1, John.percentage)); //Player aims for 1 on the dartboard, can miss and return 11 or 16
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " hit 1 " << player1 << "'s score: " << JS.getScore() << endl;
											}
										}
									}

									if (JS.getScore() == 60 && John.dartsThrown <= 3) //player aims for single 20 just to get score below to double area
									{
										JS.reduceScore(John.throw_single(20, John.percentage));
										John.dartsThrown++;
										John.Totaldarts++;
										//cout << player1 << " aimed for 20 " << player1 << "'s score: " << JS.getScore() << endl;
									}

									////////Winning the game(Checkout section)/////

									if (JS.getScore() == 50 && John.dartsThrown <= 3) //Winning the game(Hitting bullseye)
									{
										JS.reduceScore(John.throw_bull(John.percentage));
										John.dartsThrown++;
										John.Totaldarts++;
										//cout << player1 << " aimed for a bullseye! " << player1 << "'s score: " << JS.getScore() << endl;

										if (JS.getScore() == 0)
										{
											John.bulls_hit++; //Incrementing player one's number of bulls hit
											John.won++; //Incrementing player one's wins for current set
											if (John.getWon() == 3 && Jset != 7 && Sset != 7)
											{
												Jset++; //John won the set, adding one to John's set wins
											}
											John.Totalwins++; //Incrementing player one's wins for number of sets
											//cout << player1 << " won!" << endl;
											Game = false;
											break;
										}
										else
										{
											John.outerbulls_hit++; //Incrementing number of outer bulls hit for number of games
										}

									}

									if (JS.getScore() <= 40 && John.dartsThrown <= 3) //Winning the game(hitting doubles)
									{
										int firstDigit = JS.getScore() / 10; // get first digit of the player score
										int secondDigit = JS.getScore() % 10; //get right most number(used for even)
										int j_Odd = JS.getScore() % 10; //get right most number(used for odd)
										//cout << "First digit is: " << firstDigit << endl;
										//cout << "Second digit is: " << secondDigit << endl;


										if (firstDigit == 4) //If player score is in the 40 range
										{
											if (secondDigit == 0) //If player score is 40
											{
												JS.reduceScore(John.throw_double(20, John.percentage)); //Aim for double 20(40)
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " aimed for double 20 " << player1 << "'s score: " << JS.getScore() << endl;
											}
										}
										else if (firstDigit == 3) //If player score is in the 30 range
										{
											if (secondDigit == 8) //If the player score is 38
											{
												JS.reduceScore(John.throw_double(19, John.percentage)); //aim for double 19(38)
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " aimed for double 19 " << player1 << "'s score: " << JS.getScore() << endl;

											}
											else if (secondDigit == 6)//If player score is 36
											{
												JS.reduceScore(John.throw_double(18, John.percentage)); //Aim for double 18(36)
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " aimed for double 18 " << player1 << "'s score: " << JS.getScore() << endl;
											}
											else if (secondDigit == 4) //If player score is 34
											{
												JS.reduceScore(John.throw_double(17, John.percentage)); //Aim for double 17(34)
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " aimed for double 17 " << player1 << "'s score: " << JS.getScore() << endl;
											}
											else if (secondDigit == 2) //If player score is 32
											{
												JS.reduceScore(John.throw_double(16, John.percentage)); //Aim for double 16(32)
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " aimed for double 16 " << player1 << "'s score: " << JS.getScore() << endl;
											}
											else if (secondDigit == 0) //If player score is 30
											{
												JS.reduceScore(John.throw_double(15, John.percentage)); //Aim for double 15(30)
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " aimed for double 15 " << player1 << "'s score: " << JS.getScore() << endl;
											}
										}
										else if (firstDigit == 2) //If player score is in 20 range
										{
											if (secondDigit == 8) //If player score is 28
											{
												JS.reduceScore(John.throw_double(14, John.percentage)); //Aim for double 14(28)
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " aimed for double 14 " << player1 << "'s score: " << JS.getScore() << endl;

											}
											else if (secondDigit == 6) //If player score is 26
											{
												JS.reduceScore(John.throw_double(13, John.percentage)); //Aim for double 13(26)
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " aimed for double 13 " << player1 << "'s score: " << JS.getScore() << endl;
											}
											else if (secondDigit == 4) //If player score is 24
											{
												JS.reduceScore(John.throw_double(12, John.percentage)); //Aim for double 12(24)
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " aimed for double 12 " << player1 << "'s score: " << JS.getScore() << endl;
											}
											else if (secondDigit == 2) //If player score is 22
											{
												JS.reduceScore(John.throw_double(11, John.percentage)); //Aim for double 11(22)
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " aimed for double 11 " << player1 << "'s score: " << JS.getScore() << endl;
											}
											else if (secondDigit == 0) //If player score is 20
											{
												JS.reduceScore(John.throw_double(10, John.percentage)); //Aim for double 10(20)
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " aimed for double 10 " << player1 << "'s score: " << JS.getScore() << endl;
											}
										}
										else if (firstDigit == 1) //If player score is in 10 range
										{
											if (secondDigit == 8) //If player score is 18
											{
												JS.reduceScore(John.throw_double(9, John.percentage)); //Aim for double 9(18)
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " aimed for double 9 " << player1 << "'s score: " << JS.getScore() << endl;

											}
											else if (secondDigit == 6) //If player score is 16
											{
												JS.reduceScore(John.throw_double(8, John.percentage)); //Aim for double 8(16)
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " aimed for double 8 " << player1 << "'s score: " << JS.getScore() << endl;
											}
											else if (secondDigit == 4) //If player score is 14
											{
												JS.reduceScore(John.throw_double(7, John.percentage)); //Aim for double 7(14)
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " aimed for double 7 " << player1 << "'s score: " << JS.getScore() << endl;
											}
											else if (secondDigit == 2) //If player score is 12
											{
												JS.reduceScore(John.throw_double(6, John.percentage)); //Aim for double 6(12)
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " aimed for double 6 " << player1 << "'s score: " << JS.getScore() << endl;
											}
											else if (secondDigit == 0) //If player score is 10
											{
												JS.reduceScore(John.throw_double(5, John.percentage)); //Aim for double 5(10)
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " aimed for double 5 " << player1 << "'s score: " << JS.getScore() << endl;
											}
										}
										else if (firstDigit == 0) //If player score is in range 0-9 (This is because 8 divided by 10 will give 0.8)
										{
											if (secondDigit == 8) //if player score is (8)
											{
												JS.reduceScore(John.throw_double(4, John.percentage)); //Aim for double 4(8)
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " aimed for double 4 " << player1 << "'s score: " << JS.getScore() << endl;
											}
											else if (secondDigit == 6) //If player score is 6
											{
												JS.reduceScore(John.throw_double(3, John.percentage)); //Aim for double 3(6)
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " aimed for double 3 " << player1 << "'s score: " << JS.getScore() << endl;
											}
											else if (secondDigit == 4) //If player score is 4 
											{
												JS.reduceScore(John.throw_double(2, John.percentage)); //Aim for double 2(4)
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " aimed for double 2 " << player1 << "'s score: " << JS.getScore() << endl;
											}
											else if (secondDigit == 2) //if player score is 2
											{
												JS.reduceScore(John.throw_double(1, John.percentage)); //Aim for double 1(2)
												John.dartsThrown++;
												John.Totaldarts++;
												//cout << player1 << " aimed for double 1 " << player1 << "'s score: " << JS.getScore() << endl;
											}
										}


										//if number is odd due to miss then this gets player's score back into hitting doubles again
										if (j_Odd == 9)
										{
											JS.reduceScore(John.throw_single(9, John.percentage)); //Player aims for 9 on the dartboard, can miss and return 14 or 12
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " hit 9 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (j_Odd == 7)
										{
											JS.reduceScore(John.throw_single(7, John.percentage)); //Player aims for 7 on the dartboard, can miss and return 16 or 19
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " hit 7 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (j_Odd == 5)
										{
											JS.reduceScore(John.throw_single(5, John.percentage)); //Player aims for 5 on the dartboard, can miss and return 12 or 20
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " hit 5 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (j_Odd == 3)
										{
											JS.reduceScore(John.throw_single(3, John.percentage)); //Player aims for 3 on the dartboard, can miss and return 19 or 17
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " hit 3 " << player1 << " score: " << JS.getScore() << endl;
										}
										else if (j_Odd == 1)
										{
											JS.reduceScore(John.throw_single(1, John.percentage)); //Player aims for 1 on the dartboard, can miss and return 11 or 16
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " hit 1 " << player1 << "'s score: " << JS.getScore() << endl;
										}

									}

									if (JS.getScore() == 0) //If player is successful in hitting a double and their score is 0
									{
										John.won++; //They win

										if (John.getWon() == 3 && Jset != 7 && Sset != 7) //If the player wins is 3 (winning a set)
										{
											Jset++; //Player one's number of winned set's is incremented
										}
										John.Totalwins++; //Player's total wins is incremented
										//cout << player1 << " won!" << endl;
										Game = false; //Ending the game as player one won
										break; //extra measurement to make sure it breaks the loop
									}

									if (JS.getScore() <= -1) //If player's score becomes negative
									{
										JS.addScore(JS.getBelow()); //Adds 3 darts thrown back onto player score
										//cout << player1 << " has gone bust!" << player1 << "'s score: " << JS.getScore() << endl;
									}


								}//End of Player1 throwing 3 darts for loop

							    ////////////////Player two's scoring section (Same as John's scoring section only player names are changed)///////////////

								for (int f = 0; f < 3; f++) //Sid throws 3 darts
								{
									if (SS.getScore() >= 70 && Sid.dartsThrown <= 3)
									{
										SS.reduceScore(Sid.throw_treble(20, Sid.percentage));
										Sid.dartsThrown++;
										Sid.Totaldarts++;
										//cout << player2 << " threw for a treble 20! " << player2 << "'s score: " << SS.getScore() << endl;
									}

									if (SS.getScore() <= 70 && SS.getScore() >= 41 && Sid.dartsThrown <= 3)
									{
										if (SS.getScore() % 2 == 0)
										{
											//number is even
											int s_Even = SS.getScore() % 10;

											if (s_Even == 8)
											{
												SS.reduceScore(Sid.throw_single(8, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player1 << " hit 8 " << player1 << "'s score: "  << JS.getScore() << endl;
											}
											else if (s_Even == 6)
											{
												SS.reduceScore(Sid.throw_single(6, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player1 << " hit 6 " << player1 << "'s score: " << JS.getScore() << endl;

											}
											else if (s_Even == 4)
											{
												SS.reduceScore(Sid.throw_single(4, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player1 << " hit 4 " << player1 << "'s score: " << JS.getScore() << endl;
											}
											else if (s_Even == 2)
											{
												SS.reduceScore(Sid.throw_single(2, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player1 << " hit 2 " << player1 << "'s score: " << JS.getScore() << endl;
											}

										}
										else
										{
											//number is odd
											int s_Odd = SS.getScore() % 10;

											if (s_Odd == 9)
											{
												SS.reduceScore(Sid.throw_single(9, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player1 << " hit 9 " << player1 << "'s score: " << JS.getScore() << endl;
											}
											else if (s_Odd == 7)
											{
												SS.reduceScore(Sid.throw_single(7, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player1 << " hit 7 " << player1 << "'s score: " << JS.getScore() << endl;
											}
											else if (s_Odd == 5)
											{
												SS.reduceScore(Sid.throw_single(5, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player1 << " hit 5 " << player1 << "'s score: " << JS.getScore() << endl;
											}
											else if (s_Odd == 3)
											{
												SS.reduceScore(Sid.throw_single(3, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player1 << " hit 3 " << player1 << " score: " << JS.getScore() << endl;
											}
											else if (s_Odd == 1)
											{
												SS.reduceScore(Sid.throw_single(1, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player1 << " hit 1 " << player1 << "'s score: " << JS.getScore() << endl;
											}
										}
									}

									if (SS.getScore() == 60 && Sid.dartsThrown <= 3)
									{
										SS.reduceScore(Sid.throw_single(20, Sid.percentage));
										Sid.dartsThrown++;
										Sid.Totaldarts++;
										//cout << player2 << " aimed for 20 " << player2 << "'s score: " << SS.getScore() << endl;
									}

									if (SS.getScore() == 50 && Sid.dartsThrown <= 3) //Winning the game(Hitting bullseye)
									{
										SS.reduceScore(Sid.throw_bull(Sid.percentage));
										Sid.dartsThrown++;
										Sid.Totaldarts++;
										//cout << player2 << " aimed for a bullseye! " << player2 << "'s score: " << SS.getScore() << endl;

										if (SS.getScore() == 0)
										{
											Sid.bulls_hit++;
											Sid.won++;
											if (Sid.getWon() == 3 && Jset != 7 && Sset != 7)
											{
												Sset++;
											}
											Sid.Totalwins++;
											//cout << " " << John.getWon() << "    :   " << Sid.getWon() << "   | " << endl;
											//cout << player2 << " won!" << endl;
											Game = false;
											break;
										}
										else
										{
											Sid.outerbulls_hit++;
										}

									}

									if (SS.getScore() <= 40 && Sid.dartsThrown <= 3) //Winning the game(hitting doubles)
									{
										int SfirstDigit = SS.getScore() / 10; // get first digit of the player score
										//cout << "First digit is: " << SfirstDigit << endl;
										int SsecondDigit = SS.getScore() % 10; //get right most number
										//cout << "Second digit is: " << SsecondDigit << endl;
										int s_Odd = SS.getScore() % 10;

										if (SfirstDigit == 4)
										{
											if (SsecondDigit == 0)
											{
												SS.reduceScore(Sid.throw_double(20, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player2 << " aimed for double 20 " << player2 << "'s score: " << SS.getScore() << endl;
											}
										}
										else if (SfirstDigit == 3)
										{
											if (SsecondDigit == 8)
											{
												SS.reduceScore(Sid.throw_double(19, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player2 << " aimed for double 19 " << player2 << "'s score: " << SS.getScore() << endl;

											}
											else if (SsecondDigit == 6)
											{
												SS.reduceScore(Sid.throw_double(18, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player2 << " aimed for double 18 " << player2 << "'s score: " << SS.getScore() << endl;
											}
											else if (SsecondDigit == 4)
											{
												SS.reduceScore(Sid.throw_double(17, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player2 << " aimed for double 17 " << player2 << "'s score: " << SS.getScore() << endl;
											}
											else if (SsecondDigit == 2)
											{
												SS.reduceScore(Sid.throw_double(16, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player2 << " aimed for double 16 " << player2 << "'s score: " << SS.getScore() << endl;
											}
											else if (SsecondDigit == 0)
											{
												SS.reduceScore(Sid.throw_double(15, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player2 << " aimed for double 15 " << player2 << "'s score: " << SS.getScore() << endl;
											}
										}
										else if (SfirstDigit == 2)
										{
											if (SsecondDigit == 8)
											{
												SS.reduceScore(Sid.throw_double(14, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player2 << " aimed for double 14 " << player2 << "'s score: " << SS.getScore() << endl;

											}
											else if (SsecondDigit == 6)
											{
												SS.reduceScore(Sid.throw_double(13, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player2 << " aimed for double 13 " << player2 << "'s score: " << SS.getScore() << endl;
											}
											else if (SsecondDigit == 4)
											{
												SS.reduceScore(Sid.throw_double(12, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player2 << " aimed for double 12 " << player2 << "'s score: " << SS.getScore() << endl;
											}
											else if (SsecondDigit == 2)
											{
												SS.reduceScore(Sid.throw_double(11, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player2 << " aimed for double 11 " << player2 << "'s score: " << SS.getScore() << endl;
											}
											else if (SsecondDigit == 0)
											{
												SS.reduceScore(Sid.throw_double(10, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player2 << " aimed for double 10 " << player2 << "'s score: " << SS.getScore() << endl;
											}
										}
										else if (SfirstDigit == 1)
										{
											if (SsecondDigit == 8)
											{
												SS.reduceScore(Sid.throw_double(9, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player2 << " aimed for double 9 " << player2 << "'s score: " << SS.getScore() << endl;
											}
											else if (SsecondDigit == 6)
											{
												SS.reduceScore(Sid.throw_double(8, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player2 << " aimed for double 8 " << player2 << "'s score: " << SS.getScore() << endl;
											}
											else if (SsecondDigit == 4)
											{
												SS.reduceScore(Sid.throw_double(7, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player2 << " aimed for double 7 " << player2 << "'s score: " << SS.getScore() << endl;
											}
											else if (SsecondDigit == 2)
											{
												SS.reduceScore(Sid.throw_double(6, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player2 << " aimed for double 6 " << player2 << "'s score: " << SS.getScore() << endl;
											}
											else if (SsecondDigit == 0)
											{
												SS.reduceScore(Sid.throw_double(5, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player2 << " aimed for double 5 " << player2 << "'s score: " << SS.getScore() << endl;
											}
										}
										else if (SfirstDigit == 0)
										{
											if (SsecondDigit == 8)
											{
												SS.reduceScore(Sid.throw_double(4, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player2 << " aimed for double 4 " << player2 << "'s score: " << SS.getScore() << endl;
											}
											else if (SsecondDigit == 6)
											{
												SS.reduceScore(Sid.throw_double(3, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player2 << " aimed for double 3 " << player2 << "'s score: " << SS.getScore() << endl;
											}
											else if (SsecondDigit == 4)
											{
												SS.reduceScore(Sid.throw_double(2, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player2 << " aimed for double 2 " << player2 << "'s score: " << SS.getScore() << endl;
											}
											else if (SsecondDigit == 2)
											{
												SS.reduceScore(Sid.throw_double(1, Sid.percentage));
												Sid.dartsThrown++;
												Sid.Totaldarts++;
												//cout << player2 << " aimed for double 1 " << player2 << "'s score: " << SS.getScore() << endl;
											}
										}

										//if number is odd 
										if (s_Odd == 9)
										{
											SS.reduceScore(Sid.throw_single(9, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player1 << " hit 9 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (s_Odd == 7)
										{
											SS.reduceScore(Sid.throw_single(7, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player1 << " hit 7 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (s_Odd == 5)
										{
											SS.reduceScore(Sid.throw_single(5, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player1 << " hit 5 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (s_Odd == 3)
										{
											SS.reduceScore(Sid.throw_single(3, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player1 << " hit 3 " << player1 << " score: " << JS.getScore() << endl;
										}
										else if (s_Odd == 1)
										{
											SS.reduceScore(Sid.throw_single(1, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player1 << " hit 1 " << player1 << "'s score: " << JS.getScore() << endl;
										}

									}

									if (SS.getScore() == 0)
									{
										Sid.won++;
										if (Sid.getWon() == 3 && Jset != 7 && Sset != 7)
										{
											Sset++;
										}
										Sid.Totalwins++;
										//cout << " " << John.getWon() << "    :   " << Sid.getWon() << "   | " << endl;
										//cout << player2 << " won!" << endl;
										Game = false;
										break;
									}

									if (SS.getScore() <= -1)
									{
										SS.addScore(SS.getBelow()); //Adds 3 darts thrown back onto player score
										//cout << player2 << " has gone bust!" << player2 << "'s score: " << SS.getScore() << endl;
									}



								}//end of Player2 throwing 3 darts for loop
							

							
						}//end of John's winning minigame if statment
						else if (Sid.miniWon == 1)//////////////////////////////////SID WINS THE MINIGAME, SID STARTS FIRST/////////////////////////////////////
						{
							Sid.dartsThrown = 0; //Resetting player two's dart count(used as boundary in Game loop)
							John.dartsThrown = 0;//Resetting player ones's dart count(used as boundary in Game loop)
							JS.changeBelow(0); //This is to reset John's 3 thrown darts score
							SS.changeBelow(0); //This is to reset John's 3 thrown darts score

							for (int f = 0; f < 3; f++) //Sid throw's 3 darts
							{
								if (SS.getScore() >= 70 && Sid.dartsThrown <= 3)
								{
									SS.reduceScore(Sid.throw_treble(20, Sid.percentage));
									Sid.dartsThrown++;
									Sid.Totaldarts++;
									//cout << player2 << " threw for a treble 20! " << player2 << "'s score: " << SS.getScore() << endl;
								}

								if (SS.getScore() <= 70 && SS.getScore() >= 41 && Sid.dartsThrown <= 3)
								{
									if (SS.getScore() % 2 == 0)
									{
										//number is even
										int s_Even = SS.getScore() % 10;

										if (s_Even == 8)
										{
											SS.reduceScore(Sid.throw_single(8, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player1 << " hit 8 " << player1 << "'s score: "  << JS.getScore() << endl;
										}
										else if (s_Even == 6)
										{
											SS.reduceScore(Sid.throw_single(6, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player1 << " hit 6 " << player1 << "'s score: " << JS.getScore() << endl;

										}
										else if (s_Even == 4)
										{
											SS.reduceScore(Sid.throw_single(4, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player1 << " hit 4 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (s_Even == 2)
										{
											SS.reduceScore(Sid.throw_single(2, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player1 << " hit 2 " << player1 << "'s score: " << JS.getScore() << endl;
										}

									}
									else
									{
										//number is odd
										int s_Odd = SS.getScore() % 10;

										if (s_Odd == 9)
										{
											SS.reduceScore(Sid.throw_single(9, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player1 << " hit 9 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (s_Odd == 7)
										{
											SS.reduceScore(Sid.throw_single(7, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player1 << " hit 7 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (s_Odd == 5)
										{
											SS.reduceScore(Sid.throw_single(5, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player1 << " hit 5 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (s_Odd == 3)
										{
											SS.reduceScore(Sid.throw_single(3, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player1 << " hit 3 " << player1 << " score: " << JS.getScore() << endl;
										}
										else if (s_Odd == 1)
										{
											SS.reduceScore(Sid.throw_single(1, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player1 << " hit 1 " << player1 << "'s score: " << JS.getScore() << endl;
										}
									}
								}

								if (SS.getScore() == 60 && Sid.dartsThrown <= 3)
								{
									SS.reduceScore(Sid.throw_single(20, Sid.percentage));
									Sid.dartsThrown++;
									Sid.Totaldarts++;
									//cout << player2 << " aimed for 20 " << player2 << "'s score: " << SS.getScore() << endl;
								}

								if (SS.getScore() == 50 && Sid.dartsThrown <= 3) //Winning the game(Hitting bullseye)
								{
									SS.reduceScore(Sid.throw_bull(Sid.percentage));
									Sid.dartsThrown++;
									Sid.Totaldarts++;
									//cout << player2 << " aimed for a bullseye! " << player2 << "'s score: " << SS.getScore() << endl;

									if (SS.getScore() == 0)
									{
										Sid.bulls_hit++;
										Sid.won++;
										if (Sid.getWon() == 3 && Jset != 7 && Sset != 7)
										{
											Sset++;
										}
										Sid.Totalwins++;
										//cout << " " << John.getWon() << "    :   " << Sid.getWon() << "   | " << endl;
										//cout << player2 << " won!" << endl;
										Game = false;
										break;
									}
									else
									{
										Sid.outerbulls_hit++;
									}

								}

								if (SS.getScore() <= 40 && Sid.dartsThrown <= 3) //Winning the game(hitting doubles)
								{
									int SfirstDigit = SS.getScore() / 10; // get first digit of the player score
									//cout << "First digit is: " << SfirstDigit << endl;
									int SsecondDigit = SS.getScore() % 10; //get right most number
									//cout << "Second digit is: " << SsecondDigit << endl;
									int s_Odd = SS.getScore() % 10;

									if (SfirstDigit == 4)
									{
										if (SsecondDigit == 0)
										{
											SS.reduceScore(Sid.throw_double(20, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player2 << " aimed for double 20 " << player2 << "'s score: " << SS.getScore() << endl;
										}
									}
									else if (SfirstDigit == 3)
									{
										if (SsecondDigit == 8)
										{
											SS.reduceScore(Sid.throw_double(19, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player2 << " aimed for double 19 " << player2 << "'s score: " << SS.getScore() << endl;

										}
										else if (SsecondDigit == 6)
										{
											SS.reduceScore(Sid.throw_double(18, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player2 << " aimed for double 18 " << player2 << "'s score: " << SS.getScore() << endl;
										}
										else if (SsecondDigit == 4)
										{
											SS.reduceScore(Sid.throw_double(17, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player2 << " aimed for double 17 " << player2 << "'s score: " << SS.getScore() << endl;
										}
										else if (SsecondDigit == 2)
										{
											SS.reduceScore(Sid.throw_double(16, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player2 << " aimed for double 16 " << player2 << "'s score: " << SS.getScore() << endl;
										}
										else if (SsecondDigit == 0)
										{
											SS.reduceScore(Sid.throw_double(15, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player2 << " aimed for double 15 " << player2 << "'s score: " << SS.getScore() << endl;
										}
									}
									else if (SfirstDigit == 2)
									{
										if (SsecondDigit == 8)
										{
											SS.reduceScore(Sid.throw_double(14, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player2 << " aimed for double 14 " << player2 << "'s score: " << SS.getScore() << endl;

										}
										else if (SsecondDigit == 6)
										{
											SS.reduceScore(Sid.throw_double(13, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player2 << " aimed for double 13 " << player2 << "'s score: " << SS.getScore() << endl;
										}
										else if (SsecondDigit == 4)
										{
											SS.reduceScore(Sid.throw_double(12, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player2 << " aimed for double 12 " << player2 << "'s score: " << SS.getScore() << endl;
										}
										else if (SsecondDigit == 2)
										{
											SS.reduceScore(Sid.throw_double(11, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player2 << " aimed for double 11 " << player2 << "'s score: " << SS.getScore() << endl;
										}
										else if (SsecondDigit == 0)
										{
											SS.reduceScore(Sid.throw_double(10, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player2 << " aimed for double 10 " << player2 << "'s score: " << SS.getScore() << endl;
										}
									}
									else if (SfirstDigit == 1)
									{
										if (SsecondDigit == 8)
										{
											SS.reduceScore(Sid.throw_double(9, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player2 << " aimed for double 9 " << player2 << "'s score: " << SS.getScore() << endl;
										}
										else if (SsecondDigit == 6)
										{
											SS.reduceScore(Sid.throw_double(8, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player2 << " aimed for double 8 " << player2 << "'s score: " << SS.getScore() << endl;
										}
										else if (SsecondDigit == 4)
										{
											SS.reduceScore(Sid.throw_double(7, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player2 << " aimed for double 7 " << player2 << "'s score: " << SS.getScore() << endl;
										}
										else if (SsecondDigit == 2)
										{
											SS.reduceScore(Sid.throw_double(6, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player2 << " aimed for double 6 " << player2 << "'s score: " << SS.getScore() << endl;
										}
										else if (SsecondDigit == 0)
										{
											SS.reduceScore(Sid.throw_double(5, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player2 << " aimed for double 5 " << player2 << "'s score: " << SS.getScore() << endl;
										}
									}
									else if (SfirstDigit == 0)
									{
										if (SsecondDigit == 8)
										{
											SS.reduceScore(Sid.throw_double(4, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player2 << " aimed for double 4 " << player2 << "'s score: " << SS.getScore() << endl;
										}
										else if (SsecondDigit == 6)
										{
											SS.reduceScore(Sid.throw_double(3, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player2 << " aimed for double 3 " << player2 << "'s score: " << SS.getScore() << endl;
										}
										else if (SsecondDigit == 4)
										{
											SS.reduceScore(Sid.throw_double(2, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player2 << " aimed for double 2 " << player2 << "'s score: " << SS.getScore() << endl;
										}
										else if (SsecondDigit == 2)
										{
											SS.reduceScore(Sid.throw_double(1, Sid.percentage));
											Sid.dartsThrown++;
											Sid.Totaldarts++;
											//cout << player2 << " aimed for double 1 " << player2 << "'s score: " << SS.getScore() << endl;
										}
									}

									//if number is odd 
									if (s_Odd == 9)
									{
										SS.reduceScore(Sid.throw_single(9, Sid.percentage));
										Sid.dartsThrown++;
										Sid.Totaldarts++;
										//cout << player1 << " hit 9 " << player1 << "'s score: " << JS.getScore() << endl;
									}
									else if (s_Odd == 7)
									{
										SS.reduceScore(Sid.throw_single(7, Sid.percentage));
										Sid.dartsThrown++;
										Sid.Totaldarts++;
										//cout << player1 << " hit 7 " << player1 << "'s score: " << JS.getScore() << endl;
									}
									else if (s_Odd == 5)
									{
										SS.reduceScore(Sid.throw_single(5, Sid.percentage));
										Sid.dartsThrown++;
										Sid.Totaldarts++;
										//cout << player1 << " hit 5 " << player1 << "'s score: " << JS.getScore() << endl;
									}
									else if (s_Odd == 3)
									{
										SS.reduceScore(Sid.throw_single(3, Sid.percentage));
										Sid.dartsThrown++;
										Sid.Totaldarts++;
										//cout << player1 << " hit 3 " << player1 << " score: " << JS.getScore() << endl;
									}
									else if (s_Odd == 1)
									{
										SS.reduceScore(Sid.throw_single(1, Sid.percentage));
										Sid.dartsThrown++;
										Sid.Totaldarts++;
										//cout << player1 << " hit 1 " << player1 << "'s score: " << JS.getScore() << endl;
									}

								}

								if (SS.getScore() == 0)
								{
									Sid.won++;
									if (Sid.getWon() == 3 && Jset != 7 && Sset != 7)
									{
										Sset++;
									}
									Sid.Totalwins++;
									//cout << " " << John.getWon() << "    :   " << Sid.getWon() << "   | " << endl;
									//cout << player2 << " won!" << endl;
									Game = false;
									break;
								}

								if (SS.getScore() <= -1)
								{
									SS.addScore(SS.getBelow()); //Adds 3 darts thrown back onto player score
									//cout << player2 << " has gone bust!" << player2 << "'s score: " << SS.getScore() << endl;
								}



							}//end of Player2 throwing 3 darts for loop

							/////////////John's Section(Same as Sid's section, only player names changed)////////////////

							for (int d = 0; d < 3; d++) //John throws 3 darts
							{
								////////Scoring section of the game loop////

								if (JS.getScore() >= 70 && John.dartsThrown <= 3) //Players simply aiming for treble 20 to get below or equal to 70 and hasn't thrown three darts already.
								{
									JS.reduceScore(John.throw_treble(20, John.percentage)); //Score is recuded by number that's returned from throwing dart at treble 20 area.
									John.dartsThrown++; //Incrementing the thrown darts boundary
									John.Totaldarts++; //Incrementing the Total darts player one has thrown. 
									//cout << player1 << " threw for a treble 20! " << player1 << "'s score: " << JS.getScore() << endl;
								}

								/////////Focus section of Game loop////////////

								if (JS.getScore() <= 70 && JS.getScore() >= 41 && John.dartsThrown <= 3) // If player score is in range of 41-70 and hasn't thrown three darts already.
								{
									if (JS.getScore() % 2 == 0) //checking is the number even
									{
										//number is even
										int Jeven = JS.getScore() % 10; //Getting right most number of player one's score
										//cout << "Jeven is: " << Jeven << endl;

										if (Jeven == 8)
										{
											JS.reduceScore(John.throw_single(8, John.percentage)); //Player aims for 8 on the dartboard, can miss and return 11 or 16
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " hit 8 " << player1 << "'s score: "  << JS.getScore() << endl;
										}
										else if (Jeven == 6)
										{
											JS.reduceScore(John.throw_single(6, John.percentage)); //Player aims for 6 on the dartboard, can miss and return 13 or 10
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " hit 6 " << player1 << "'s score: " << JS.getScore() << endl;

										}
										else if (Jeven == 4)
										{
											JS.reduceScore(John.throw_single(4, John.percentage)); //Player aims for 4 on the dartboard, can miss and return 18 or 13
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " hit 4 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (Jeven == 2)
										{
											JS.reduceScore(John.throw_single(2, John.percentage)); //Player aims for 2 on the dartboard, can miss and return 17 or 15
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " hit 2 " << player1 << "'s score: " << JS.getScore() << endl;
										}
									}
									else
									{
										//number is odd
										int j_Odd = JS.getScore() % 10;

										if (j_Odd == 9)
										{
											JS.reduceScore(John.throw_single(9, John.percentage)); //Player aims for 9 on the dartboard, can miss and return 14 or 12
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " hit 9 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (j_Odd == 7)
										{
											JS.reduceScore(John.throw_single(7, John.percentage)); //Player aims for 7 on the dartboard, can miss and return 16 or 19
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " hit 7 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (j_Odd == 5)
										{
											JS.reduceScore(John.throw_single(5, John.percentage)); //Player aims for 5 on the dartboard, can miss and return 12 or 20
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " hit 5 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (j_Odd == 3)
										{
											JS.reduceScore(John.throw_single(3, John.percentage)); //Player aims for 3 on the dartboard, can miss and return 19 or 17
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " hit 3 " << player1 << " score: " << JS.getScore() << endl;
										}
										else if (j_Odd == 1)
										{
											JS.reduceScore(John.throw_single(1, John.percentage)); //Player aims for 1 on the dartboard, can miss and return 11 or 16
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " hit 1 " << player1 << "'s score: " << JS.getScore() << endl;
										}
									}
								}

								if (JS.getScore() == 60 && John.dartsThrown <= 3) //player aims for single 20 just to get score below to double area
								{
									JS.reduceScore(John.throw_single(20, John.percentage));
									John.dartsThrown++;
									John.Totaldarts++;
									//cout << player1 << " aimed for 20 " << player1 << "'s score: " << JS.getScore() << endl;
								}

								////////Winning the game(Checkout section)/////

								if (JS.getScore() == 50 && John.dartsThrown <= 3) //Winning the game(Hitting bullseye)
								{
									JS.reduceScore(John.throw_bull(John.percentage));
									John.dartsThrown++;
									John.Totaldarts++;
									//cout << player1 << " aimed for a bullseye! " << player1 << "'s score: " << JS.getScore() << endl;

									if (JS.getScore() == 0)
									{
										John.bulls_hit++; //Incrementing player one's number of bulls hit
										John.won++; //Incrementing player one's wins for current set
										if (John.getWon() == 3 && Jset != 7 && Sset != 7)
										{
											Jset++;
										}
										John.Totalwins++; //Incrementing player one's wins for number of games
										//cout << player1 << " won!" << endl;
										Game = false;
										break;
									}
									else
									{
										John.outerbulls_hit++; //Incrementing number of outer bulls hit for number of games
									}

								}

								if (JS.getScore() <= 40 && John.dartsThrown <= 3) //Winning the game(hitting doubles)
								{
									int firstDigit = JS.getScore() / 10; // get first digit of the player score
									int secondDigit = JS.getScore() % 10; //get right most number(used for even)
									int j_Odd = JS.getScore() % 10; //get right most number(used for odd)
									//cout << "First digit is: " << firstDigit << endl;
									//cout << "Second digit is: " << secondDigit << endl;


									if (firstDigit == 4) //If player score is in the 40 range
									{
										if (secondDigit == 0) //If player score is 40
										{
											JS.reduceScore(John.throw_double(20, John.percentage)); //Aim for double 20(40)
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " aimed for double 20 " << player1 << "'s score: " << JS.getScore() << endl;
										}
									}
									else if (firstDigit == 3) //If player score is in the 30 range
									{
										if (secondDigit == 8) //If the player score is 38
										{
											JS.reduceScore(John.throw_double(19, John.percentage)); //aim for double 19(38)
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " aimed for double 19 " << player1 << "'s score: " << JS.getScore() << endl;

										}
										else if (secondDigit == 6)//If player score is 36
										{
											JS.reduceScore(John.throw_double(18, John.percentage)); //Aim for double 18(36)
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " aimed for double 18 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (secondDigit == 4) //If player score is 34
										{
											JS.reduceScore(John.throw_double(17, John.percentage)); //Aim for double 17(34)
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " aimed for double 17 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (secondDigit == 2) //If player score is 32
										{
											JS.reduceScore(John.throw_double(16, John.percentage)); //Aim for double 16(32)
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " aimed for double 16 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (secondDigit == 0) //If player score is 30
										{
											JS.reduceScore(John.throw_double(15, John.percentage)); //Aim for double 15(30)
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " aimed for double 15 " << player1 << "'s score: " << JS.getScore() << endl;
										}
									}
									else if (firstDigit == 2) //If player score is in 20 range
									{
										if (secondDigit == 8) //If player score is 28
										{
											JS.reduceScore(John.throw_double(14, John.percentage)); //Aim for double 14(28)
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " aimed for double 14 " << player1 << "'s score: " << JS.getScore() << endl;

										}
										else if (secondDigit == 6) //If player score is 26
										{
											JS.reduceScore(John.throw_double(13, John.percentage)); //Aim for double 13(26)
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " aimed for double 13 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (secondDigit == 4) //If player score is 24
										{
											JS.reduceScore(John.throw_double(12, John.percentage)); //Aim for double 12(24)
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " aimed for double 12 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (secondDigit == 2) //If player score is 22
										{
											JS.reduceScore(John.throw_double(11, John.percentage)); //Aim for double 11(22)
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " aimed for double 11 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (secondDigit == 0) //If player score is 20
										{
											JS.reduceScore(John.throw_double(10, John.percentage)); //Aim for double 10(20)
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " aimed for double 10 " << player1 << "'s score: " << JS.getScore() << endl;
										}
									}
									else if (firstDigit == 1) //If player score is in 10 range
									{
										if (secondDigit == 8) //If player score is 18
										{
											JS.reduceScore(John.throw_double(9, John.percentage)); //Aim for double 9(18)
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " aimed for double 9 " << player1 << "'s score: " << JS.getScore() << endl;

										}
										else if (secondDigit == 6) //If player score is 16
										{
											JS.reduceScore(John.throw_double(8, John.percentage)); //Aim for double 8(16)
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " aimed for double 8 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (secondDigit == 4) //If player score is 14
										{
											JS.reduceScore(John.throw_double(7, John.percentage)); //Aim for double 7(14)
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " aimed for double 7 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (secondDigit == 2) //If player score is 12
										{
											JS.reduceScore(John.throw_double(6, John.percentage)); //Aim for double 6(12)
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " aimed for double 6 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (secondDigit == 0) //If player score is 10
										{
											JS.reduceScore(John.throw_double(5, John.percentage)); //Aim for double 5(10)
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " aimed for double 5 " << player1 << "'s score: " << JS.getScore() << endl;
										}
									}
									else if (firstDigit == 0) //If player score is in range 0-9 (This is because 8 divided by 10 will give 0.8)
									{
										if (secondDigit == 8) //if player score is (8)
										{
											JS.reduceScore(John.throw_double(4, John.percentage)); //Aim for double 4(8)
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " aimed for double 4 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (secondDigit == 6) //If player score is 6
										{
											JS.reduceScore(John.throw_double(3, John.percentage)); //Aim for double 3(6)
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " aimed for double 3 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (secondDigit == 4) //If player score is 4 
										{
											JS.reduceScore(John.throw_double(2, John.percentage)); //Aim for double 2(4)
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " aimed for double 2 " << player1 << "'s score: " << JS.getScore() << endl;
										}
										else if (secondDigit == 2) //if player score is 2
										{
											JS.reduceScore(John.throw_double(1, John.percentage)); //Aim for double 1(2)
											John.dartsThrown++;
											John.Totaldarts++;
											//cout << player1 << " aimed for double 1 " << player1 << "'s score: " << JS.getScore() << endl;
										}
									}


									//if number is odd due to miss then this gets player's score back into hitting doubles again
									if (j_Odd == 9)
									{
										JS.reduceScore(John.throw_single(9, John.percentage)); //Player aims for 9 on the dartboard, can miss and return 14 or 12
										John.dartsThrown++;
										John.Totaldarts++;
										//cout << player1 << " hit 9 " << player1 << "'s score: " << JS.getScore() << endl;
									}
									else if (j_Odd == 7)
									{
										JS.reduceScore(John.throw_single(7, John.percentage)); //Player aims for 7 on the dartboard, can miss and return 16 or 19
										John.dartsThrown++;
										John.Totaldarts++;
										//cout << player1 << " hit 7 " << player1 << "'s score: " << JS.getScore() << endl;
									}
									else if (j_Odd == 5)
									{
										JS.reduceScore(John.throw_single(5, John.percentage)); //Player aims for 5 on the dartboard, can miss and return 12 or 20
										John.dartsThrown++;
										John.Totaldarts++;
										//cout << player1 << " hit 5 " << player1 << "'s score: " << JS.getScore() << endl;
									}
									else if (j_Odd == 3)
									{
										JS.reduceScore(John.throw_single(3, John.percentage)); //Player aims for 3 on the dartboard, can miss and return 19 or 17
										John.dartsThrown++;
										John.Totaldarts++;
										//cout << player1 << " hit 3 " << player1 << " score: " << JS.getScore() << endl;
									}
									else if (j_Odd == 1)
									{
										JS.reduceScore(John.throw_single(1, John.percentage)); //Player aims for 1 on the dartboard, can miss and return 11 or 16
										John.dartsThrown++;
										John.Totaldarts++;
										//cout << player1 << " hit 1 " << player1 << "'s score: " << JS.getScore() << endl;
									}

								}

								if (JS.getScore() == 0) //If player is successful in hitting a double and their score is 0
								{
									John.won++; //They win

									if (John.getWon() == 3 && Jset != 7 && Sset != 7) //If the player wins is 3 (winning a set)
									{
										Jset++; //Player one's number of winned set's is incremented
									}
									John.Totalwins++; //Player's total wins is incremented
									//cout << player1 << " won!" << endl;
									Game = false; //Ending the game as player one won
									break; //extra measurement to make sure it breaks the loop
								}

								if (JS.getScore() <= -1) //If player's score becomes negative
								{
									JS.addScore(JS.getBelow()); //Adds 3 darts thrown back onto player score
									//cout << player1 << " has gone bust!" << player1 << "'s score: " << JS.getScore() << endl;
								}


							}//End of Player1 throwing 3 darts for loop



						}//end of Sid's winning minigame if statment

				} //end of while loop


			}//end of set loop


		}//end of match for loop

		//cout << Jset << Sset << endl;

		//Outcome 7|0
		if (Jset == 7 && Sset == 0) //Did John get this outcome?
		{
			jOutcome1++; //Increment this outcome for John
		}
		else if (Sset == 7 && Jset == 0) //Did Sid get this outcome?
		{
			sOutcome1++; //Increment this outcome for Sid
		}
		//Outcome 7|1
		else if (Jset == 7 && Sset == 1)
		{
			jOutcome2++;
		}
		else if (Sset == 7 && Jset == 1)
		{
			sOutcome2++;
		}
		//Outcome 7|2
		else if (Jset == 7 && Sset == 2)
		{
			jOutcome3++;
		}
		else if (Sset == 7 && Jset == 2)
		{
			sOutcome3++;
		}
		//Outcome 7|3
		else if (Jset == 7 && Sset == 3)
		{
			jOutcome4++;
		}
		else if (Sset == 7 && Jset == 3)
		{
			sOutcome4++;
		}
		//Outcome 7|4
		else if (Jset == 7 && Sset == 4)
		{
			jOutcome5++;
		}
		else if (Sset == 7 && Jset == 4)
		{
			sOutcome5++;
		}
		//Outcome 7|5
		else if (Jset == 7 && Sset == 5)
		{
			jOutcome6++;
		}
		else if (Sset == 7 && Jset == 5)
		{
			sOutcome6++;
		}
		//Outcome 7|6
		else if (Jset == 7 && Sset == 6)
		{
			jOutcome7++;
		}
		else if (Sset == 7 && Jset == 6)
		{
			sOutcome7++;
		}
		
	}//end of numgames for loop

	///////////(SIMULATION ENDS)/////////////////


	//Calculating the frequency of outcomes for John
	double freq1 = (jOutcome1 / numGames) * 100; //Number of outcome divided by inputted number of games multiplied by 100
	double freq2 = (jOutcome2 / numGames) * 100;
	double freq3 = (jOutcome3 / numGames) * 100;
	double freq4 = (jOutcome4 / numGames) * 100;
	double freq5 = (jOutcome5 / numGames) * 100;
	double freq6 = (jOutcome6 / numGames) * 100;
	double freq7 = (jOutcome7 / numGames) * 100;
	//Calculating the frequency of outcomes for Sid
	double Sfreq1 = (sOutcome1 / numGames) * 100;
	double Sfreq2 = (sOutcome2 / numGames) * 100;
	double Sfreq3 = (sOutcome3 / numGames) * 100;
	double Sfreq4 = (sOutcome4 / numGames) * 100;
	double Sfreq5 = (sOutcome5 / numGames) * 100;
	double Sfreq6 = (sOutcome6 / numGames) * 100;
	double Sfreq7 = (sOutcome7 / numGames) * 100;
	double calc = freq1 + freq2 + freq3 + freq4 + freq5 + freq6 + freq7 + Sfreq1 + Sfreq2 + Sfreq3 + Sfreq4 + Sfreq5 + Sfreq6 + Sfreq7; //Calculating total percentage
	double johnAvg = ((double)John.Totaldarts) / numGames;  //Calculating the average of the player based on the darts thrown in all the rounds.
	double sidAvg = ((double)Sid.Totaldarts) / numGames;  //Calculating the average of the player based on the darts thrown in all the rounds.

	if (numGames == 1) //just a measure attempting to give accurate total percentage in the case of 1 game
	{
		freq1 = freq1 / 2;
		freq2 = freq2 / 2;
		freq3 = freq3 / 2;
		freq4 = freq4 / 2;
		freq5 = freq5 / 2;
		freq6 = freq6 / 2;
		freq7 = freq7 / 2;

		Sfreq1 = Sfreq1 / 2;
		Sfreq2 = Sfreq2 / 2;
		Sfreq3 = Sfreq3 / 2;
		Sfreq4 = Sfreq4 / 2;
		Sfreq5 = Sfreq5 / 2;
		Sfreq6 = Sfreq6 / 2;
		Sfreq7 = Sfreq7 / 2;
			
		calc = calc / 2;
	}

	int Jposs[8][8]{ {7, 6,}, //Array to simply store outcomes to display easier
					{7, 5,},
					{7, 4,},
					{7, 3,},
					{7, 2,},
					{7, 1,},
					{7, 0,}};

	int Sposs[8][8]{ {7, 6,}, //Array to simply store outcomes to display easier
					{7, 5,},
					{7, 4,},
					{7, 3,},
					{7, 2,},
					{7, 1,},
					{7, 0,}};

	///////DISPLAYING RESULTS TO THE PLAYERS)//////////////////

	cout << "////////////////////////////////////////////      R E S U L T S     /////////////////////////////////////////////////" << endl;
	cout << "__________________________________" << endl;
	cout << "John's Outcomes for " << numGames << " matches" << endl;
	cout << "__________________________________" << endl;
	cout << "John " << "   :   " << " Sid " << "   |   " << " Frequency" << endl;                                                            //John's Statistics
	cout << " " << Jposs[6][0] << "      :    "  << Jposs[6][1] << "      |  " << "      "   << freq1 << "%" << "           John's Set Wins: " << John.Totalwins << endl;
	cout << " " << Jposs[5][0] << "      :    "  << Jposs[5][1] << "      |  " << "      "   << freq2 << "%" << "           John's Match wins: " << Jmatch << endl;
	cout << " " << Jposs[4][0] << "      :    "  << Jposs[4][1] << "      |  " << "      "   << freq3 << "%" << "           John's Bulls Hit: " << John.bulls_hit << endl;
	cout << " " << Jposs[3][0] << "      :    "  << Jposs[3][1] << "      |  " << "      "   << freq4 << "%" << "           John's Outer Bulls Hit: " << John.outerbulls_hit << endl;
	cout << " " << Jposs[2][0] << "      :    "  << Jposs[2][1] << "      |  " << "      "   << freq5 << "%" << "           John's Total Darts Thrown: " << John.Totaldarts << endl;
	cout << " " << Jposs[1][0] << "      :    "  << Jposs[1][1] << "      |  " << "      "   << freq6 << "%" << "           John's Avg Darts Thrown: " << johnAvg << endl;
	cout << " " << Jposs[0][0] << "      :    "  << Jposs[0][1] << "      |  " << "      "   << freq7 << "%" << endl;
	cout << " " << Jposs[0][0] << "      :    "  << Jposs[0][1] << "      |  " << "      "   << freq7 << "%" << endl;
	cout << "__________________________________" << endl;
	cout << "Sid's Outcomes for " << numGames << " matches " << endl;
	cout << "__________________________________" << endl;
	cout << "Sid " << "    :   " << " John " << "  |   " << " Frequency" << endl;                                                            //Sid's Statistics
	cout << " " << Sposs[6][0] << "      :    " << Sposs[6][1] << "      |  " << "      "  << Sfreq1 << "%" << "            Sid's Set Wins: " << Sid.Totalwins << endl;
	cout << " " << Sposs[5][0] << "      :    " << Sposs[5][1] << "      |  " << "      "  << Sfreq2 << "%" << "            Sid's Match wins: " << Smatch << endl;
	cout << " " << Sposs[4][0] << "      :    " << Sposs[4][1] << "      |  " << "      "  << Sfreq3 << "%" << "            Sid's Bulls Hit: " << Sid.bulls_hit << endl;
	cout << " " << Sposs[3][0] << "      :    " << Sposs[3][1] << "      |  " << "      "  << Sfreq4 << "%" << "            Sid's Outer Bulls Hit: " << Sid.outerbulls_hit << endl;
	cout << " " << Sposs[2][0] << "      :    " << Sposs[2][1] << "      |  " << "      "  << Sfreq5 << "%" << "            Sid's Total Darts Thrown: " << Sid.Totaldarts << endl;
	cout << " " << Sposs[1][0] << "      :    " << Sposs[1][1] << "      |  " << "      "  << Sfreq6 << "%" << "            Sid's Avg Darts Thrown: " << sidAvg << endl;
	cout << " " << Sposs[0][0] << "      :    " << Sposs[0][1] << "      |  " << "      "  << Sfreq7 << "%" << endl;
	cout << "Total Percentage= " << calc << "%" << endl;
	cout << "Enter any key to exit: ";
	cin >> e;
}