#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "character_deserializer.h"

int main(void)
{
    character_v3_t superman_v1;
    character_v3_t batman_v2;
    character_v3_t flash_v3;
    character_v3_t wonderwoman_v3;
    int version;

    version = get_character("Superman_v1.txt", &superman_v1);
    assert(version == 1);
    assert(strcmp(superman_v1.name, "player_15") == 0);
    assert(superman_v1.level == 10);
    assert(superman_v1.health == 100);
    assert(superman_v1.mana == 25);
    assert(superman_v1.strength == 28);
    assert(superman_v1.dexterity == 20);
    assert(superman_v1.intelligence == 15);
    assert(superman_v1.armour == 14);
    assert(superman_v1.evasion == 10);
    assert(superman_v1.leadership == 1);
    assert(superman_v1.minion_count == 0);
    assert(superman_v1.elemental_resistance.fire == 1);
    assert(superman_v1.elemental_resistance.cold == 1);
    assert(superman_v1.elemental_resistance.lightning == 1);
    
    version = get_character("Batman_v2.txt", &batman_v2);
    assert(version == 2);
    assert(strcmp(batman_v2.name, "Batman_v2") == 0);
    assert(batman_v2.level == 25);
    assert(batman_v2.health == 130);
    assert(batman_v2.mana == 50);
    assert(batman_v2.strength == 30);
    assert(batman_v2.dexterity == 28);
    assert(batman_v2.intelligence == 40);
    assert(batman_v2.armour == 20);
    assert(batman_v2.evasion == 20);
    assert(batman_v2.leadership == 2);
    assert(batman_v2.minion_count == 0);
    assert(batman_v2.elemental_resistance.fire == 3);
    assert(batman_v2.elemental_resistance.cold == 3);
    assert(batman_v2.elemental_resistance.lightning == 3);
    
    version = get_character("Flash_v3.txt", &flash_v3);
    assert(version == 3);
    assert(strcmp(flash_v3.name, "Flash_v3") == 0);
    assert(flash_v3.level == 50);
    assert(flash_v3.health == 280);
    assert(flash_v3.mana == 55);
    assert(flash_v3.strength == 50);
    assert(flash_v3.dexterity == 85);
    assert(flash_v3.intelligence == 30);
    assert(flash_v3.armour == 20);
    assert(flash_v3.evasion == 45);
    assert(flash_v3.leadership == 12);
    assert(flash_v3.minion_count == 0);
    assert(flash_v3.elemental_resistance.fire == 10);
    assert(flash_v3.elemental_resistance.cold == 10);
    assert(flash_v3.elemental_resistance.lightning == 10);
    
    version = get_character("Wonderwoman_v3.txt", &wonderwoman_v3);
    assert(version == 3);
    assert(strcmp(wonderwoman_v3.name, "Wonderwoman_v3") == 0);
    assert(wonderwoman_v3.level == 55);
    assert(wonderwoman_v3.health == 320);
    assert(wonderwoman_v3.mana == 75);
    assert(wonderwoman_v3.strength == 75);
    assert(wonderwoman_v3.dexterity == 55);
    assert(wonderwoman_v3.intelligence == 35);
    assert(wonderwoman_v3.armour == 45);
    assert(wonderwoman_v3.evasion == 30);
    assert(wonderwoman_v3.leadership == 20);
    assert(wonderwoman_v3.minion_count == 2);
    assert(wonderwoman_v3.elemental_resistance.fire == 20);
    assert(wonderwoman_v3.elemental_resistance.cold == 22);
    assert(wonderwoman_v3.elemental_resistance.lightning == 15);

    assert(strcmp(wonderwoman_v3.minions[0].name, "amazoness") == 0);
    assert(wonderwoman_v3.minions[0].health == 50);
    assert(wonderwoman_v3.minions[0].strength == 15);
    assert(wonderwoman_v3.minions[0].defence == 5);

    assert(strcmp(wonderwoman_v3.minions[1].name, "valkyrie") == 0);
    assert(wonderwoman_v3.minions[1].health == 45);
    assert(wonderwoman_v3.minions[1].strength == 20);
    assert(wonderwoman_v3.minions[1].defence == 4);

	return 0;
}
