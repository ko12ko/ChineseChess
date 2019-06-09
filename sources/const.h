/*
 * Define constant
 */

#ifndef _CONST_H
#define _CONST_H

/**************************** Can change ***********************************/
// applicaition
#define APP_NAME			"Chinese Chess"

// window
#define WINDOW_NAME			"ÖÐ¹úÏóÆå"
#define WINDOW_X			400
#define WINDOW_Y			100
#define WINDOW_WIDTH		600
#define WINDOW_HEIGHT		600

// board
#define BOARD_X				50
#define BOARD_Y				50
#define NODE_INTERVAL		50

#define BOARD_REVERSE		1

// angle line (pixels = ELEMENT_X / ?)
#define ANGLE_LINE_SPACE_DEVIDE		6
#define ANGLE_LINE_LENGTH_DEVIDE	4

// chess
#define CHESS_BK_RGB_1			RGB(255,0,0)
#define CHESS_BK_RGB_2			RGB(0,255,0)
#define CHESS_BK_RGB_DEFAULT	RGB(0,0,255)

/**************************** Don't change ***********************************/
#define BOARD_WIDTH			(NODE_INTERVAL * (NODE_X_SCALE_COUNT - 1))
#define BOARD_HEIGHT		(NODE_INTERVAL * (NODE_Y_SCALE_COUNT - 1))
#define BOARD_END_X			(BOARD_X + BOARD_WIDTH)
#define BOARD_END_Y			(BOARD_Y + BOARD_HEIGHT)
#define ELEMENT_X			(BOARD_WIDTH / (NODE_X_SCALE_COUNT - 1))
#define ELEMENT_Y			(BOARD_HEIGHT / (NODE_Y_SCALE_COUNT - 1))


#endif