#include "character_deserializer.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    character_v3_t test;
    get_character("Wonderwoman_v3.txt", &test);

    printf("name is %s\nlevel is %d\nstrength is %d\n", test.name, test.level, test.strength);
    printf("dexterity is %d\nintelligence is %d\narmours is %d\n", test.dexterity, test.intelligence, test.armour);
    printf("hp is %d\nmp is %d\n", test.health, test.mana);   
    printf("minion1 is name %s\nminion2 name is %s\nminion3 name is %s", test.minions[0].name, test.minions[1].name, test.minions[2].name);   
    // char test[123] = "I love you!!";
    // char* token  = strstr(test, ",");
    // printf("%s", token);

    return 0;
}
