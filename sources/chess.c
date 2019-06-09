/**
*	Function:	Chinese Chess
*	Author:		ko12
*	Start Time:	3/25/2015
*	End Time:	3/30/2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "chess.h"

// Chess type map to chess name.
const PTCHAR typeToName[ 15 ] = {
	TEXT(" "),
	TEXT("兵"),
	TEXT("砲"),
	TEXT("車"),
	TEXT("馬"),
	TEXT("相"),
	TEXT("仕"),
	TEXT("帅"),
	TEXT("卒"),
	TEXT("炮"),
	TEXT("车"),
	TEXT("马"),
	TEXT("象"),
	TEXT("士"),
	TEXT("将")
};

// Initialize game
// Return value
//		== 0, success
//		!= 0, failure
int BoardInit(Board **board)
{
	*board = (Board *)malloc(sizeof(Board));
	if (!*board)
		return 1;

	memset((*board)->map, 0, sizeof((*board)->map));

	(*board)->map[ 3 ][ 0 ] = (*board)->map[ 3 ][ 2 ] = (*board)->map[ 3 ][ 4 ] = (*board)->map[ 3 ][ 6 ] = (*board)->map[ 3 ][ 8 ] = soldier1;
	(*board)->map[ 2 ][ 1 ] = (*board)->map[ 2 ][ 7 ] = cannon1;
	(*board)->map[ 0 ][ 0 ] = (*board)->map[ 0 ][ 8 ] = car1;
	(*board)->map[ 0 ][ 1 ] = (*board)->map[ 0 ][ 7 ] = horse1;
	(*board)->map[ 0 ][ 2 ] = (*board)->map[ 0 ][ 6 ] = elephant1;
	(*board)->map[ 0 ][ 3 ] = (*board)->map[ 0 ][ 5 ] = defender1;
	(*board)->map[ 0 ][ 4 ] = general1;

	(*board)->map[ 6 ][ 0 ] = (*board)->map[ 6 ][ 2 ] = (*board)->map[ 6 ][ 4 ] = (*board)->map[ 6 ][ 6 ] = (*board)->map[ 6 ][ 8 ] = soldier2;
	(*board)->map[ 7 ][ 1 ] = (*board)->map[ 7 ][ 7 ] = cannon2;
	(*board)->map[ 9 ][ 0 ] = (*board)->map[ 9 ][ 8 ] = car2;
	(*board)->map[ 9 ][ 1 ] = (*board)->map[ 9 ][ 7 ] = horse2;
	(*board)->map[ 9 ][ 2 ] = (*board)->map[ 9 ][ 6 ] = elephant2;
	(*board)->map[ 9 ][ 3 ] = (*board)->map[ 9 ][ 5 ] = defender2;
	(*board)->map[ 9 ][ 4 ] = general2;

	(*board)->winner	= 0;
	(*board)->owner		= 0;
	(*board)->indexPos	= 0;
	(*board)->reverse	= BOARD_REVERSE;
	return 0;
}

int BoardIsFriend(Board *board, ChessType chess)
{
	return (!board->owner) ? (chess >= soldier1 && chess <= general1) : (chess >= soldier2 && chess <= general2);
}

int BoardIsHome(Board *board, Position pos)
{
	return (!board->owner) ? (pos.x >= 0 && pos.x <= 4) : (pos.x >= 5 && pos.x <= 9);
}

int BoardIsInHomeDefender(Board *board, Position pos)
{
	Position temp;
	temp.x = (!board->owner) ? 1 : 8;
	temp.y = 4;
	return (pos.x == temp.x && pos.y == temp.y) || (abs(pos.x - temp.x) == 1 && abs(pos.y - temp.y) == 1);
}

int BoardIsInPalace(Board *board, Position pos)
{
	int top, left, bottom, right;
	top		= (!board->owner) ? 0 : 7;
	left	= 3;
	bottom	= (!board->owner) ? 2 : 9;
	right	= 5;
	return pos.x >= top && pos.x <= bottom && pos.y >= left && pos.y <= right;
}

int BoardFaceToFace(Board *board, Position pos)
{
	int i;

	if (!board->owner)
	{
		i = pos.x + 1;
		while (i <= 9)
		{
			if (board->map[ i ][ pos.y ] == general2)
			{
				return 1;
			}
			if (board->map[ i ][ pos.y ] != space)
			{
				return 0;
			}
			i ++;
		}
		return 0;
	}
	else
	{
		i = pos.x - 1;
		while (i >= 0)
		{
			if (board->map[ i ][ pos.y ] == general1)
			{
				return 1;
			}
			if (board->map[ i ][ pos.y ] != space)
			{
				return 0;
			}
			i ++;
		}
		return 0;
	}
}

// Move chess
// Return value
//		== 0, success
//		!= 0, failure
int BoardMoveChess(Board *board, Position startPos, Position endPos)
{
	int i;
	ChessType startChess, endChess;
	int temp, count;
	
	startChess = board->map[ startPos.x ][ startPos.y ];
	endChess = board->map[ endPos.x ][ endPos.y ];

	// judge startPos. The startPos must be owner's chess.
	if (startChess == space || !BoardIsFriend(board, board->map[ startPos.x ][ startPos.y ]))
	{
		return 1;
	}

	// judge endPos. The chess must can move to endPos.
	if ((endPos.x == startPos.x && endPos.y == startPos.y) || BoardIsFriend(board, board->map[ endPos.x ][ endPos.y ]))
	{
		return 1;
	}
	switch (startChess)
	{
	case soldier1:
		// go ahead
		if (endPos.y == startPos.y && endPos.x - startPos.x == 1)
		{
			board->map[ endPos.x ][ endPos.y ] = board->map[ startPos.x ][ startPos.y ];
			board->map[ startPos.x ][ startPos.y ] = space;
			return 0;
		}
		// left or right(must cross the river)
		if (startPos.x > 4 && endPos.x == startPos.x && abs(endPos.y - startPos.y) == 1)
		{
			board->map[ endPos.x ][ endPos.y ] = board->map[ startPos.x ][ startPos.y ];
			board->map[ startPos.x ][ startPos.y ] = space;
			return 0;
		}
		return 1;
	case soldier2:
		// go ahead
		if (endPos.y == startPos.y && endPos.x - startPos.x == -1)
		{
			board->map[ endPos.x ][ endPos.y ] = board->map[ startPos.x ][ startPos.y ];
			board->map[ startPos.x ][ startPos.y ] = space;
			return 0;
		}
		// left or right(must cross the river)
		if (startPos.x < 5 && endPos.x == startPos.x && abs(endPos.y - startPos.y) == 1)
		{
			board->map[ endPos.x ][ endPos.y ] = board->map[ startPos.x ][ startPos.y ];
			board->map[ startPos.x ][ startPos.y ] = space;
			return 0;
		}
		return 1;
	case cannon1:
	case cannon2:
		if (endPos.x == startPos.x || endPos.y == startPos.y)
		{
			if (endPos.x == startPos.x)
			{
				count = 0;
				temp = max(startPos.y, endPos.y);
				for (i = min(startPos.y, endPos.y) + 1; i < temp; i ++)
					if (board->map[ endPos.x ][ i ] != space)
						count ++;
				if (count > 1 || (count == 0 && board->map[ endPos.x ][ endPos.y ] != space) || (count == 1 && board->map[ endPos.x ][ endPos.y ] == space))
					return 1;
				board->map[ endPos.x ][ endPos.y ] = board->map[ startPos.x ][ startPos.y ];
				board->map[ startPos.x ][ startPos.y ] = space;
			}
			else
			{
				count = 0;
				temp = max(startPos.x, endPos.x);
				for (i = min(startPos.x, endPos.x) + 1; i < temp; i ++)
					if (board->map[ i ][ endPos.y ] != space)
						count ++;
				if (count > 1 || (count == 0 && board->map[ endPos.x ][ endPos.y ] != space) || (count == 1 && board->map[ endPos.x ][ endPos.y ] == space))
					return 1;
				board->map[ endPos.x ][ endPos.y ] = board->map[ startPos.x ][ startPos.y ];
				board->map[ startPos.x ][ startPos.y ] = space;
			}
			return 0;
		}
		return 1;
	case car1:
	case car2:
		if (endPos.x == startPos.x || endPos.y == startPos.y)
		{
			if (endPos.x == startPos.x)
			{
				count = 0;
				temp = max(startPos.y, endPos.y);
				for (i = min(startPos.y, endPos.y) + 1; i < temp; i ++)
					if (board->map[ endPos.x ][ i ] != space)
						count ++;
				if (count >= 1)
					return 1;
				board->map[ endPos.x ][ endPos.y ] = board->map[ startPos.x ][ startPos.y ];
				board->map[ startPos.x ][ startPos.y ] = space;
			}
			else
			{
				count = 0;
				temp = max(startPos.x, endPos.x);
				for (i = min(startPos.x, endPos.x) + 1; i < temp; i ++)
					if (board->map[ i ][ endPos.y ] != space)
						count ++;
				if (count >= 1)
					return 1;
				board->map[ endPos.x ][ endPos.y ] = board->map[ startPos.x ][ startPos.y ];
				board->map[ startPos.x ][ startPos.y ] = space;
			}
			return 0;
		}
		return 1;
	case horse1:
	case horse2:
		// run on sun path
		if ((abs(endPos.x - startPos.x) == 2 && abs(endPos.y - startPos.y) == 1)
			|| (abs(endPos.x - startPos.x) == 1 && abs(endPos.y - startPos.y) == 2))
		{
			// judge whther or not have a barrage on sun path
			if (endPos.x - startPos.x == 2 && board->map[ startPos.x + 1 ][ startPos.y ] != space)
				return 1;
			if (endPos.x - startPos.x == -2 && board->map[ startPos.x - 1 ][ startPos.y ] != space)
				return 1;
			if (endPos.y - startPos.y == 2 && board->map[ startPos.x ][ startPos.y + 1 ] != space)
				return 1;
			if (endPos.y - startPos.y == -2 && board->map[ startPos.x ][ startPos.y - 1 ] != space)
				return 1;
			// can go now
			board->map[ endPos.x ][ endPos.y ] = board->map[ startPos.x ][ startPos.y ];
			board->map[ startPos.x ][ startPos.y ] = space;
			return 0;
		}
		return 1;
	case elephant1:
	case elephant2:
		if (!BoardIsHome(board, endPos))
			return 1;
		if (abs(endPos.x - startPos.x) == 2 
			&& abs(endPos.y - startPos.y) == 2 
			&& board->map[ (endPos.x + startPos.x) / 2 ][ (endPos.y + startPos.y) / 2 ] == space)
		{
			board->map[ endPos.x ][ endPos.y ] = board->map[ startPos.x ][ startPos.y ];
			board->map[ startPos.x ][ startPos.y ] = space;
			return 0;
		}
		return 1;
	case defender1:
	case defender2:
		if (BoardIsInHomeDefender(board, endPos) 
			&& (abs(endPos.x - startPos.x) == 1 && abs(endPos.y - startPos.y) == 1))
		{
			board->map[ endPos.x ][ endPos.y ] = board->map[ startPos.x ][ startPos.y ];
			board->map[ startPos.x ][ startPos.y ] = space;
			return 0;
		}
		return 1;
	case general1:
	case general2:
		// General face to face, can eat ecah other
		if ((endChess == ((!board->owner) ? general2 : general1)) && (endPos.y == startPos.y))
		{
			temp = max(endPos.x, startPos.x);
			for (i = min(endPos.x, startPos.x) + 1; i < temp; i ++)
			{
				if (board->map[ i ][ endPos.y ] != space)
					break;
			}
			if (i < temp)
				return 1;
			board->map[ endPos.x ][ endPos.y ] = board->map[ startPos.x ][ startPos.y ];
			board->map[ startPos.x ][ startPos.y ] = space;
			return 0;
		}
		// General can go in palace
		if (BoardIsInPalace(board, endPos) 
			&& ((endPos.x == startPos.x) && (abs(endPos.y - startPos.y) == 1) || ((endPos.y == startPos.y) && (abs(endPos.x - startPos.x) == 1))))
		{
			if ((endChess == ((!board->owner) ? general2 : general1)) && (endPos.y == startPos.y))
			{
				temp = max(endPos.x, startPos.x);
				for (i = min(endPos.x, startPos.x) + 1; i < temp; i ++)
				{
					if (board->map[ i ][ endPos.y ] != space)
						break;
				}
				if (i < temp)
					return 1;
			}
			board->map[ endPos.x ][ endPos.y ] = board->map[ startPos.x ][ startPos.y ];
			board->map[ startPos.x ][ startPos.y ] = space;
			return 0;
		}
		return 1;
	}
}

// Choose a position
void BoardSelect(Board *board, Position pos)
{
	ChessType chess;
	int flag;

	// Out of board
	if (pos.x < 0 || pos.x > NODE_Y_SCALE_COUNT || pos.y < 0 || pos.y > NODE_X_SCALE_COUNT)
		return;

	if (!board->indexPos)			// startPos
	{
		chess = board->map[ pos.x ][ pos.y ];
		if (chess == space || ((!board->owner) ? (chess < soldier1 || chess > general1) : (chess < soldier2 || chess > general2)))
		{
			return ;
		}
		board->movePos[ board->indexPos ] = pos;
		board->indexPos ^= 1;
	}
	else							// endPos
	{
		flag = 0;
		board->movePos[ board->indexPos ] = pos;
		// Whether or not want to eat general
		if (board->map[ board->movePos[ 1 ].x ][ board->movePos[ 1 ].y ] == general1)
		{
			flag = 2;
		}
		else if (board->map[ board->movePos[ 1 ].x ][ board->movePos[ 1 ].y ] == general2)
		{
			flag = 1;
		}
		// move chess
		if (!BoardMoveChess(board, board->movePos[ 0 ], board->movePos[ 1 ]))
		{
			if (flag == 1)			// player 1 is winner
			{
				board->winner = 1;
			}
			else if (flag == 2)		// player 2 is winner
			{
				board->winner = 2;
			}
			board->owner ^= 1;		// Change owner
		}
		board->indexPos ^= 1;		// Change step
	}
}

// Save game
// return value
//		== 0, success
//		!= 0, failure
int BoardSave(Board *board, char szFileName[])
{
	FILE *file;
	
	fopen_s(&file, szFileName, "wb");				// modify by jishichao on 2017.10.15
	if (!file)
	{
		return 1;
	}
	fwrite(board->map, sizeof(ChessType), NODE_Y_SCALE_COUNT * NODE_X_SCALE_COUNT, file);
	fclose(file);
	return 0;
}