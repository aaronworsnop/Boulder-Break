#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define CAVE_SIZE 10

// Initialising Story
void InitialiseStory(char* paragraph)
{
	// The story
	strcpy(paragraph, "Greetings. After the Great War you fell down a long...\n\nlong...\n\nway...\n\nThere's nothing up there anymore. You might as well\n\n DELVE DEEPER!.");
}

// Printing the cave state
void PrintCave(int cave[CAVE_SIZE][CAVE_SIZE])
{
	for (int i = 0; i < CAVE_SIZE; i++)
	{
		for (int j = 0; j < CAVE_SIZE; j++)
		{
			if (j == 0 && i != 0)
			{
				if (cave[i][j] == 1)
				{
					printf("\n#");
				}
				else if (cave[i][j] == 3)
				{
					printf("\n ");
				}
				else if (cave[i][j] == 'X')
				{
					printf("\nX");
				}
				else if (cave[i][j] == '*')
				{
					printf("\n*");
				}
				else if (cave[i][j] == 'O')
				{
					printf("\nO");
				}
				else if (cave[i][j] == '+')
				{
					printf("\n+");
				}
				else
				{
					printf("\n ");
				}
			}
			else
			{
				if (cave[i][j] == 1)
				{
					printf("#");
				}
				else if (cave[i][j] == 3)
				{
					printf(" ");
				}
				else if (cave[i][j] == 'X')
				{
					printf("X");
				}
				else if (cave[i][j] == '*')
				{
					printf("*");
				}
				else if (cave[i][j] == 'O')
				{
					printf("O");
				}
				else if (cave[i][j] == '+')
				{
					printf("+");
				}
				else
				{
					printf(" ");
				}
			}
		}
	}
	printf("\n");
}

// Preparing initial cave state
void InitialiseCave(int cave[CAVE_SIZE][CAVE_SIZE], char* layout)
{
	int caveSection = 0;
	for (int i = 0; i < CAVE_SIZE; i++)
	{
		for (int j = 0; j < CAVE_SIZE; j++)
		{
			if (layout[caveSection] == '1')
			{
				// Wall
				cave[i][j] = 1;
			}
			else if (layout[caveSection] == '0')
			{
				// Empty
				cave[i][j] = 0;
			}
			else if (layout[caveSection] == 'E')
			{
				// Exit
				cave[i][j] = 3;
			}
			caveSection++;
		}
	}
}


int IsBorderComplete(int cave[CAVE_SIZE][CAVE_SIZE])
{
	for (int i = 0; i < CAVE_SIZE; i++)
	{
		for (int j = 0; j < CAVE_SIZE; j++)
		{
			if ((i == 0 || i == CAVE_SIZE - 1))
			{
				if (cave[i][j] != 1 && cave[i][j] != 3)
				{
					return 0;
				}
			}
			else if ((j == 0 || j == CAVE_SIZE - 1))
			{
				if (cave[i][j] != 1 && cave[i][j] != 3)
				{
					return 0;
				}
			}
			else
			{
				return 1;
			}
		}
	}
}

int IsExitUnique(int cave[CAVE_SIZE][CAVE_SIZE])
{
	int exits = 0;
	for (int i = 0; i < CAVE_SIZE; i++)
	{
		for (int j = 0; j < CAVE_SIZE; j++)
		{
			if (cave[i][j] == 3)
			{
				exits++;
			}
		}
	}
	if (exits == 1)
	{
		return 1;
	}
	return 0;
}

int IsExitAccessible(int cave[CAVE_SIZE][CAVE_SIZE])
{
	for (int i = 0; i < CAVE_SIZE; i++)
	{
		for (int j = 0; j < CAVE_SIZE; j++)
		{
			if (cave[i][j] == 3)
			{
				if ((i == 0 && j == 0) || (i == 0 && j == CAVE_SIZE - 1) || (i == CAVE_SIZE - 1 && j == 0) || (i == CAVE_SIZE - 1 && j == CAVE_SIZE - 1))
				{
					return 0;
				}
				else if (i > 0 && i < CAVE_SIZE - 1 && j > 0 && j < CAVE_SIZE - 1)
				{
					return 0;
				}
				else
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

void AddItem(int cave[CAVE_SIZE][CAVE_SIZE], int row, int col, char* element)
{
	int players = 0;
	for (int i = 0; i < CAVE_SIZE; i++)
	{
		for (int j = 0; j < CAVE_SIZE; j++)
		{
			if (cave[i][j] == 'X')
			{
				players++;
			}
		}
	}
	if (row >= 0 && row < CAVE_SIZE && col >= 0 && col < CAVE_SIZE && cave[row][col] == 0)
	{
		if (element[0] == 'p' && players < 1)
		{
			cave[row][col] = 'X';
		}
		else if (element[0] == 'h')
		{
			cave[row][col] = '*';
		}
		else if (element[0] == 't')
		{
			cave[row][col] = '+';
		}
		else if (element[0] == 'b')
		{
			cave[row][col] = 'O';
		}
	}
}

void RotateCave(int cave[CAVE_SIZE][CAVE_SIZE])
{
	int tempCave[CAVE_SIZE][CAVE_SIZE];
	for (int i = 0; i < CAVE_SIZE; i++)
	{
		for (int j = 0; j < CAVE_SIZE; j++)
		{
			tempCave[j][CAVE_SIZE - 1 - i] = cave[i][j];
		}
	}
	for (int i = 0; i < CAVE_SIZE; i++)
	{
		for (int j = 0; j < CAVE_SIZE; j++)
		{
			cave[i][j] = tempCave[i][j];
		}
	}
}

int MakeMove(int cave[CAVE_SIZE][CAVE_SIZE], char move)
{
	if (move == 'w')
	{
		// Checking through every element to find the player
		for (int i = 0; i < CAVE_SIZE; i++)
		{
			for (int j = 0; j < CAVE_SIZE; j++)
			{
				if (cave[i][j] == 'X' && cave[i - 1][j] != 1)
				{
					// Player move logic
					if (cave[i - 1][j] == 'O')
					{
						int boulderTravel = i - 1;
						while (cave[boulderTravel - 1][j] != 1)
						{
							if (cave[boulderTravel - 1][j] == 0)
							{
								// Move boulder up
								cave[boulderTravel][j] = 0;
								cave[boulderTravel - 1][j] = 'O';
								boulderTravel--;
							}
							else if (cave[boulderTravel - 1][j] == '+')
							{
								break;
							}
							else if (cave[boulderTravel - 1][j] == '*')
							{
								cave[boulderTravel][j] = 0;
								cave[boulderTravel - 1][j] = 0;
								break;
							}
							else if (cave[boulderTravel - 1][j] == 'O')
							{
								cave[boulderTravel][j] = 'O';
								break;
							}

						}
					}
					else if (cave[i - 1][j] == '*')
					{
						// Move player up
						cave[i][j] = 0;
						return 1;
					}
					else if (cave[i - 1][j] == 3)
					{
						// Move player up
						cave[i][j] = 0;
						cave[i - 1][j] = 'X';
						return 2;
					}
					else
					{
						cave[i][j] = 0;
						cave[i - 1][j] = 'X';
					}
				}
			}
		}
	}
	if (move == 'a')
	{
		RotateCave(cave);
		// Checking through every element to find the player
		for (int i = 0; i < CAVE_SIZE; i++)
		{
			for (int j = 0; j < CAVE_SIZE; j++)
			{
				if (cave[i][j] == 'X' && cave[i - 1][j] != 1)
				{
					// Player move logic
					if (cave[i - 1][j] == 'O')
					{
						int boulderTravel = i - 1;
						while (cave[boulderTravel - 1][j] != 1)
						{
							if (cave[boulderTravel - 1][j] == 0)
							{
								// Move boulder up
								cave[boulderTravel][j] = 0;
								cave[boulderTravel - 1][j] = 'O';
								boulderTravel--;
							}
							else if (cave[boulderTravel - 1][j] == '+')
							{
								break;
							}
							else if (cave[boulderTravel - 1][j] == '*')
							{
								cave[boulderTravel][j] = 0;
								cave[boulderTravel - 1][j] = 0;
								break;
							}
							else if (cave[boulderTravel - 1][j] == 'O')
							{
								cave[boulderTravel][j] = 'O';
								break;
							}

						}
					}
					else if (cave[i - 1][j] == '*')
					{
						// Move player up
						cave[i][j] = 0;
						RotateCave(cave);
						RotateCave(cave);
						RotateCave(cave);
						return 1;
					}
					else if (cave[i - 1][j] == 3)
					{
						// Move player up
						cave[i][j] = 0;
						cave[i - 1][j] = 'X';
						RotateCave(cave);
						RotateCave(cave);
						RotateCave(cave);
						return 2;
					}
					else
					{
						cave[i][j] = 0;
						cave[i - 1][j] = 'X';
					}
				}
			}
		}
		RotateCave(cave);
		RotateCave(cave);
		RotateCave(cave);
	}
	if (move == 's')
	{
		RotateCave(cave);
		RotateCave(cave);
		// Checking through every element to find the player
		for (int i = 0; i < CAVE_SIZE; i++)
		{
			for (int j = 0; j < CAVE_SIZE; j++)
			{
				if (cave[i][j] == 'X' && cave[i - 1][j] != 1)
				{
					// Player move logic
					if (cave[i - 1][j] == 'O')
					{
						int boulderTravel = i - 1;
						while (cave[boulderTravel - 1][j] != 1)
						{
							if (cave[boulderTravel - 1][j] == 0)
							{
								// Move boulder up
								cave[boulderTravel][j] = 0;
								cave[boulderTravel - 1][j] = 'O';
								boulderTravel--;
							}
							else if (cave[boulderTravel - 1][j] == '+')
							{
								break;
							}
							else if (cave[boulderTravel - 1][j] == '*')
							{
								cave[boulderTravel][j] = 0;
								cave[boulderTravel - 1][j] = 0;
								break;
							}
							else if (cave[boulderTravel - 1][j] == 'O')
							{
								cave[boulderTravel][j] = 'O';
								break;
							}

						}
					}
					else if (cave[i - 1][j] == '*')
					{
						// Move player up
						cave[i][j] = 0;
						RotateCave(cave);
						RotateCave(cave);
						return 1;
					}
					else if (cave[i - 1][j] == 3)
					{
						// Move player up
						cave[i][j] = 0;
						cave[i - 1][j] = 'X';
						RotateCave(cave);
						RotateCave(cave);
						return 2;
					}
					else
					{
						cave[i][j] = 0;
						cave[i - 1][j] = 'X';
					}
				}
			}
		}
		RotateCave(cave);
		RotateCave(cave);
	}
	if (move == 'd')
	{
		RotateCave(cave);
		RotateCave(cave);
		RotateCave(cave);
		// Checking through every element to find the player
		for (int i = 0; i < CAVE_SIZE; i++)
		{
			for (int j = 0; j < CAVE_SIZE; j++)
			{
				if (cave[i][j] == 'X' && cave[i - 1][j] != 1)
				{
					// Player move logic
					if (cave[i - 1][j] == 'O')
					{
						int boulderTravel = i - 1;
						while (cave[boulderTravel - 1][j] != 1)
						{
							if (cave[boulderTravel - 1][j] == 0)
							{
								// Move boulder up
								cave[boulderTravel][j] = 0;
								cave[boulderTravel - 1][j] = 'O';
								boulderTravel--;
							}
							else if (cave[boulderTravel - 1][j] == '+')
							{
								break;
							}
							else if (cave[boulderTravel - 1][j] == '*')
							{
								cave[boulderTravel][j] = 0;
								cave[boulderTravel - 1][j] = 0;
								break;
							}
							else if (cave[boulderTravel - 1][j] == 'O')
							{
								cave[boulderTravel][j] = 'O';
								break;
							}

						}
					}
					else if (cave[i - 1][j] == '*')
					{
						// Move player up
						cave[i][j] = 0;
						RotateCave(cave);
						return 1;
					}
					else if (cave[i - 1][j] == 3)
					{
						// Move player up
						cave[i][j] = 0;
						cave[i - 1][j] = 'X';
						RotateCave(cave);
						return 2;
					}
					else
					{
						cave[i][j] = 0;
						cave[i - 1][j] = 'X';
					}
				}
			}
		}
		RotateCave(cave);
	}
	return 0;
}

/* GetMove() returns the entered character. Invalid characters ignored */
char GetMove(void)
{
	char move;
	printf("\nEnter move: ");
	scanf("%c", &move);
	// Ignore any characters that are invalid
	while ((move != 'w') && (move != 'a') && (move != 's') && (move != 'd')) {
		scanf("%c", &move);
	}
	return move;
}

/* The Boulder Break simulation */
int main(void)
{
	char story[2000];
	char layout[200] = "1111111111111000001111000000111000000001100000000E10010000011100000011111000001111111001111111111111";
	int cave[CAVE_SIZE][CAVE_SIZE] = { 0 };
	int gameOver = 0;

	InitialiseStory(story);
	InitialiseCave(cave, layout);
	AddItem(cave, 2, 4, "boulder");
	AddItem(cave, 5, 6, "boulder");
	AddItem(cave, 4, 8, "hole");
	AddItem(cave, 1, 4, "treasure");
	AddItem(cave, 4, 5, "player");

	printf("ENGGEN131 - C Project 2022\n");
	printf("                          ... presents ...\n");
	printf("______   _____  _     _        ______  _______  ______\n");
	printf("|_____] |     | |     | |      |     \\ |______ |_____/\n");
	printf("|_____] |_____| |_____| |_____ |_____/ |______ |    \\_\n");
	printf("______   ______ _______ _______ _     _\n");
	printf("|_____] |_____/ |______ |_____| |____/ \n");
	printf("|_____] |    \\_ |______ |     | |    \\_\n");
	printf("\n");
	printf("%s\n", story);
	printf("\nMove the player (X) using the keys 'w', 'a', 's', 'd'\n");
	printf("Good luck!\n\n\n");

	/* Main game loop */
	PrintCave(cave);
	while (!gameOver) {
		gameOver = MakeMove(cave, GetMove());
		PrintCave(cave);
		if (gameOver == 1) {
			printf("\n\nGAME OVER!! \nYou died!\n\n");
		}
		else if (gameOver == 2) {
			printf("\n\nCONGRATULATIONS!! \nYou escaped!\n\n");
		}
	}

	return 0;
}