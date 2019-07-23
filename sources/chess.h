/*
 * Chinese Chess core
 */

#ifndef _CHESS_H
#define _CHESS_H

#include "const.h"
#include "common.h"

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
}Board;

int BoardInit(Board **, int);
int BoardMoveChess(Board *, Position, Position);


#endif