
#include "game.h"
#include "event.h"
#include <stdio.h>

static Game *game;

void updateWindow() {
	game->window->board = (unsigned int *)game->board->map;
	game->window->owner = game->board->owner;
	game->window->winner = game->board->winner;
}

void updateBoard() {
	unsigned int *boardMap;
	RecordRestore(game->record, &boardMap);
	memcpy(game->board->map, boardMap, sizeof(unsigned int) * NODE_X_SCALE_COUNT * NODE_Y_SCALE_COUNT);
	game->board->owner = game->record->owner;
}

int eventMoveChess(Position startPos, Position endPos) {
	int status = BoardMoveChess(game->board, startPos, endPos);
	RecordAdd(game->record, (unsigned int*)game->board->map, NODE_X_SCALE_COUNT * NODE_Y_SCALE_COUNT, game->board->owner);
	game->record = game->record->next[game->record->nextCount - 1];

	//static int i = 0;
	//char filename[30];
	//sprintf_s(filename, 29, "%d.chess", i++);
	//RecordSave(game->record, filename);

	//RecordLoad(game->record, "1.chess");
	//updateBoard();

	updateWindow();
	return status;
}

void eventLoad() {
	RecordLoad(game->record, "load.chess");
	updateBoard();
}

void eventGameEnd() {
	GameEnd(game);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {

	int isError = GameInit(&game);
	game->window->isError = isError;

	if (WindowCreate(game->window, hInstance, hPrevInstance, szCmdLine, iCmdShow) != 0) {
		return 1;
	}

	GameRun();
	return 0;
}