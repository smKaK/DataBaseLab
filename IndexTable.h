#ifndef DB_LAB1_INDEXTABLE_H
#define DB_LAB1_INDEXTABLE_H
#define SIZE 1000

typedef struct {
    int key_id;
    int address;
} indexAddress;

extern indexAddress indexTable[SIZE];

void readIndexTable();
void rewriteIndexTable();
void sortIndexTable();
int getAddress(int key_id);
void deleteFromIndexTable(int key_id);
void setNewAddress();

#endif //DB_LAB1_INDEXTABLE_H
