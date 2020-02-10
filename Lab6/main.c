#include "character_deserializer.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    character_v3_t test;
    get_character("Batman_v2.txt", &test);

    printf("name is %s\n level is %d\n strength is %d\n", test.name, test.level, test.strength);
    printf("dexterity is %d\n intelligence is %d\n armours is %d\n", test.dexterity, test.intelligence, test.armour);
    printf("hp is %d\n mp is %d\n", test.health, test.mana);   
    // char test[123] = "I love you!!";
    // char* token  = strstr(test, ",");
    // printf("%s", token);

    return 0;
}
