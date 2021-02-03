#ifndef DB_LAB1_DEVELOPERS_H
#define DB_LAB1_DEVELOPERS_H
#define DEVELOPERS_FILE "Developers.bin"

typedef struct {
   int key_id;
   char name[30];
   char country[30];
   int firstGameAddress;
} Developer;

extern int developersCount;

#endif //DB_LAB1_DEVELOPERS_H
