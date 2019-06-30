
#include "record.h"
#include "stdlib.h"

static unsigned int *encodeBoard(unsigned int *board, unsigned int boardSize) {
	unsigned int *data = (unsigned int *)malloc(RECORD_DATA_LENGTH * sizeof(unsigned int));
	int k = 0;
	unsigned int value = 0;
	for (int i = 0; i < boardSize; i++) {
		if (k % 2 == 0) {
			value = board[i] << 4;
		}
		else {
			value = value | (board[i] & 0x00ff);
		}
		data[k / 2] = value;
		k++;
	}
	return data;
}

static unsigned int *decodeBoard(unsigned int *data) {
	unsigned int *board = (unsigned int *)malloc(RECORD_DATA_LENGTH * 2 * sizeof(unsigned int));
	for (int i = 0; i < RECORD_DATA_LENGTH; i++) {
		board[i * 2] = data[i] >> 4;
		board[i * 2 + 1] = data[i] & 0x00ff;
	}
	return board;
}

int record(Record *record, unsigned int *board, unsigned int boardSize, int owner) {
	Record *newRecord = (Record*)malloc(sizeof(Record));
	newRecord->data = encodeBoard(board, boardSize);
	newRecord->owner = owner;
	newRecord->previous = record;
	newRecord->next = NULL;
	newRecord->nextCount = 0;

	record->next = (Record **)realloc(record->next, (record->nextCount + 1) * sizeof(Record *));
	record->next[record->nextCount] = newRecord;
	record->nextCount++;
}

int restore(Record *record, unsigned int **board) {
	*board = decodeBoard(record->data);
}

int saveRecord(Record *record, char *filename) {

}

int loadRecord(Record *record, char *filename) {

}
