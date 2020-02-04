#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "receipter.h"

int main(void)
{
    time_t time = 1569472997;

    assert(TRUE == add_item("Magarita", 12.45));
    assert(TRUE == add_item("Sharkfin soup", 500.12));
    assert(TRUE == add_item("Kingcrab dip", 125.99));
    assert(TRUE == add_item("Deep fried scallops", 7.36));
    assert(TRUE == add_item("Tacoyaki", 6.898));
    assert(TRUE == add_item("Salmon sashimi", 16.54));
    assert(TRUE == add_item("Tuna sashimi", 15.42));
    assert(TRUE == add_item("Unagi soup", 25.48));
    assert(TRUE == add_item("Nestea ice tea", 5.99));
    assert(TRUE == add_item("Chocolate brownie fudge", 8.99));

    assert(FALSE == add_item("This won't get added lol", 2.55));

    add_tip(20.55);
    
    assert(TRUE == print_receipt("receipt5.txt", time));

	return 0;
}
