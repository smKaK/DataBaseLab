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
} indexAddress;

extern indexAddress indexTable[SIZE];

void readIndexTable(); // read from Indexes.bin to indexesAddress variable
void rewriteIndexTable();   // write from  indexesAddress variable to Indexes.bin
void sortIndexTable(); // sorts indexTable by key_id
int getAddress(int key_id);
void deleteFromIndexTable(int key_id);
void setNewAddress();

#endif //DB_LAB1_INDEXTABLE_H
