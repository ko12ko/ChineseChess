
#ifndef _RECORD_H
#define _RECORD_H

#define RECORD_DATA_LENGTH 45

typedef struct Record {
	unsigned int *data;
	struct Record *previous;
	struct Record **next;
	int nextCount;
	int owner;
} Record;

int RecordInit(Record **, unsigned int *, unsigned int, int);
int RecordAdd(Record *, unsigned int *, unsigned int, int);
int RecordRestore(Record *, unsigned int **);
int RecordSave(Record *, const char *);
int RecordLoad(Record *, const char *);
void RecordEnd(Record *);

#endif