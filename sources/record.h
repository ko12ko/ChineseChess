
#ifndef _RECORD_H
#define _RECORD_H

#define RECORD_DATA_LENGTH 45

typedef struct {
	unsigned int *data;
	Record *previous;
	Record **next;
	int nextCount;
	int owner;
} Record;


int record(Record *record, unsigned int *board);
int restore(Record *record, unsigned int **board);
int saveRecord(Record *record, char *filename);
int loadRecord(Record *record, char *filename);

#endif