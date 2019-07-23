

#ifndef _WINDOW_H
#define _WINDOW_H

#include <windows.h>
#include "common.h"
#include "event.h"

typedef struct {
	HWND hwnd;
	int isError;

	unsigned int *board;
	int owner;
	int winner;

	int reverse;
	int indexPos;
	Position movePos[2];
} Window;

int WindowInit(Window **window, unsigned int *board, int owner, int winner, int reverse);
int WINAPI WindowCreate(Window *window, HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow);
void WindowRunLoop();
void WindowEnd(Window *);

#endif
