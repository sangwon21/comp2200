#include <assert.h>
#include <stdio.h>
#include "cyber_spaceship.h"

#define CAB_LENGTH (50)

int main(void)
{
    char cab[CAB_LENGTH];
    const char* cluster_start_addresses[5];
    size_t cluster_lengths[5];

    size_t out_longest_safe_area_length = 0;
    size_t* out_longest_safe_area_length_p = &out_longest_safe_area_length;
    const char* longest_safe_cluster_start_address;
    int time_in_mins;
    const char* cab_start_address = cab;

    cluster_start_addresses[0] = &cab[8];
    cluster_start_addresses[1] = &cab[1];
    cluster_start_addresses[2] = &cab[13];
    cluster_start_addresses[3] = &cab[33];
    cluster_start_addresses[4] = &cab[38];

    cluster_lengths[0] = 10U;
    cluster_lengths[1] = 22U;
    cluster_lengths[2] = 10U;
    cluster_lengths[3] = 13U;
    cluster_lengths[4] = 10U;

    longest_safe_cluster_start_address = get_longest_safe_zone_or_null(cab_start_address, CAB_LENGTH, cluster_start_addresses, cluster_lengths, 5, out_longest_safe_area_length_p);

    assert(out_longest_safe_area_length == 15);
    assert(longest_safe_cluster_start_address == cab_start_address + 18);

    time_in_mins = get_travel_time(cab_start_address, CAB_LENGTH, cluster_start_addresses, cluster_lengths, 5);

    assert(time_in_mins == 7);

	return 0;
}
