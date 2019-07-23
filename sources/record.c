
#include "record.h"
#include <stdio.h>
#include <stdlib.h>

static unsigned char *encodeBoard(unsigned int *board, unsigned int boardSize) {
	unsigned char *data = (unsigned char *)malloc(RECORD_DATA_LENGTH * sizeof(unsigned char));
	int k = 0;
	unsigned char value = 0;
	for (unsigned int i = 0; i < boardSize; i++) {
		if (k % 2 == 0) {
			value = (unsigned char)board[i] << 4;
		}
		else {
			value = value | ((unsigned char)board[i] & 0x0f);
			data[k / 2] = value;
		}
		k++;
	}
	return data;
}

static unsigned int *decodeBoard(unsigned char *data) {
	unsigned int *board = (unsigned int *)malloc(RECORD_DATA_LENGTH * 2 * sizeof(unsigned int));
	for (unsigned int i = 0; i < RECORD_DATA_LENGTH; i++) {
		board[i * 2] = data[i] >> 4;
		board[i * 2 + 1] = data[i] & 0x0f;
	}
	return board;
}

static Record* buildRecord(unsigned int *board, unsigned int boardSize, int owner) {
	Record *record = (Record*)malloc(sizeof(Record));
	record->data = encodeBoard(board, boardSize);
	record->owner = owner;
	record->previous = NULL;
	record->next = NULL;
	record->nextCount = 0;
	return record;
}

int RecordInit(Record **record, unsigned int *board, unsigned int boardSize, int owner) {
	Record *newRecord = buildRecord(board, boardSize, owner);
	newRecord->previous = newRecord;
	*record = newRecord;
	return 0;
}

int RecordAdd(Record *record, unsigned int *board, unsigned int boardSize, int owner) {
	Record *newRecord;
	int status = RecordInit(&newRecord, board, boardSize, owner);
	if (status != 0) {
		return status;
	}

	record->next = (Record **)realloc(record->next, (record->nextCount + 1) * sizeof(Record *));
	record->next[record->nextCount] = newRecord;
	record->nextCount++;
	return 0;
}

int RecordRestore(Record *record, unsigned int **board) {
	*board = decodeBoard(record->data);
	return 0;
}

int RecordSave(Record *record, const char *filename) {
	FILE *file;
	fopen_s(&file, filename, "w");
	if (file == NULL) {
		return 1;
	}
	fwrite(record->data, sizeof(unsigned char), RECORD_DATA_LENGTH, file);
	fwrite(&record->owner, sizeof(int), 1, file);
	fclose(file);
	return 0;
}

int RecordLoad(Record *record, const char *filename) {
	FILE *file;
	fopen_s(&file, filename, "r");
	if (file == NULL) {
		return 1;
	}
	fread(record->data, sizeof(unsigned char), RECORD_DATA_LENGTH, file);
	fread(&record->owner, sizeof(int), 1, file);
	fclose(file);
	return 0;
}

static freeRecord(Record *record) {
	free(record->data);
	free(record->previous);
	for (int i = 0; i < record->nextCount; i++) {
		freeRecord(record->next[i]);
	}
}

void RecordEnd(Record *record) {
	freeRecord(record);
}
