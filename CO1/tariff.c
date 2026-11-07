#include <stdio.h>
#include "tariff.h"

long compute_bill(int units)
{
    long paise = FIXED_CHARGE_PAISE;

    int first = units < SLAB1_UNITS ?
                units : SLAB1_UNITS;

    int second = units > SLAB1_UNITS ?
                 (units < SLAB2_UNITS ?
                 units - SLAB1_UNITS :
                 SLAB2_UNITS - SLAB1_UNITS) : 0;

    int third = units > SLAB2_UNITS ?
                units - SLAB2_UNITS : 0;

    paise += (long)first * RATE1_PAISE;
    paise += (long)second * RATE2_PAISE;
    paise += (long)third * RATE3_PAISE;

#ifdef DEBUG
    printf("[DEBUG] Units = %d\n", units);
    printf("[DEBUG] Bill in paise = %ld\n", paise);
#endif

    return paise;
}