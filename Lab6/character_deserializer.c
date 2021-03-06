#include <stdio.h>
#include <string.h>
#include "character_deserializer.h"
#define BUFFER_LENGTH (512)
#define NAME_LIMIT (51)
#define TRUE (1)
#define FALSE (0)

int my_atoi(const char* number)
{
    int result = 0;
    const char* pointer = number;

    while (*pointer != '\0') {
        result = result * 10 + (*pointer - '0');
        pointer++;
    }

    return result;
}

void version1_deserialize(character_v3_t* out_character, char* buffer)
{
    char player_name[BUFFER_LENGTH] = "player_";
    const char* token = strtok(buffer, ":");

    while (token) {
        if (strcmp("id", token) == 0) {
            token = strtok(NULL, ":,");
            strcat(player_name, token);
            strcpy(out_character->name, player_name);
        } else if (strcmp("lvl", token) == 0) {
            token = strtok(NULL, ":,");
            out_character->level = my_atoi(token);
        } else if (strcmp("str", token) == 0) {
            token = strtok(NULL, ":,");
            out_character->strength = my_atoi(token);
        } else if (strcmp("dex", token) == 0) {
            token = strtok(NULL, ":,");
            out_character->dexterity = my_atoi(token);
        } else if (strcmp("intel", token) == 0) {
            token = strtok(NULL, ":,");
            out_character->intelligence = my_atoi(token);
        } else if (strcmp("def", token) == 0) {
            token = strtok(NULL, ":,");
            out_character->armour = my_atoi(token);
        } else if (strcmp("hp", token) == 0) {
            token = strtok(NULL, ":,");
            out_character->health = my_atoi(token);
        } else if (strcmp("mp", token) == 0) {
            token = strtok(NULL, ":,");
            out_character->mana = my_atoi(token);
        }
        token = strtok(NULL, ":,");
    }
    out_character->minion_count = 0;
    out_character->evasion = out_character->dexterity / 2;
    out_character->leadership = out_character->level / 10;
    out_character->elemental_resistance.fire = (out_character->armour / 4) / 3;
    out_character->elemental_resistance.cold = (out_character->armour / 4) / 3;
    out_character->elemental_resistance.lightning = (out_character->armour / 4) / 3;
}

void version2_deserialize(character_v3_t* out_character, char* buffer)
{
    char player_name[NAME_LIMIT];
    const char* token = strtok(buffer, ",");
    int count = 0;
    strncpy(player_name, token, NAME_LIMIT);
    player_name[NAME_LIMIT - 1] = '\0';

    while (token) {
        if (count == 0) {
            strncpy(out_character->name, player_name, NAME_LIMIT);
            goto increase_token;
        }
        if (count == 1) {
            out_character->level = my_atoi(token);
        } else if (count == 2) {
            out_character->strength = my_atoi(token);
        } else if (count == 3) {
            out_character->dexterity = my_atoi(token);
        } else if (count == 4) {
            out_character->intelligence = my_atoi(token);
        } else if (count == 5) {
            out_character->armour = my_atoi(token);
        } else if (count == 6) {
            out_character->evasion = my_atoi(token);
        }  else if (count == 7) {
            out_character-> elemental_resistance.cold = my_atoi(token) / 3;
            out_character-> elemental_resistance.fire = my_atoi(token) / 3;
            out_character-> elemental_resistance.lightning = my_atoi(token) / 3;
        } else if (count == 8) {
            out_character->health = my_atoi(token);
        } else if (count == 9) {
            out_character->mana = my_atoi(token);
        }
increase_token:
        count++;
        token = strtok(NULL, ",");
    }
    out_character->leadership = out_character->level / 10;
    out_character->minion_count = 0;
}

void read_minions(character_v3_t* out_character, FILE* file)
{
    char buffer[BUFFER_LENGTH];
    char line[BUFFER_LENGTH];
    char player_name[NAME_LIMIT];
    char space;
    int count = 0;

    while (TRUE) {
        if (fgets(line, BUFFER_LENGTH, file) == NULL) {
            clearerr(file);
            break;
        }

        if (sscanf(line, "%s %c %d %c %d %c %d", buffer, &space, &out_character->minions[count].health, &space, &out_character->minions[count].strength, &space, &out_character->minions[count].defence)) {
            strncpy(player_name, buffer, NAME_LIMIT);
            player_name[NAME_LIMIT - 1] = '\0';
            strncpy(out_character->minions[count].name, player_name, NAME_LIMIT);                            
            count++;
        }
    } 
}

void version3_deserialize(character_v3_t* out_character, FILE* file)
{
    char player_name[NAME_LIMIT];
    char buffer[BUFFER_LENGTH];
    char line[BUFFER_LENGTH];
    char space;

    while (TRUE) {
        if (fgets(line, BUFFER_LENGTH, file) == NULL) {
            clearerr(file);
            break;
        }

        if (sscanf(line, "%s %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c %d %c %d", buffer, &space, &out_character->level, &space, &out_character->health, &space, &out_character->mana, &space, &out_character->strength, &space, &out_character->dexterity, &space, &out_character->intelligence, &space, &out_character->armour, &space, &out_character->evasion, &space, &out_character->elemental_resistance.fire, &space, &out_character->elemental_resistance.cold, &space, &out_character->elemental_resistance.lightning, &space, &out_character->leadership, &space, &out_character->minion_count)) {
            strncpy(player_name, buffer, NAME_LIMIT);
            player_name[NAME_LIMIT - 1] = '\0';
            strncpy(out_character->name, player_name, NAME_LIMIT);

            if (out_character->minion_count != 0) {
                fgets(buffer, BUFFER_LENGTH, file);
                read_minions(out_character, file);
            }                            
        }
    }
}

int get_character(const char* filename, character_v3_t* out_character)
{
    char buffer[BUFFER_LENGTH];
    char* token;
    int version = 1;
    FILE* file = fopen(filename, "r");

    fgets(buffer, BUFFER_LENGTH, file);

    token = strstr(buffer, ":");
    if (token != NULL) {
        version1_deserialize(out_character, buffer);
        version = 1;
        goto file_end;
    }

    token = strstr(buffer, ",");
    if (token != NULL) {
        fgets(buffer, BUFFER_LENGTH, file);
        version2_deserialize(out_character, buffer);
        version = 2;
        goto file_end;
    }

    version3_deserialize(out_character, file);
    version = 3;

file_end:
    fclose(file);
    return version;
}
