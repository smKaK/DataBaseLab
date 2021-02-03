#ifndef DB_LAB1_GAMES_H
#define DB_LAB1_GAMES_H
#define GAMES_FILE "Games.bin"

typedef struct {
    int key_id;
    char gameName[30];
    char gameEngineName[30];
    int nextGameAddress;
} Game;

extern int gamesCount;

#endif //DB_LAB1_GAMES_H
