#include <stdio.h>
#include "cyber_spaceship.h"

const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length)
{
    const char* const cab_end_location = cab_start_location + cab_length;
    char* pos = (char*)cab_start_location;
    char* cluster_pos = NULL;
    int i = 0;
    size_t max_length = 0;
    size_t count = 0;
    size_t safe_length = 0;
    char* result = NULL;
    char* tmp = NULL;

    if (cluster_count == 0) {
        *out_longest_safe_area_length = cab_length;
        return cab_start_location;
    }

    if (cab_length == 0) {
        *out_longest_safe_area_length = 0;
        return NULL;
    }

    for ( ; pos < cab_end_location; pos++) {
        i = 0;
        count = 0;
        for ( ; i < (int)cluster_count; i++) {
            cluster_pos = (char*)cluster_start_locations[i];
            if (pos >=  cluster_pos && pos < cluster_pos + cluster_lengths[i]) {
                count++;
            }
        }
        if (count % 2 == 0 || count == 0) {
            if (safe_length == 0) {
                tmp = pos;
            }
            safe_length++;
            continue;
        }
        if (safe_length >= max_length) {
            max_length = safe_length;
            result = tmp;
        }
        safe_length = 0;
    }

    if (safe_length != 0 && safe_length >= max_length) {
        result = tmp;
        max_length = safe_length;
    }

    *out_longest_safe_area_length = max_length;
    return result;
}

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count)
{
    const char* const cab_end_location = cab_start_location + cab_length;
    char* pos = (char*)cab_start_location;
    char* cluster_pos = NULL;
    int i = 0;
    size_t count = 0;
    size_t safe_length = 0;
    size_t unsafe_length = 0;
    
    for ( ; pos < cab_end_location; pos++) {
        i = 0;
        count = 0;
        for ( ; i < (int)cluster_count; i++) {
            cluster_pos = (char*)cluster_start_locations[i];
            if (pos >=  cluster_pos && pos < cluster_pos + cluster_lengths[i]) {
                count++;
            }
        }
        if (count % 2 == 0 || count == 0) {
            safe_length++;
            continue;
        }
        unsafe_length++;
    }

    return (int)(safe_length / 10.0 + unsafe_length / 5.0 + 0.5);
}

