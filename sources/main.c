
#include "game.h"
#include "event.h"

static Game *game;

void updateWindow() {
	game->window->board = (unsigned int *)game->board->map;
	game->window->owner = game->board->owner;
	game->window->winner = game->board->winner;
}

int eventMoveChess(Position startPos, Position endPos) {
	int status = BoardMoveChess(game->board, startPos, endPos);
	updateWindow();
	return status;
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