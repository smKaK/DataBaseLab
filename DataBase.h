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
#endif //DB_LAB1_DATABASE_H
