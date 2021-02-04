#include <stdio.h>
#include "DataBase.h"
int main() {
    InitFiles();
    Developer dev1 = {.key_id = 13, .name = "GSC", .country = "Ukraine", .firstGameAddress = -1};
    Developer dev2 = {.key_id = 203, .name = "4A", .country = "Ukraine", .firstGameAddress = -1};
    Developer dev3 = {.key_id = 303, .name = "55A", .country = "Ukraine", .firstGameAddress = -1};
    Game g1 = {.key_id = 3, .developer_id = 13,.gameName = "Stalker 2", .gameEngineName = "Unreal Engine 4", .nextGameAddress = -1, .isDeleted = 0};
    Game  g2 ={.key_id = 4, .developer_id = 13, .gameName = "Witcher 3", .gameEngineName = "Red Engine", .nextGameAddress = -1, .isDeleted = 0};
    Game  g3 ={.key_id = 5, .developer_id = 13, .gameName = "Witcher 4", .gameEngineName = "Red Engine", .nextGameAddress = -1, .isDeleted = 0};
    insert_m(&dev2);
    insert_m(&dev1);
    insert_m(&dev3);

    insert_s(&g1);
    insert_s(&g2);
    insert_s(&g3);
    ut_m();
    ut_i();
    ut_s();

    get_m(13);
    get_m(203);
    get_s(13, 3);

    update_m(13, "CDProjectRed", "Poland");
    ut_m();

    update_s(13,3, "Stalker 1", "Xz");
    ut_s();

    delete_s(13,4);
    ut_s();
    ut_m();

    get_s(13,4);
    return 0;
}