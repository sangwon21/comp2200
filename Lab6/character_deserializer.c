#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "character_deserializer.h"
#define BUFFER_LENGTH 255

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

void version1_deserialize(character_v3_t* out_character)
{
    char buffer[BUFFER_LENGTH] = "player_";
    char tmp[BUFFER_LENGTH];
    const char* token;

    while (token) {
        if (strcmp("id", token) == 0) {
            token = strtok(NULL, ":,");
            strcat(tmp, token);
            strcpy(out_character->name, tmp);
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

int get_character(const char* filename, character_v3_t* out_character)
{
    char buffer[BUFFER_LENGTH];
    char tmp[BUFFER_LENGTH] = "player_";
    char* token;
    FILE* file = fopen(filename, "r");

    fscanf(file, "%s", buffer);
    
    token = strtok(buffer, ":,");

    
    
    fclose(file);
    return 0;
}