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

    printf("Function: ut_m:");

    int key_id;
    char name[30], country[30];
    for (int i = 0; i < ; i++) {
        fread(&index, sizeof(int), 1, file);
        fread(&modelName, sizeof(modelName), 1, file);
        fread(&stagesNumber, sizeof(int), 1, file);
        fread(&firstRocketAddress, sizeof(int), 1, file);
        cout << "index: " << index << ", model name: " << modelName <<
             ", number of stages: " << stagesNumber << ", first rocket address: " << firstRocketAddress << endl;
    }
}

