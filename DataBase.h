#ifndef DB_LAB1_DATABASE_H
#define DB_LAB1_DATABASE_H

#include <stdio.h>
#include "Games.h"
#include "Developers.h"
#include "IndexTable.h"


void InitFiles(); //    truncates the file to zero length if it exists,
                  //    otherwise creates a file if it does not exist

void ut_m(); //writing on screen Developers.bin file data

void ut_s(); // writing on screen Games.bin file data

void ut_i(); //  writing on screen Indexes.bin file data

void insert_m(Developer* developer); // inserts a developer into developers.bin

void insert_s(Game* game); // inserts a game into Games.bin

void get_m(int key_id); //reading of developer by key_id on the basis of direct index access;

void get_s(int key_id_m, int key_id_s); //reading the game;

void update_m(int key_id, char newCompanyName[30], char newCountryName[30]);

void update_s(int key_id_m, int key_id_s, char newGameName[30], char newGameEngine[30]);

void delete_m(int key_m);

void delete_s(int key_id_m, int key_id_s);
#endif //DB_LAB1_DATABASE_H
