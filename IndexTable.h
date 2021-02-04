#ifndef DB_LAB1_INDEXTABLE_H
#define DB_LAB1_INDEXTABLE_H
#define SIZE 1000
#define INDEXES_FILE "Indexes.bin"
#include <stdio.h>
#include "Developers.h"
#include <stdlib.h>

typedef struct {
    int key_id;
    int address;
    int isDeleted;
} indexAddress;

extern indexAddress indexTable[SIZE];
extern int deletedDevelopersCount;

void readIndexTable(); // read from Indexes.bin to indexesAddress variable
void rewriteIndexTable();   // write from  indexesAddress variable to Indexes.bin
void sortIndexTable(); // sorts indexTable by key_id
int getAddress(int key_id); // get address by key_id
void deleteFromIndexTable(int key_id);
void setNewAddress();
int binarySearch(indexAddress arr[SIZE], int l, int r, int x);
#endif //DB_LAB1_INDEXTABLE_H
