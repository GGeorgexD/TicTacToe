#include "stdio.h"
#include "TypesHeader.h"

//Declaration of enums
enum TTTGame_State_enum
{
	TTTGame_State_ChosingFirstMove,
	TTTGame_State_Playing,
	TTTGame_State_Victory,
	TTTGame_State_Draw
};

//Declaration of macro
#define MAX_ROWS 3
#define MAX_COLS 3

//Declaration of enum
enum whichPlayer_enum
{
	Player_1,
	Player_2
};

// Declaration of structure
struct TTTBoardInfo_struct
{
	tm_uint8 TTTBoard[MAX_ROWS][MAX_COLS];
	tm_uint8 numCols;
	tm_uint8 numRows;
};

//Declaration of variables
struct TTTBoardInfo_struct TTTBoardInfo;
enum whichPlayer_enum whichPlayer;
enum TTTGame_State_enum  TTTGame_State;
tm_uint32 TTTNumberofMoves;
tm_bool TTTStopTheGame;

//Declaration of function prototypes
void TTTInit(void);
void TTTInitBoard(void);
void main(void);
void TTTStartGame(void);
void TTTDisplayingBoard(void);
void TTTGameState(void);
tm_bool TTTChosingWhichPlayerMovesFirst(void);
void TTTMakingMoves(void);
void TTTMarking_On_Board(tm_uint32 columnsvalue, tm_uint32 rowsvalue);
tm_bool TTTCheckVictory(void);
void TTTStartAgainTheGame(void);


//Functions

//Init function
//Initialize the board, and the variables
void TTTInit(void)
{
	TTTInitBoard();
	whichPlayer = 0;
	TTTGame_State = TTTGame_State_ChosingFirstMove;
	TTTNumberofMoves = 0;
	TTTStopTheGame = false;
}

//Init Board dfnction
//Every position is given the character '_' except the last line, it receives the ' ' character(empty)
void TTTInitBoard(void)
{
	for (TTTBoardInfo.numRows = 0; TTTBoardInfo.numRows < MAX_ROWS; TTTBoardInfo.numRows++)
	{
		for (TTTBoardInfo.numCols = 0; TTTBoardInfo.numCols < MAX_COLS; TTTBoardInfo.numCols++)
		{
			if (TTTBoardInfo.numRows == MAX_ROWS - 1)
			{
				TTTBoardInfo.TTTBoard[TTTBoardInfo.numRows][TTTBoardInfo.numCols] = ' ';
			}
			else
			{
				TTTBoardInfo.TTTBoard[TTTBoardInfo.numRows][TTTBoardInfo.numCols] = '_';
			}
		}
	}
}

//Main function
//Calls the Start Game function
void main(void)
{
	TTTStartGame();
}

//Start Game function
//Function that initialize the game and runs until the it finishes
//Then it checks if the players wants to restart it.
void TTTStartGame(void)
{
	TTTInit();
	TTTDisplayingBoard();
	while (TTTStopTheGame == false)
	{
		TTTGameState();
	}
	TTTStartAgainTheGame();
}

//Display Board function
//After every character, the character '|' is added, except for the last column
void TTTDisplayingBoard(void)
{
	for (TTTBoardInfo.numRows = 0; TTTBoardInfo.numRows < MAX_ROWS; TTTBoardInfo.numRows++)
	{
		for (TTTBoardInfo.numCols = 0; TTTBoardInfo.numCols < MAX_COLS; TTTBoardInfo.numCols++)
		{
			printf("%c", TTTBoardInfo.TTTBoard[TTTBoardInfo.numRows][TTTBoardInfo.numCols]);
			if (TTTBoardInfo.numCols != MAX_COLS - 1)
			{
				printf("|");
			}
			else {/* Do nothing */ }
		}
		printf("\n");
	}
}

//Game State function
//The game's state-machine function 
void TTTGameState(void)
{
	tm_bool isVictory = false;
	switch (TTTGame_State)
	{
		case TTTGame_State_ChosingFirstMove:
		{
			if (TTTChosingWhichPlayerMovesFirst() == true)
			{
				TTTGame_State = TTTGame_State_Playing;
			}
			else {/* Do nothing */ }
			break;
		}
		case TTTGame_State_Playing:
		{
			TTTMakingMoves();
			if (TTTNumberofMoves > 4)
			{
				isVictory = TTTCheckVictory();
				if (isVictory == true)
				{
					TTTGame_State = TTTGame_State_Victory;
				}
				else if (TTTNumberofMoves == 9)
				{
					TTTGame_State = TTTGame_State_Draw;
				}
				else {/* Do nothing */}
			}
			break;
		}
		case TTTGame_State_Victory:
		{
			printf("PLAYER %d WINS\n", whichPlayer);
			TTTStopTheGame = true;
			break;
		}
		case TTTGame_State_Draw:
		{
			printf("It's a draw!\n");
			TTTStopTheGame = true;
			break;
		}
	}
}

//Chosing Which Player Moves First function
//Function that takes the input to see which player moves first.
//If the input is not valid, a notification massage will be displayed.
tm_bool TTTChosingWhichPlayerMovesFirst(void)
{
	tm_bool player_chosen = false;
	tm_uint32 choosePlayer;
	printf_s("\nChoose who goes first(1 -> Player 1(X), 2 -> Player 2(0)\n");
	scanf_s("%d", &choosePlayer);
	if ((choosePlayer != 1) && (choosePlayer != 2))
	{
		printf("\nNumber invalid!\nTry again!\n");
	}
	else if (choosePlayer == 1)
	{
		whichPlayer = Player_1;
		player_chosen = true;
	}
	else
	{
		whichPlayer = Player_2;
		player_chosen = true;
	}
	return player_chosen;
}

//Making Moves function
//Function that signilize which player turn is, then it marks the board with the sign
void TTTMakingMoves(void)
{
	tm_uint32 colsval;
	tm_uint32 rowsval;
	if (whichPlayer == Player_1)
	{
		printf("\nPlayer 1 moves!\n");
	}
	else
	{
		printf("\nPlayer 2 moves!\n");
	}
	printf_s("Enter row position(1 is the first position): ");
	scanf_s("%d", &rowsval);
	printf_s("Enter column position(1 is the fist position): ");
	scanf_s("%d", &colsval);
	TTTMarking_On_Board(rowsval - 1, colsval - 1);
}


//Marking on Board function
//Function that marks the board with the player's sign
void TTTMarking_On_Board(tm_uint32 rowsvalue, tm_uint32 columnsvalue)
{
	if ((columnsvalue == MAX_COLS) || (rowsvalue == MAX_ROWS))
	{
		printf("\nInvalid position!\nTry again!\n");
	}
	else
	{
		if ((TTTBoardInfo.TTTBoard[rowsvalue][columnsvalue] == '_') || (TTTBoardInfo.TTTBoard[rowsvalue][columnsvalue] == ' '))
		{
			if (whichPlayer == Player_1)
			{
				TTTBoardInfo.TTTBoard[rowsvalue][columnsvalue] = 'X';
			}
			else
			{
				TTTBoardInfo.TTTBoard[rowsvalue][columnsvalue] = '0';
			}
			whichPlayer = !whichPlayer;
			TTTNumberofMoves++;
		}
		else
		{
			printf("\nPosition already taken!\nTry again!\n");
		}
	}
	TTTDisplayingBoard();
}

//Check Victory function
//Function that checks if any player has won
tm_bool TTTCheckVictory(void)
{
	tm_uint8 local_numCols;
	tm_uint8 local_numRows;

	//Check if victory on any row
	for (local_numRows = 0; local_numRows < MAX_ROWS; local_numRows++)
	{
		if ((TTTBoardInfo.TTTBoard[local_numRows][0] == TTTBoardInfo.TTTBoard[local_numRows][1]) && (TTTBoardInfo.TTTBoard[local_numRows][1] == TTTBoardInfo.TTTBoard[local_numRows][2]))
		{
			return true;
		}
		else {/* Do nothing */ }
	}

	//Check if victory on any column
	for (local_numCols = 0; local_numCols < MAX_ROWS; local_numCols++)
	{
		if ((TTTBoardInfo.TTTBoard[0][local_numCols] == TTTBoardInfo.TTTBoard[1][local_numCols]) && (TTTBoardInfo.TTTBoard[1][local_numCols] == TTTBoardInfo.TTTBoard[2][local_numCols]))
		{
			return true;
		}
		else {/* Do nothing */ }
	}

	//Check if victory on the main diagonal
	if ((TTTBoardInfo.TTTBoard[0][0] == TTTBoardInfo.TTTBoard[1][1]) && (TTTBoardInfo.TTTBoard[1][1] == TTTBoardInfo.TTTBoard[2][2]))
	{
		return true;
	}
	else {/* Do nothing */ }

	//Check if victory on the secondary diagonal
	if ((TTTBoardInfo.TTTBoard[0][2] == TTTBoardInfo.TTTBoard[1][1]) && (TTTBoardInfo.TTTBoard[1][1] == TTTBoardInfo.TTTBoard[2][0]))
	{
		return true;
	}
	else {/* Do nothing */ }

	return false;
}

//Start Again the Game function
//Function that verifies if the player/players wants to restart the game
void TTTStartAgainTheGame(void)
{
	tm_uint32 start_again;
	printf_s("\nDo you want to start again?\n0 -> No, 1-> Yes\n");
	scanf_s("%d", &start_again);
	if ((start_again != 0) && (start_again != 1))
	{
		printf_s("\nInvalid input!\nTry again!");
		TTTStartAgainTheGame();
	}
	else if (start_again == 0)
	{
		printf_s("\nThank you for playing!");
	}
	else
	{
		TTTStartGame();
	}
}