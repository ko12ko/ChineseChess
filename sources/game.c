
#include "game.h"

int GameInit(Game **game) {
	Game *newGame = (Game*)malloc(sizeof(Game));
	int initBoardStatus = BoardInit(&newGame->board, BOARD_REVERSE);
	if (initBoardStatus != 0) {
		return initBoardStatus;
	}

	int initRecordStatus = RecordInit(&newGame->record, (unsigned int*)newGame->board->map, NODE_X_SCALE_COUNT * NODE_Y_SCALE_COUNT, newGame->board->owner);
	if (initRecordStatus != 0) {
		return initRecordStatus;
	}

	int initWindowStatus = WindowInit(&newGame->window, (unsigned int*)newGame->board->map, newGame->board->owner, newGame->board->winner, BOARD_REVERSE);
	if (initWindowStatus != 0) {
		return initWindowStatus;
	}

	*game = newGame;
	return 0;
}

void GameRun() {
	WindowRunLoop();
}

void GameEnd(Game *game) {
	WindowEnd(game->window);
	RecordEnd(game->record);
}
