#include "character_deserializer.h"
#include <stdio.h>

int main(void)
{
    character_v3_t test;
    get_character("Superman_v1.txt", &test);

    printf("name is %s\n level is %d\n strength is %d\n", test.name, test.level, test.strength);
    printf("dexterity is %d\n intelligence is %d\n armours is %d\n", test.dexterity, test.intelligence, test.armour);
    printf("hp is %d\n mp is %d\n", test.health, test.mana);   
    return 0;
}
