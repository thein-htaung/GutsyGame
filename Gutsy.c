#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_PLAYERS 500

typedef struct
{
	char name[30];
	int accPoints; //accumalated points for each game
	int numThrows;
} player_t;

void playGutsy(player_t *pl, int count[], int countPerGame[], int *numThrows);
int throwDice(int count[], int countPerGame[], int *accPoints, int *currPoints);
void printStatistics(int arr[]);
void getPlayerInfo(player_t *pl, int index);
void initArray(int arr[], int n);
void printPlayers_Throws(player_t *pl);

int main()
{
	int total_dice_count[7], throwPerTurn = 0;
	int perGame_dice_count[7];
	int totalAccPts = 0;
	int numOfPlayers = 0;
	int numOfGames = 0;
	bool gameEnds = false;
	player_t players[MAX_PLAYERS];


	// Initialize dice counts to zero
	initArray(total_dice_count, 7);
	initArray(perGame_dice_count, 7);

	printf("How many Gutsy players?\n");
	scanf("%i", &numOfPlayers);
	printf("How many times do you want to play?\n");
	scanf("%i", &numOfGames);

	srand((unsigned int)time(NULL));

	// Get players' names and initial the accumulated points and number of throws for each player
	for (int i = 0; i < numOfPlayers; i++)
	{
		getPlayerInfo(&players[i], i);
		players[i].accPoints = 0;
		players[i].numThrows = 0;
	}

	// Implement no. of games
	int gameCnt = 0;
	while (gameCnt < numOfGames)
	{
		printf("\n-------------Game #%i Begins-------------\n", gameCnt + 1);
		// Implement goal for 101 points for each player
		int index = 0;
		while (players[index].accPoints < 101)
		{
			playGutsy(&players[index], total_dice_count, perGame_dice_count, &players[index].numThrows);

			// This makes sure that the game exits once a player has gained a score of 101
			if (players[index].accPoints > 100)
			{
				printf("\n***** Winner: %s *****\n", players[index].name);
				break;
			}

			// Only increase the index of the players if more than one player
			if (numOfPlayers > 1)
			{
				index++;
			}

			if (index == numOfPlayers)
			{
				printf("\n");
			}
			index = index % numOfPlayers; //Alternate between players
		}

		// Reset each player accumulated points
		for (int i = 0; i < numOfPlayers; i++)
		{
			players[i].accPoints = 0;
		}

		printf("Game %i - Statistics\n", gameCnt + 1);
		printStatistics(perGame_dice_count);

		// Reset dice counts
		initArray(perGame_dice_count, 7);

		gameCnt++;
	}

	printf("\nFinal Statistics for 2 Games\n*******\n");
	for (int i = 0; i < numOfPlayers; i++)
	{
		printPlayers_Throws(&players[i]);
	}
	printf("\n");
	printStatistics(total_dice_count);
}

/* This function prints the player’s name and the total points for the play, the accumulated total for the game, and
	the number of throws needed in the play.
*/
void playGutsy(player_t *pl, int count[], int countPerGame[], int *numThrows)
{
	int curr_pts = 0;
	int curr_throws = 0;

	printf("%s's turn: ", pl->name);
	curr_throws = throwDice(count, countPerGame, &(pl->accPoints), &curr_pts);
	*numThrows += curr_throws;
	printf("= %i", curr_pts);
	printf(" Accumalated total = %i ", pl->accPoints);
	printf("Throws = %i\n", curr_throws);
}

/* This function returns:
	accumalated value, number of times the dice was thrown, and the counter for statistics
	and prints out the dice value for each throw
*/
int throwDice(int count[], int countPerGame[], int *accPoints, int *currPoints)
{

	int dice = 0;
	int counter = 0; // This counter stores how many throws are made in one game
	bool isDotOne = false;
	*currPoints = 0;

	while ((*currPoints < 40) && (dice != 1))
	{
		dice = rand() % 6 + 1;
		printf("%i ", dice); // Print random dice numbers
		*currPoints += dice;

		count[dice]++;
		countPerGame[dice]++;
		counter++;
	}
	if (dice == 1)
	{
		*currPoints = 0;
	}
	*accPoints += *currPoints;

	return counter;
}

/* This function calculates and displays(prints out) final statistics shown below.It accepts an array with
	the number of occurrences for each face value(stored in arr[]) and the total number of throws made(nThrows)
*/
void printStatistics(int arr[])
{
	double probability = 0;
	int nThrows = 0;

	// Get total throws
	for (int i = 1; i < 7; i++)
	{
		nThrows += arr[i];
	}

	// Print stats
	for (int i = 1; i < 7; i++)
	{
		probability = (double) arr[i] / nThrows;
		printf("P(%i): %.4lf (%i/%i)\n", i, probability, arr[i], nThrows);
	}
}

// This function asks for player's name, how many times the player wants to play and how many players
void getPlayerInfo(player_t *pl, int index)
{
	printf("Enter player #%i's name : ", index + 1);
	scanf("%s", pl->name);
}

// Array initalizer
void initArray(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = 0;
	}
}

// This function prints the number of throws that each player made
void printPlayers_Throws(player_t *pl)
{
	printf("%s\n", pl->name);
	printf("Total number of throws made: %i\n", pl->numThrows);
	printf("*******\n");
}