#include <stdio.h>

#define SLAB1_UNITS 100
#define SLAB2_UNITS 200

#define RATE1_PAISE 0
#define RATE2_PAISE 225
#define RATE3_PAISE 450

#define FIXED_CHARGE_PAISE 5000L

long compute_bill(int units)
{
    long paise = FIXED_CHARGE_PAISE;

    int first = units < SLAB1_UNITS ? units : SLAB1_UNITS;

    int second = units > SLAB1_UNITS ?
                 (units < SLAB2_UNITS ?
                 units - SLAB1_UNITS :
                 SLAB2_UNITS - SLAB1_UNITS) : 0;

    int third = units > SLAB2_UNITS ?
                units - SLAB2_UNITS : 0;

    paise += (long)first * RATE1_PAISE;
    paise += (long)second * RATE2_PAISE;
    paise += (long)third * RATE3_PAISE;

    return paise;
}

int main(void)
{
    int tests[] = {0, 100, 150, 200, 350};

    int n = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < n; i++)
    {
        long total = compute_bill(tests[i]);

        printf("%d units = Rs %ld.%02ld\n",
               tests[i], total / 100, total % 100);
    }

    return 0;
}