#include "IndexTable.h"

indexAddress indexTable[SIZE];
int deletedDevelopersCount = 0;

void readIndexTable()
{
    FILE* indexesFile = fopen(INDEXES_FILE, "rb+");
    for (int i = 0; i < developersCount; i++) {
        fread(&indexTable[i].key_id, sizeof(int), 1, indexesFile);
        fread(&indexTable[i].address, sizeof(int), 1, indexesFile);
        fread(&indexTable[i].isDeleted, sizeof(int), 1, indexesFile);
    }
    fclose(indexesFile);
}

void rewriteIndexTable()
{
    FILE* indexesFile = fopen(INDEXES_FILE, "wb+");
    for (int i = 0; i < developersCount; i++) {
        fwrite(&indexTable[i].key_id, sizeof(int), 1, indexesFile);
        fwrite(&indexTable[i].address, sizeof(int), 1, indexesFile);
        fwrite(&indexTable[i].isDeleted, sizeof(int), 1, indexesFile);
    }
    fclose(indexesFile);
}

int cmpfunc(const void * a, const void * b) {
    return (((indexAddress *)a)->key_id  - ((indexAddress *)b)->key_id );
}

void sortIndexTable()
{
    qsort(indexTable, developersCount, sizeof(indexAddress), cmpfunc);
}

int binarySearch(indexAddress arr[SIZE], int l, int r, int x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;
       if (arr[mid].key_id == x)
            return mid;

         if (arr[mid].key_id > x)
            return binarySearch(arr, l, mid - 1, x);
        return binarySearch(arr, mid + 1, r, x);
    }
     return -1;
}

int getAddress(int key_id)
{
    int i = binarySearch(indexTable, 0,developersCount, key_id);
    if(i != -1 && indexTable[i].isDeleted == 0) {
        return indexTable[i].address;
    } else
    {
        return -1;
    }
}

void deleteFromIndexTable(int key_id)
{
    for (int i = 0; i < developersCount; i++) {
        if (indexTable[i].key_id == key_id) {
            indexTable[i].key_id = -1;
            indexTable[i].address = -1;
            indexTable[i].isDeleted = 0;
            return;
        }
    }
}
