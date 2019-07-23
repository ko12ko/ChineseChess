
#ifndef _COMMON_H
#define _COMMON_H

typedef struct {
	int x;
	int y;
} Position;

typedef enum {
	space,
	soldier1, cannon1, car1, horse1, elephant1, defender1, general1,
	soldier2, cannon2, car2, horse2, elephant2, defender2, general2
} ChessType;

#endif
