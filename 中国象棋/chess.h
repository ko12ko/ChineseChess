/**
*	Function:	Chinese Chess
*	Author:		ko12
*	Start Time:	3/25/2015
*	End Time:	3/30/2015
*/

#ifndef _CHESS_H
#define _CHESS_H

#include <windows.h>
#include "const.h"

// Position of the board
typedef struct
{
	int x;
	int y;
}Position;

extern const PTCHAR typeToName[ 15 ];

// Chess type
typedef enum {
	space, 
	soldier1, cannon1, car1, horse1, elephant1, defender1, general1, 
	soldier2, cannon2, car2, horse2, elephant2, defender2, general2
}ChessType;

// Board
typedef struct
{
	ChessType map[ NODE_Y_SCALE_COUNT ][ NODE_X_SCALE_COUNT ];
	int winner;				// Who is winner ? 
							//		0 -- no one
							//		1 -- player 1
							//		2 -- player 2

	int owner;				// Who is owner ?
							//		0 -- player 1
							//		1 -- player 2

	Position movePos[ 2 ];	// Record startPos and endPos
	int indexPos;
	
	int reverse;			// Reverse board
}Board;

int BoardInit(Board **);
int BoardMoveChess(Board *, Position, Position);
void BoardSelect(Board *, Position);
int BoardSave(Board *board, char szFileName[]);


#endif