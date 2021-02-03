#include "DataBase.h"

void InitFiles()
{
    FILE* developersFile_m = fopen(DEVELOPERS_FILE, "wb+");
    fclose(developersFile_m);
    FILE* gamesFile_s = fopen(GAMES_FILE, "wb+");
    fclose(gamesFile_s);
    FILE* indexesFile_i = fopen(INDEXES_FILE, "wb+");
    fclose(indexesFile_i);
 }

void ut_m()
{
    FILE* developersFile = fopen(DEVELOPERS_FILE, "rb+");
    if(developersFile == NULL)
        perror("Error:can't open developers.bin");

    printf("Function: ut_m:\n");

    int key_id, firstGameAddress;
    char companyName[30], country[30];

    for (int i = 0; i < developersCount; i++) {
        fread(&key_id, sizeof(int), 1, developersFile);
        fread(&companyName, sizeof(companyName), 1, developersFile);
        fread(&country, sizeof(country), 1, developersFile);
        fread(&firstGameAddress, sizeof(int), 1, developersFile);
        printf("key id: %d, company name: %s, country: %s, first game address: %d\n",
               key_id, companyName, country, firstGameAddress);
    }
    fclose(developersFile);
}

void ut_i()
{


    FILE* indexesFile = fopen(INDEXES_FILE, "rb+");
    if(indexesFile == NULL)
        perror("Error:can't open Indexes.bin");

    int key_id, address;

    for (int i = 0; i < developersCount; i++) {
        fread(&key_id, sizeof(int), 1, indexesFile);
        fread(&address, sizeof(int), 1, indexesFile);
        printf("key id: %d, address: %d\n",
               key_id, address);
    }
    fclose(indexesFile);
}

void insert_m(Developer* developer)
{
    for (int i = 0; i < developersCount; i++) {
        if (indexTable[i].key_id == developer->key_id) {
             printf("This key is already used\n");
            return;
        }
    }

    FILE* developersFile = fopen(DEVELOPERS_FILE, "rb+");

    readIndexTable();
    indexTable[developersCount].key_id = developer->key_id;
    indexTable[developersCount].address = developersCount * sizeof(Developer);
    developersCount++;

    fseek(developersFile, 0, SEEK_END);

    fwrite(&developer->key_id, sizeof(int), 1, developersFile);
    fwrite(&developer->name, sizeof(developer->name), 1, developersFile);
    fwrite(&developer->country, sizeof(developer->country), 1, developersFile);
    fwrite(&developer->firstGameAddress, sizeof(int), 1, developersFile);

    sortIndexTable();
    rewriteIndexTable();
    fclose(developersFile);


}
