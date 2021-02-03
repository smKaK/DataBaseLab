#ifndef DB_LAB1_GAMES_H
#define DB_LAB1_GAMES_H

typedef struct {
    int key_id;
    char gameName[30];
    char gameEngineName[30];
    int nextGameAddress;
} Game;

#endif //DB_LAB1_GAMES_H
