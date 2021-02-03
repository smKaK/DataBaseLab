#include <stdio.h>
#include "DataBase.h"
int main() {
    InitFiles();
    Developer dev1 = {.key_id = 1, .name = "GSC", .country = "Ukraine", .firstGameAddress = 0};
    Developer dev2 = {.key_id = 2, .name = "4A", .country = "Ukraine", .firstGameAddress = 42};
    insert_m(&dev2);
    insert_m(&dev1);
    ut_m();
    ut_i();
    return 0;
}