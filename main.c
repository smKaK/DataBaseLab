#include <stdio.h>
#include "DataBase.h"
int main() {
    InitFiles();
    Developer dev1 = {.key_id = 1, .name = "GSC", .country = "Ukraine", .firstGameAddress = -1};
    Developer dev2 = {.key_id = 2, .name = "4A", .country = "Ukraine", .firstGameAddress = -1};
    Developer dev3 = {.key_id = 3, .name = "CDProjectRed", .country = "Poland", .firstGameAddress = -1};
    Developer dev4 = {.key_id = 4, .name = "Nintendo", .country = "USA", .firstGameAddress = -1};
    Developer dev5 = {.key_id = 5, .name = "Ubisoft", .country = "France", .firstGameAddress = -1};
    Developer dev6 = {.key_id = 6, .name = "EA", .country = "USA", .firstGameAddress = -1};
    Game g1 = {.key_id = 1, .developer_id = 1,.gameName = "Stalker 2", .gameEngineName = "Unreal Engine 4", .nextGameAddress = -1, .isDeleted = 0};
    Game g2 ={.key_id = 2, .developer_id = 3, .gameName = "Witcher 3", .gameEngineName = "Red Engine", .nextGameAddress = -1, .isDeleted = 0};
    Game g3 ={.key_id = 3, .developer_id = 3, .gameName = "Witcher 2", .gameEngineName = "Red Engine", .nextGameAddress = -1, .isDeleted = 0};
    Game g4 = {.key_id = 4, .developer_id = 5, .gameName = "Assassin's creed", .gameEngineName = "Cry Engine", .nextGameAddress = -1, .isDeleted = 0};
    Game g5 = {.key_id = 5, .developer_id = 5, .gameName = "Far Cry", .gameEngineName = "Cry Engine", .nextGameAddress = -1, .isDeleted = 0};
    Game g6 = {.key_id = 6, .developer_id = 5, .gameName = "Watch Dogs", .gameEngineName = "Cry Engine", .nextGameAddress = -1, .isDeleted = 0};
    Game g7 =  {.key_id = 7, .developer_id = 6, .gameName = "FIFA", .gameEngineName = "Frostbite", .nextGameAddress = -1, .isDeleted = 0};
    insert_m(&dev1);
    insert_m(&dev2);
    insert_m(&dev3);
    insert_m(&dev4);
    insert_m(&dev5);

    insert_s(&g1);
    insert_s(&g2);
    insert_s(&g3);
    insert_s(&g4);
    insert_s(&g5);
    insert_s(&g6);

    ut_m();
    ut_s();

    delete_m(3);
    delete_s(5, 5);

    ut_m();
    ut_s();

    insert_m(&dev6);
    insert_s(&g7);

    ut_m();
    ut_s();

    update_m(6,"SEGA", "Japan");
    update_s(6,7,"Sonic", "Star Engine");

    ut_m();
    ut_s();
    return 0;
}