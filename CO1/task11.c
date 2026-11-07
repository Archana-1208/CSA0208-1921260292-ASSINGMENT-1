#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define FIXED_CHARGE_PAISE 5000LL

#define SLAB1_UNITS 100ULL
#define SLAB2_UNITS 200ULL

#define RATE1_PAISE 0LL
#define RATE2_PAISE 225LL
#define RATE3_PAISE 450LL

int main(void)
{
    uint16_t previous = 1200;
    uint16_t current = 1350;

    uint64_t units = (uint16_t)(current - previous);

    uint64_t first = units < SLAB1_UNITS ?
                     units : SLAB1_UNITS;

    uint64_t second = units > SLAB1_UNITS ?
                      (units < SLAB2_UNITS ?
                      units - SLAB1_UNITS : 100ULL) : 0ULL;

    uint64_t third = units > SLAB2_UNITS ?
                     units - SLAB2_UNITS : 0ULL;

    int64_t energy =
        (int64_t)first * RATE1_PAISE +
        (int64_t)second * RATE2_PAISE +
        (int64_t)third * RATE3_PAISE;

    int64_t total = energy + FIXED_CHARGE_PAISE;

    printf("Previous Reading: %u\n", previous);
    printf("Current Reading: %u\n", current);

    printf("Units Consumed: %" PRIu64 "\n", units);

    printf("Energy Charge: Rs %" PRId64 ".%02" PRId64 "\n",
           energy / 100, energy % 100);

    printf("Total Bill: Rs %" PRId64 ".%02" PRId64 "\n",
           total / 100, total % 100);

    return 0;
}