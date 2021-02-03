#ifndef DB_LAB1_DATABASE_H
#define DB_LAB1_DATABASE_H

#include <stdio.h>
#include "Games.h"
#include "Developers.h"
#define GAMES_FILE "Games.bin"
#define DEVELOPERS_FILE "Developers.bin"
#define INDEXES_FILE "Indexes.bin"


void InitFiles(); //    truncates the file to zero length if it exists,
                  //    otherwise creates a file if it does not exist

void ut_m(); // reading and writing master file

void ut_s(); // reading and writing slave file

#endif //DB_LAB1_DATABASE_H
