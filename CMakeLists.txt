cmake_minimum_required(VERSION 3.17)
project(DB_LAB1 C)

set(CMAKE_C_STANDARD 99)

add_executable(DB_LAB1 main.c Games.h Developers.h DataBase.c DataBase.h IndexTable.c IndexTable.h Developers.c Games.c)