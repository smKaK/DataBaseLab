#include <stdio.h>
#include "DataBase.h"
int main() {
    InitFiles();
    Developer dev1 = {.key_id = 1, .name = "GSC", .country = "Ukraine", .firstGameAddress = -1};
    Developer dev2 = {.key_id = 2, .name = "4A", .country = "Ukraine", .firstGameAddress = -1};
    Game g1 = {.key_id = 1, .developer_id = 2,.gameName = "Stalker 2", .gameEngineName = "Unreal Engine 4", .nextGameAddress = -1};
    Game  g2 ={.key_id = 2, .developer_id = 2, .gameName = "Witcher 3", .gameEngineName = "Red Engine", .nextGameAddress = -1};
    insert_m(&dev2);
    insert_m(&dev1);
    insert_s(&g1);
    insert_s(&g2);
    ut_m();
    ut_i();
    ut_s();
    printf("Game: %d , Developer: %d", sizeof (Game), sizeof (Developer));
    return 0;
}