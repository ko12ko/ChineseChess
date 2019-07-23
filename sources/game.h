
/*
 * Game logic
 */

#ifndef _GAME_H
#define _GAME_H

#include "chess.h"
#include "record.h"
#include "const.h"
#include "window.h"

typedef struct {
	Board *board;
	Record *record;
	Window *window;
} Game;

int GameInit(Game **game);
void GameEnd(Game *game);
void GameRun();

#endif