/**
*	Function:	Create chinese chess game.
*	Author:		ko12
*	Start Time:	3/25/2015
*	End Time:	3/30/2015
*/

#include <windows.h>
#include <strsafe.h>
#include "const.h"
#include "chess.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Entry
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT(APP_NAME);			// Application name
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program must run on Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, 
		TEXT(WINDOW_NAME), 
		WS_OVERLAPPEDWINDOW,
		WINDOW_X, 
		WINDOW_Y, 
		WINDOW_WIDTH, 
		WINDOW_HEIGHT,
		NULL, 
		NULL, 
		hInstance, 
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

// draw angle line
// if flag is equal to
//		0		-- write all directed angle line
//		1		-- write left angle line
//		2		-- write right angle line
//		others	-- don't write angle line
void drawAngleLine(HDC hdc, int posX, int posY, int flag)
{
	if (flag == 0 || flag == 1)
	{
		//left top
		MoveToEx(hdc, posX - ELEMENT_X / ANGLE_LINE_SPACE_DEVIDE, posY - (ELEMENT_Y / ANGLE_LINE_LENGTH_DEVIDE + ELEMENT_Y / ANGLE_LINE_SPACE_DEVIDE), NULL);
		LineTo(hdc, posX - ELEMENT_X / ANGLE_LINE_SPACE_DEVIDE, posY - ELEMENT_Y / ANGLE_LINE_SPACE_DEVIDE);
		LineTo(hdc, posX - (ELEMENT_Y / ANGLE_LINE_LENGTH_DEVIDE + ELEMENT_Y / ANGLE_LINE_SPACE_DEVIDE), posY - ELEMENT_Y / ANGLE_LINE_SPACE_DEVIDE);
		//left bottom
		MoveToEx(hdc, posX - ELEMENT_X / ANGLE_LINE_SPACE_DEVIDE, posY + (ELEMENT_Y / ANGLE_LINE_LENGTH_DEVIDE + ELEMENT_Y / ANGLE_LINE_SPACE_DEVIDE), NULL);
		LineTo(hdc, posX - ELEMENT_X / ANGLE_LINE_SPACE_DEVIDE, posY + ELEMENT_Y / ANGLE_LINE_SPACE_DEVIDE);
		LineTo(hdc, posX - (ELEMENT_Y / ANGLE_LINE_LENGTH_DEVIDE + ELEMENT_Y / ANGLE_LINE_SPACE_DEVIDE), posY + ELEMENT_Y / ANGLE_LINE_SPACE_DEVIDE);
	}
	if (flag == 0 || flag == 2)
	{
		//right top
		MoveToEx(hdc, posX + ELEMENT_X / ANGLE_LINE_SPACE_DEVIDE, posY - (ELEMENT_Y / ANGLE_LINE_LENGTH_DEVIDE + ELEMENT_Y / ANGLE_LINE_SPACE_DEVIDE), NULL);
		LineTo(hdc, posX + ELEMENT_X / ANGLE_LINE_SPACE_DEVIDE, posY - ELEMENT_Y / ANGLE_LINE_SPACE_DEVIDE);
		LineTo(hdc, posX + (ELEMENT_Y / ANGLE_LINE_LENGTH_DEVIDE + ELEMENT_Y / ANGLE_LINE_SPACE_DEVIDE), posY - ELEMENT_Y / ANGLE_LINE_SPACE_DEVIDE);
		//right bottom
		MoveToEx(hdc, posX + ELEMENT_X / ANGLE_LINE_SPACE_DEVIDE, posY + (ELEMENT_Y / ANGLE_LINE_LENGTH_DEVIDE + ELEMENT_Y / ANGLE_LINE_SPACE_DEVIDE), NULL);
		LineTo(hdc, posX + ELEMENT_X / ANGLE_LINE_SPACE_DEVIDE, posY + ELEMENT_Y / ANGLE_LINE_SPACE_DEVIDE);
		LineTo(hdc, posX + (ELEMENT_Y / ANGLE_LINE_LENGTH_DEVIDE + ELEMENT_Y / ANGLE_LINE_SPACE_DEVIDE), posY + ELEMENT_Y / ANGLE_LINE_SPACE_DEVIDE);
	}
}

// Draw board
void drawBoard(HDC hdc)
{
	int i;

	//draw X-scale lines
	for (i = 0; i < NODE_Y_SCALE_COUNT; i ++)
	{
		MoveToEx(hdc, BOARD_X, BOARD_Y + i * ELEMENT_Y, NULL);
		LineTo(hdc, BOARD_END_X, BOARD_Y + i * ELEMENT_Y);
	}

	//draw Y-scale lines
	MoveToEx(hdc, BOARD_X, BOARD_Y, NULL);
	LineTo(hdc, BOARD_X, BOARD_END_Y);
	for (i = 1; i < NODE_X_SCALE_COUNT - 1; i ++)
	{
		MoveToEx(hdc, BOARD_X + i * ELEMENT_X, BOARD_Y, NULL);
		LineTo(hdc, BOARD_X + i * ELEMENT_X, BOARD_Y + ELEMENT_Y * (NODE_Y_SCALE_COUNT / 2 - 1));
		MoveToEx(hdc, BOARD_X + i * ELEMENT_X, BOARD_Y + ELEMENT_Y * NODE_Y_SCALE_COUNT / 2, NULL);
		LineTo(hdc, BOARD_X + i * ELEMENT_X, BOARD_END_Y);
	}
	MoveToEx(hdc, BOARD_END_X, BOARD_Y, NULL);
	LineTo(hdc, BOARD_END_X, BOARD_END_Y);

	//draw crosswire
	MoveToEx(hdc, BOARD_X + ELEMENT_X * (NODE_X_SCALE_COUNT / 2 - 1), BOARD_Y, NULL);
	LineTo(hdc, BOARD_X + ELEMENT_X * (NODE_X_SCALE_COUNT / 2 + 1), BOARD_Y + ELEMENT_Y * 2);
	MoveToEx(hdc, BOARD_X + ELEMENT_X * (NODE_X_SCALE_COUNT / 2 + 1), BOARD_Y, NULL);
	LineTo(hdc, BOARD_X + ELEMENT_X * (NODE_X_SCALE_COUNT / 2 - 1), BOARD_Y + ELEMENT_Y * 2);

	MoveToEx(hdc, BOARD_END_X - ELEMENT_X * (NODE_X_SCALE_COUNT / 2 - 1), BOARD_END_Y, NULL);
	LineTo(hdc, BOARD_END_X - ELEMENT_X * (NODE_X_SCALE_COUNT / 2 + 1), BOARD_END_Y - ELEMENT_Y * 2);
	MoveToEx(hdc, BOARD_END_X - ELEMENT_X * (NODE_X_SCALE_COUNT / 2 + 1), BOARD_END_Y, NULL);
	LineTo(hdc, BOARD_END_X - ELEMENT_X * (NODE_X_SCALE_COUNT / 2 - 1), BOARD_END_Y - ELEMENT_Y * 2);

	//draw angle line
	drawAngleLine(hdc, BOARD_X + 0 * 2 * ELEMENT_X, BOARD_Y + 3 * ELEMENT_Y, 2);
	drawAngleLine(hdc, BOARD_X + 0 * 2 * ELEMENT_X, BOARD_Y + 6 * ELEMENT_Y, 2);
	drawAngleLine(hdc, BOARD_X + 4 * 2 * ELEMENT_X, BOARD_Y + 3 * ELEMENT_Y, 1);
	drawAngleLine(hdc, BOARD_X + 4 * 2 * ELEMENT_X, BOARD_Y + 6 * ELEMENT_Y, 1);
	for (i = 1; i <= 3; i ++)
	{
		drawAngleLine(hdc, BOARD_X + i * 2 * ELEMENT_X, BOARD_Y + 3 * ELEMENT_Y, 0);
		drawAngleLine(hdc, BOARD_X + i * 2 * ELEMENT_X, BOARD_Y + 6 * ELEMENT_Y, 0);
	}
	drawAngleLine(hdc, BOARD_X + 1 * ELEMENT_X, BOARD_Y + 2 * ELEMENT_Y, 0);
	drawAngleLine(hdc, BOARD_X + 7 * ELEMENT_X, BOARD_Y + 2 * ELEMENT_Y, 0);
	drawAngleLine(hdc, BOARD_X + 1 * ELEMENT_X, BOARD_Y + 7 * ELEMENT_Y, 0);
	drawAngleLine(hdc, BOARD_X + 7 * ELEMENT_X, BOARD_Y + 7 * ELEMENT_Y, 0);
}

// Draw all chess on board
void drawChess(HDC hdc, Board *board)
{
	int i, j;
	PTCHAR str;
	size_t size;
	//HPEN hPenOld, hPen1, hPen2;
	UINT uint;
	HFONT hFontOld, hFont;

	//hPen1 = CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	//hPen2 = CreatePen(PS_DOT, 1, RGB(0, 0, 255));
	SetBkColor(hdc, CHESS_BK_RGB_DEFAULT);
	SetBkMode(hdc, OPAQUE);
	//SetROP2(hdc, R2_NOT);

	hFont = CreateFont(30,0,0,0,FW_HEAVY,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Impact"));
	hFontOld = (HFONT)SelectObject(hdc, hFont);

	uint = GetTextAlign(hdc);
	SetTextAlign(hdc, VTA_BASELINE | TA_CENTER);

	for (i = 0; i < NODE_Y_SCALE_COUNT; i ++)
	{
		for (j = 0; j < NODE_X_SCALE_COUNT; j ++)
		{
			if (board->map[ i ][ j ] >= soldier1 && board->map[ i ][ j ] <= general1)
			{
				//hPenOld = (HPEN)SelectObject(hdc, hPen1);
				SetBkColor(hdc, CHESS_BK_RGB_1);
			}
			else if (board->map[ i ][ j ] >= soldier2 && board->map[ i ][ j ] <= general2)
			{
				//hPenOld = (HPEN)SelectObject(hdc, hPen2);
				SetBkColor(hdc, CHESS_BK_RGB_2);
			}
			else
			{
				continue;
			}
			str = typeToName[ board->map[ i ][ j ] ];
			StringCchLength(str, 3, &size);
			TextOut(hdc, BOARD_X + ((!board->reverse) ? j : (NODE_X_SCALE_COUNT - 1 - j)) * ELEMENT_X, BOARD_Y + ((!board->reverse) ? i : (NODE_Y_SCALE_COUNT - 1 - i)) * ELEMENT_Y, str, size);
		}
	}

	SelectObject(hdc, hFontOld);
	SetTextAlign(hdc, uint);
	//SelectObject(hdc, hPenOld);
}

void drawOwnerInfo(HDC hdc, Board *board, int x, int y)
{
	TCHAR strOwner[ 20 ], strStep[ 20 ];
	UINT uint;
	size_t sizeOwner, sizeStep;

	SetBkColor(hdc, (!board->owner) ? CHESS_BK_RGB_1 : CHESS_BK_RGB_2);

	StringCchPrintf(strOwner, 20, (!board->owner) ? TEXT("玩家：1") : TEXT("玩家：2"));
	StringCchLength(strOwner, 20, &sizeOwner);
	StringCchPrintf(strStep, 20, (!board->indexPos) ? TEXT("选起点") : TEXT("选终点"));
	StringCchLength(strStep, 20, &sizeStep);
	uint = GetTextAlign(hdc);
	SetTextAlign(hdc, TA_RIGHT);
	TextOut(hdc, x, y, strOwner, sizeOwner);
	TextOut(hdc, x, y + 30, strStep, sizeStep);
	SetTextAlign(hdc, uint);


}

void mouseClick(Board *board, int mouseX, int mouseY)
{
	Position pos;

	pos.y = (mouseX - (BOARD_X - ELEMENT_X / 2)) / ELEMENT_X;
	pos.x = (mouseY - (BOARD_Y - ELEMENT_Y / 2)) / ELEMENT_Y;
	if (pos.x >= 0 && pos.x < NODE_Y_SCALE_COUNT && pos.y >= 0 && pos.y < NODE_X_SCALE_COUNT)
	{
		// reverse board
		if (board->reverse)
		{
			pos.x = NODE_Y_SCALE_COUNT - 1 - pos.x;
			pos.y = NODE_X_SCALE_COUNT - 1 - pos.y;
		}

		BoardSelect(board, pos);
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int mouseX, mouseY;

	static Board *board;
	static int xClient, yClient;

	switch (message)
	{
	case WM_CREATE:
		if (BoardInit(&board))
		{
			MessageBox(hwnd, TEXT("游戏初始化错误"), TEXT("错误"), MB_OK);
			DestroyWindow(hwnd);
		}
		return 0;

	case WM_SIZE:
		xClient		= LOWORD(lParam);
		yClient		= HIWORD(lParam);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		drawBoard(hdc);
		drawChess(hdc, board);
		drawOwnerInfo(hdc, board, xClient, 0);
		EndPaint(hwnd, &ps);
		if (board->winner)
		{
			MessageBox(hwnd, (board->winner == 1) ? TEXT("玩家1胜利！！") : TEXT("玩家2胜利！！"), TEXT("结束"), MB_OK);
			DestroyWindow(hwnd);
		}
		return 0;

	case WM_LBUTTONDOWN:
		mouseX = LOWORD(lParam);
		mouseY = HIWORD(lParam);
		mouseClick(board, mouseX, mouseY);
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	case WM_DESTROY:
		if (board)
			free(board);
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}