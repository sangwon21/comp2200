#include <limits.h>
#include "array.h"

int get_index_of(const int numbers[], const size_t element_count, const int num){
    int index;

    if ((int)element_count <= 0) {
        return -1;
    }

    for (index = 0; index < (int)element_count; index++) {
        if (numbers[index] == num) {
            return index;
        }
    }

    return -1;
}

int get_last_index_of(const int numbers[], const size_t element_count, const int num){
    int index;

    if ((int)element_count <= 0) {
        return -1;
    }

    for (index = (int)element_count; index >= 0; index--) {
        if (numbers[index] == num) {
            return index;
        }
    }
    
    return -1;
}

int get_max_index(const int numbers[], const size_t element_count){
    int max_index;
    int max_number;
    size_t index;

    if (element_count == 0) {
        return -1;
    }
    max_index = 0;
    max_number = numbers[0];

    for (index = 0 + 1; index < element_count; index++) {
        if (numbers[index] > max_number) {
            max_index = index;
            max_number = numbers[index];
        }
    }

    return max_index;
}

int get_min_index(const int numbers[], const size_t element_count){
    int min_index;
    int min_number;
    size_t index;

    if (element_count == 0) {
        return -1;
    }
    min_index = 0;
    min_number = numbers[0];

    for (index = 0 + 1; index < element_count; index++) {
        if (numbers[index] < min_number) {
            min_index = index;
            min_number = numbers[index];
        }
    }

    return min_index;
}

int is_all_positive(const int numbers[], const size_t element_count){
    int index;

    if ((int)element_count <= 0) {
        return FALSE;
    }

    for (index = 0; index < (int)element_count; index++) { 
        if (numbers[index] < 0) {
            return FALSE;
        } 
    }

    return TRUE;
}

int has_even(const int numbers[], const size_t element_count){
    int index;

    if ((int)element_count <= 0) {
        return FALSE;
    }

    for (index = 0; index < (int)element_count; index++) { 
        if (numbers[index] % 2 == 0) {
            return TRUE;
        } 
    }
    
    return FALSE;
}

int insert(int numbers[], const size_t element_count, const int num, const size_t pos){
    
    int index;

    if (element_count < pos) {
        return FALSE;
    }

    if (element_count == pos) {
        numbers[pos] = num;
        return TRUE;
    }

    for (index = (int)element_count - 1; index >= (int)pos; index--) {
        numbers[index + 1] = numbers[index];
    }

    numbers[pos] = num;

    return TRUE;
}

int remove_at(int numbers[], const size_t element_count, const size_t index){

    int pos;

    if (element_count < index + 1) {
        return FALSE;
    }

    for (pos = index; pos < (int)element_count; pos++) {
        numbers[pos] = numbers[pos + 1];
    }
    
    numbers[pos - 1] = INT_MIN;

    return TRUE;
}
