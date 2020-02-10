#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "character_deserializer.h"
#define BUFFER_LENGTH 255
#define NAME_LIMIT 50

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
    out_character->evasion = 10;
    out_character->leadership = 1;
    out_character->elemental_resistance.fire = 1;
    out_character->elemental_resistance.cold = 1;
    out_character->elemental_resistance.lightning = 1;
}

void version2_deserialize(character_v3_t* out_character, char* buffer)
{
    char player_name[NAME_LIMIT];
    const char* token = strtok(buffer, ",");
    int count = 0;
    strncpy(player_name, token, NAME_LIMIT);
    
    while (token) {
        if (count == 0) {
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
}

int get_character(const char* filename, character_v3_t* out_character)
{
    char buffer[BUFFER_LENGTH];
    char* token;
    FILE* file = fopen(filename, "r");

    fscanf(file, "%s", buffer);
    
    token = strstr(buffer, ":");
    if (token != NULL) {
        version1_deserialize(out_character, buffer);
    }

    token = strstr(buffer, ",");
    if(token != NULL) {
        fscanf(file, "%s", buffer);
        version2_deserialize(out_character, buffer);
    }
    
    
    fclose(file);
    return 0;
}