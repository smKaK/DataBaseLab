#include "DataBase.h"

void InitFiles()
{
    FILE* developersFile_m = fopen(DEVELOPERS_FILE, "wb+");
    fclose(developersFile_m);
    FILE* gamesFile_s = fopen(GAMES_FILE, "wb+");
    fclose(gamesFile_s);
    FILE* indexesFile_i = fopen(INDEXES_FILE, "wb+");
    fclose(indexesFile_i);

    for(int i = 0; i < SIZE; ++i)
    {
        indexTable[i].key_id = -1;
        indexTable[i].address = -1;
        indexTable[i].isDeleted = 0;
    }

 }

void ut_m()
{
    FILE* developersFile = fopen(DEVELOPERS_FILE, "rb+");
    if(developersFile == NULL)
        perror("Error:can't open developers.bin\n");

    printf("Function: ut_m:\n");

    int key_id, firstGameAddress;
    char companyName[30], country[30];

    FILE* indexesFile = fopen(DEVELOPERS_FILE, "rb+");
    if(indexesFile == NULL)
        perror("Error:can't open Indexes.bin\n");
    for(int i = 0; i < developersCount + deletedDevelopersCount; ++i)
    {
        if(indexTable[i].isDeleted == 0)
        {
            int address = getAddress(indexTable[i].key_id);
            fseek(developersFile, address, SEEK_SET);
            fread(&key_id, sizeof(int), 1, developersFile);
            fread(&companyName, sizeof(companyName), 1, developersFile);
            fread(&country, sizeof(country), 1, developersFile);
            fread(&firstGameAddress, sizeof(int), 1, developersFile);
            printf("Key id: %d, Company name: %s, Country: %s, First game address: %d\n",
                   key_id, companyName, country, firstGameAddress);
        }

    }

    fclose(developersFile);
    fclose(indexesFile);
}

void ut_i()
{

    FILE* indexesFile = fopen(INDEXES_FILE, "rb+");
    if(indexesFile == NULL)
        perror("Error:can't open Indexes.bin\n");

    int key_id, address, isDeleted;

    for (int i = 0; i < developersCount + deletedDevelopersCount; i++) {
        fread(&key_id, sizeof(int), 1, indexesFile);
        fread(&address, sizeof(int), 1, indexesFile);
        fread(&isDeleted, sizeof(int), 1, indexesFile);
        printf("Key id: %d, Address: %d, is Deleted: %d\n",
               key_id, address, isDeleted);
    }
    fclose(indexesFile);
}

void ut_s()
{
    FILE* gamesFile = fopen(GAMES_FILE, "rb+");
    if(gamesFile == NULL)
        perror("Error:can't open Games.bin\n");

    printf("Function: ut_s:\n");

    int key_id, nextGameAddress, developer_id, isDeleted;
    char gameName[30], gameEngine[30];

    for (int i = 0; i < gamesCount + deletedGamesCount; i++) {
        fseek(gamesFile, 72, SEEK_CUR);
        fread(&isDeleted, sizeof(int), 1, gamesFile);
        if(isDeleted == 0) {
            fseek(gamesFile, -76, SEEK_CUR);
            fread(&key_id, sizeof(int), 1, gamesFile);
            fread(&developer_id, sizeof(int), 1, gamesFile);
            fread(&gameName, sizeof(gameName), 1, gamesFile);
            fread(&gameEngine, sizeof(gameEngine), 1, gamesFile);
            fread(&nextGameAddress, sizeof(int), 1, gamesFile);
            fread(&isDeleted, sizeof (int), 1, gamesFile);
            printf("Key id: %d, Game name: %s,  Game engine: %s, Next game address: %d, IsDeleted:%d \n",
                   key_id, gameName, gameEngine, nextGameAddress,isDeleted);
        }
    }

    fclose(gamesFile);
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
    indexTable[developersCount+deletedDevelopersCount].key_id = developer->key_id;
    indexTable[developersCount+deletedDevelopersCount].address = (developersCount+deletedDevelopersCount) * sizeof(Developer);
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

void insert_s(Game* game)
{
    int flag = 0;
    for (int i = 0; i < developersCount; i++) {
        if (indexTable[i].key_id == game->developer_id && indexTable[i].isDeleted != 1) {
            flag = 1;
        }
    }
    if(flag == 0)
    {
        printf("this developer does not exists!!!\n");
        return;
    }

    FILE* gamesFile = fopen(GAMES_FILE, "rb+");
    fseek(gamesFile, 0, SEEK_END);
    fwrite(&game->key_id, sizeof(int), 1, gamesFile);
    fwrite(&game->developer_id, sizeof (int), 1, gamesFile);
    fwrite(&game->gameName, sizeof(game->gameName), 1, gamesFile);
    fwrite(&game->gameEngineName, sizeof(game->gameEngineName), 1, gamesFile);
    fwrite(&game->nextGameAddress, sizeof(int), 1, gamesFile);
    fwrite(&game->isDeleted, sizeof(int), 1, gamesFile);

    FILE* developersFile = fopen(DEVELOPERS_FILE, "rb+");
    int offsetToFirstGameAddress = getAddress(game->developer_id) + 64; // 64b = key_id(4b) +
                                                                        // companyName(30b) +
                                                                        // country(30b)
    fseek(developersFile, offsetToFirstGameAddress, SEEK_SET);

    int firstGameAddress;
    fread(&firstGameAddress, sizeof(int), 1, developersFile);

    int address = (gamesCount+deletedGamesCount)*sizeof(Game);
    if (firstGameAddress == -1) {
        fseek(developersFile, -4, SEEK_CUR);
        fwrite(&address, sizeof(int), 1, developersFile);
    } else {
        int nextGameAddress = firstGameAddress;
        while (nextGameAddress != -1) {
            fseek(gamesFile, nextGameAddress + 68, SEEK_SET);
            fread(&nextGameAddress, sizeof(int), 1, gamesFile);
        }
        fseek(gamesFile, -4, SEEK_CUR);
        fwrite(&address, sizeof(int), 1, gamesFile);
    }
    gamesCount++;
    fclose(gamesFile);
    fclose(developersFile);
}

void get_m(int key_id)
{
    int offset = getAddress(key_id);
    if (offset == -1) {
         printf("There is no developer with key_id %d \n", key_id);
        return;
    }

    FILE* developersFile = fopen(DEVELOPERS_FILE, "rb+");
    fseek(developersFile, offset+4, SEEK_SET);
    char companyName[30], country[30];
    int  firstGameAddress;
    fread(&companyName, sizeof(companyName), 1, developersFile);
    fread(&country, sizeof(country), 1, developersFile);
    fread(&firstGameAddress, sizeof(int), 1, developersFile);
    printf("Developer with index %d has Company Name: %s, Country: %s\n",
           key_id, companyName, country);
    fclose(developersFile);
}

void get_s(int key_id_m, int key_id_s)
{
    int offset_m = getAddress(key_id_m);
    if (offset_m == -1) {
        printf("There is no developer with key_id %d \n", key_id_m);
        return;
    }

    FILE* developersFile = fopen(DEVELOPERS_FILE, "rb+");
    fseek(developersFile, offset_m, SEEK_SET);
    char companyName[30], country[30];
    int  firstGameAddress;
    fseek(developersFile, offset_m + 64 ,SEEK_SET);
    fread(&firstGameAddress, sizeof(int), 1, developersFile);

    fclose(developersFile);

    //printf("%d", firstGameAddress);

    if(firstGameAddress == -1)
    {
        printf("There are no games by this company\n");
        return;
    } else{
        FILE* gamesFile = fopen(GAMES_FILE, "rb+");
        fseek(gamesFile, firstGameAddress, SEEK_SET);
        char gameName[30], gameEngine[30];
        int key_id_s_;
        int nextGameAddress = firstGameAddress;
        int currentAddress = firstGameAddress;
        fread(&key_id_s_, sizeof (int), 1, gamesFile);
        while (key_id_s_ != key_id_s) {
            if(nextGameAddress == -1)
            {
                printf("No Game with key_id %d by company with key_id %d\n", key_id_s, key_id_m);
                return;
            }
            fseek(gamesFile, nextGameAddress, SEEK_SET);
            fread(&key_id_s_, sizeof (int), 1, gamesFile);
            currentAddress = nextGameAddress;
            fseek(gamesFile, nextGameAddress + 68, SEEK_SET);
            fread(&nextGameAddress, sizeof(int), 1, gamesFile);
        }
        int isDeleted = -1;
        fseek(gamesFile, currentAddress+8, SEEK_SET);
        fread(gameName, sizeof (gameName), 1, gamesFile);
        fread(gameEngine, sizeof (gameEngine), 1, gamesFile);
        fseek(gamesFile,sizeof (int), SEEK_CUR);
        fread(&isDeleted, sizeof(int), 1, gamesFile);
        if(isDeleted == 0)
        {
            printf("Game with key id: %d by company with key id: %d has Name: %s and gameEngine: %s\n"
                    , key_id_s, key_id_m, gameName, gameEngine);
        } else
        {
            printf("No Game with key_id %d by company with key_id %d\n", key_id_s, key_id_m);
        }

        fclose(developersFile);
    }
}

void update_m(int key_id, char newCompanyName[30], char newCountryName[30])
{
    int offset = getAddress(key_id);
    if (offset == -1) {
        printf("There is no developer with key id %d\n", key_id);
        return;
    }

    FILE* developerFile = fopen(DEVELOPERS_FILE, "rb+");
    fseek(developerFile, offset + 4, SEEK_SET);
    fwrite(newCompanyName, 30, 1, developerFile);
    fwrite(newCountryName, 30, 1, developerFile);
    fclose(developerFile);
}

void update_s(int key_id_m, int key_id_s, char newGameName[30], char newGameEngine[30]) {
    int offset_m = getAddress(key_id_m);
    if (offset_m == -1) {
        printf("There is no developer with key id %d\n", key_id_m);
        return;
    }

    FILE *developersFile = fopen(DEVELOPERS_FILE, "rb+");
    fseek(developersFile, offset_m, SEEK_SET);

    int firstGameAddress;
    fseek(developersFile, offset_m + 64, SEEK_SET);
    fread(&firstGameAddress, sizeof(int), 1, developersFile);

    fclose(developersFile);

    if (firstGameAddress == -1) {
        printf("There are no games by this company\n");
        return;
    } else {
        FILE *gamesFile = fopen(GAMES_FILE, "rb+");
        fseek(gamesFile, firstGameAddress, SEEK_SET);
        char gameName[30], gameEngine[30];
        int key_id_s_;
        int nextGameAddress = firstGameAddress;
        int currentAddress = firstGameAddress;
        fread(&key_id_s_, sizeof(int), 1, gamesFile);
        while (key_id_s_ != key_id_s) {
            if (nextGameAddress == -1) {
                printf("No Game with key_id %d by company with key_id %d\n", key_id_s, key_id_m);
                return;
            }
            fseek(gamesFile, nextGameAddress, SEEK_SET);
            fread(&key_id_s_, sizeof(int), 1, gamesFile);
            currentAddress = nextGameAddress;
            fseek(gamesFile, nextGameAddress + 68, SEEK_SET);
            fread(&nextGameAddress, sizeof(int), 1, gamesFile);
        }


        fseek(gamesFile, currentAddress + 8, SEEK_SET);
        fwrite(newGameName, 30, 1, gamesFile);
        fwrite(newGameEngine, 30, 1, gamesFile);
        fclose(gamesFile);
    }
}



void delete_m(int key_id)
{
    int k = binarySearch(indexTable,0, developersCount,key_id);
    if (k == -1) {
        printf("There is no developer with key id %d\n", key_id);
        return;
    }
   indexTable[k].isDeleted = 1;

    int offset = indexTable[k].address;
    FILE* developersFile = fopen(DEVELOPERS_FILE, "rb+");
    int firstGameAddress;
    fseek(developersFile, offset + 64 ,SEEK_SET);
    fread(&firstGameAddress, sizeof(int), 1, developersFile);
    fclose(developersFile);
    if(firstGameAddress != -1)
    {
        FILE* gamesFile = fopen(GAMES_FILE, "rb+");
        int newIsDel = 1;
        fseek(gamesFile, firstGameAddress, SEEK_SET);
        int nextGameAddress = firstGameAddress;
        int currentAddress = firstGameAddress;
        while(nextGameAddress != -1)
        {
            currentAddress = nextGameAddress;
            fseek(gamesFile, currentAddress + 72, SEEK_SET);
            fwrite(&newIsDel, sizeof(int), 1, gamesFile);
            deletedGamesCount++;
            gamesCount--;
            fseek(gamesFile, nextGameAddress + 68, SEEK_SET);
            fread(&nextGameAddress, sizeof(int), 1, gamesFile);
        }
        //fseek(gamesFile, 72, SEEK_CUR);
        //fwrite(&newIsDel, sizeof(int), 1, gamesFile);
        fclose(gamesFile);

    }



    rewriteIndexTable();
    fclose(developersFile);
}


void delete_s(int key_id_m, int key_id_s) {
    int offset_m = getAddress(key_id_m);
    if (offset_m == -1) {
        printf("There is no developer with key id %d\n", key_id_m);
        return;
    }

    FILE *developersFile = fopen(DEVELOPERS_FILE, "rb+");
    fseek(developersFile, offset_m, SEEK_SET);
    int firstGameAddress;
    fseek(developersFile, offset_m + 64, SEEK_SET);
    fread(&firstGameAddress, sizeof(int), 1, developersFile);


    if (firstGameAddress == -1) {
        printf("There are no games by this company\n");
        return;
    } else {
        FILE *gamesFile = fopen(GAMES_FILE, "rb+");


        int key_id_s_;
        int newNextGameAddress = -1;

        int newIsDeleted = 1;

        int nextNextGameAddress = -1;
        int nextGameAddress = firstGameAddress;
        int currentAddress = firstGameAddress;

        fseek(gamesFile, firstGameAddress, SEEK_SET);
        fread(&key_id_s_, sizeof(int), 1, gamesFile);

        fseek(gamesFile, firstGameAddress + 68, SEEK_SET);
        fread(&nextGameAddress, sizeof(int), 1, gamesFile);

        if (key_id_s_ == key_id_s) {

            fseek(developersFile, offset_m + 64, SEEK_SET);             //change first Game Address field
            fwrite(&nextGameAddress, sizeof(int), 1, developersFile);

            fseek(gamesFile, firstGameAddress + 68, SEEK_SET);     // change next game address to -1 and set isDeleted
            fwrite(&newNextGameAddress, sizeof(int), 1, gamesFile);
            fwrite(&newIsDeleted, sizeof(int), 1, gamesFile);

            gamesCount--;
            deletedGamesCount++;

            return;
        }else{
            while(nextGameAddress != -1){
                fseek(gamesFile, nextGameAddress, SEEK_SET);
                fread(&key_id_s_, sizeof (int), 1, gamesFile);
                if (key_id_s_ == key_id_s)
                {
                    fseek(gamesFile, nextGameAddress + 68, SEEK_SET);      //finding new nextAddress
                    fread(&nextNextGameAddress, sizeof(int), 1, gamesFile);

                    fseek(gamesFile, currentAddress + 68, SEEK_SET);         // writing new nextAddress
                    fwrite(&nextNextGameAddress, sizeof(int), 1, gamesFile);

                    fseek(gamesFile, nextGameAddress + 68, SEEK_SET);
                    fwrite(&newNextGameAddress, 4,1, gamesFile);
                    fwrite(&newIsDeleted, 4,1,gamesFile);

                    fflush(gamesFile);

                    gamesCount--;
                    deletedGamesCount++;
                    return;
                }

                currentAddress = nextGameAddress;
                fseek(gamesFile, nextGameAddress+68, SEEK_SET);
                fread(&nextGameAddress, sizeof (int), 1, gamesFile);

            }



        }

        fclose(gamesFile);
    }
    fclose(developersFile);
}

