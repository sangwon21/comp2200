#include <stdio.h>
#include <time.h>
#include <string.h>
#include "receipter.h"
#define MAX_ITEM_LENGTH (10)
#define ONE_LINE_LENGTH (50)
#define PRINT_LINE_LIMIT (75)
#define MAX_FOOD_NAME_LENGTH (25)
#define NULL_CHAR ('\0')

typedef struct {
    char name[MAX_FOOD_NAME_LENGTH + 1];
    double price;
} food_t;

static int g_current_item_length = 0;
static food_t g_item_lists[MAX_ITEM_LENGTH];
static double g_tip = 0;
static char g_message[PRINT_LINE_LIMIT + 1];
static int g_message_length = 0;
static int g_order_num = 0;

int add_item(const char* name, double price)
{
    int name_length = 0;
    if (g_current_item_length >= MAX_ITEM_LENGTH) {
        return FALSE;
    }
    name_length = strlen(name);

    g_item_lists[g_current_item_length].price = price;    
    
    if (name_length >= MAX_FOOD_NAME_LENGTH) {
        strncpy(g_item_lists[g_current_item_length].name, name, MAX_FOOD_NAME_LENGTH);
        g_item_lists[g_current_item_length++].name[MAX_FOOD_NAME_LENGTH] = NULL_CHAR;
        
        return TRUE;
    }

    strncpy(g_item_lists[g_current_item_length].name, name, name_length);
    g_item_lists[g_current_item_length++].name[name_length] = NULL_CHAR;

    return TRUE;
}

void add_tip(double tip)
{
    g_tip = tip;
}

void add_message(const char* message)
{
    int message_length = strlen(message);
    if (message_length >= PRINT_LINE_LIMIT) {
        strncpy(g_message, message, PRINT_LINE_LIMIT);
        g_message[PRINT_LINE_LIMIT] = NULL_CHAR;
        g_message_length = PRINT_LINE_LIMIT;
        return;
    }
    strncpy(g_message, message, message_length);
    g_message[message_length] = NULL_CHAR;
    g_message_length = message_length;
}

void initialize_data()
{
    g_tip = 0;
    g_current_item_length = 0;
    g_message[g_current_item_length] = NULL_CHAR;
    g_message_length = 0;
}

int print_receipt(const char* filename, time_t timestamp)
{
    FILE* file = NULL;
    struct tm* timeinfo = NULL;
    int index = 0;
    double subTotal = 0.0;
    double tax = 0.0;
    const char* iter_ptr = NULL;

    if (g_current_item_length == 0) {
        return FALSE;
    }

    file = fopen(filename, "w");
    timeinfo = gmtime ( &timestamp );
    
    fprintf(file, "%s", "Charles' Seafood\n");
    fprintf(file, "%s", "--------------------------------------------------\n");
    fprintf(file, "%d-%02d-%02d %02d:%02d:%02d", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    fprintf(file, "                          %05d\n", g_order_num);
    fprintf(file, "%s", "--------------------------------------------------\n");
    for (; index < g_current_item_length; index++) {
        subTotal += g_item_lists[index].price;
        fprintf(file, "%33s%17.2f\n", g_item_lists[index].name, g_item_lists[index].price);
    }
    tax = subTotal * 0.05;

    fprintf(file, "\n%33s%17.2f\n", "Subtotal", subTotal);
    if (g_tip != 0) {
        fprintf(file, "%33s%17.2f\n", "Tip", g_tip);
    }

    fprintf(file, "%33s%17.2f\n", "Tax", tax);
    fprintf(file, "%33s%17.2f\n\n", "Total", subTotal + g_tip + tax);

    
    iter_ptr = g_message;
    if (g_message_length != 0) {
        while (*iter_ptr != NULL_CHAR && iter_ptr - g_message != PRINT_LINE_LIMIT) {
            if (iter_ptr - g_message == ONE_LINE_LENGTH) {
                fprintf(file, "%c", '\n');
            }
            fprintf(file, "%c", *iter_ptr);
            iter_ptr++;
        }
        fprintf(file, "%c", '\n');
    }
    
    fprintf(file, "%s\n", "==================================================");
    fprintf(file, "%50s", "Tax#-51234");
    
    g_order_num++;    
    fclose(file);
    initialize_data();
    return TRUE;
}
