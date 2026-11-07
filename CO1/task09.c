#include <stdio.h>
#include <limits.h>

#define SLAB1_UNITS 100U
#define SLAB2_UNITS 200U

#define RATE1_PAISE 0LL
#define RATE2_PAISE 225LL
#define RATE3_PAISE 450LL

#define FIXED_CHARGE_PAISE 5000LL

#define METER_MAX 65535U
#define ROLLOVER_HIGH 60000U
#define ROLLOVER_LOW 5535U

typedef unsigned short meter_t;

static unsigned int used_units(meter_t previous, meter_t current)
{
    return (unsigned int)(meter_t)(current - previous);
}

static long long energy_charge(unsigned int units)
{
    unsigned int first = units < SLAB1_UNITS ?
                         units : SLAB1_UNITS;

    unsigned int second = units > SLAB1_UNITS ?
                          (units < SLAB2_UNITS ?
                          units - SLAB1_UNITS :
                          SLAB2_UNITS - SLAB1_UNITS) : 0U;

    unsigned int third = units > SLAB2_UNITS ?
                         units - SLAB2_UNITS : 0U;

    return (long long)first * RATE1_PAISE
         + (long long)second * RATE2_PAISE
         + (long long)third * RATE3_PAISE;
}

int main(void)
{
    int household;
    char category;

    unsigned int previous, current, units;

    long long energy, total;

    if (USHRT_MAX != 65535U)
    {
        puts("This program requires a 16-bit unsigned short.");
        return 1;
    }

    printf("Enter household number, category, previous and current readings: ");

    if (scanf("%d %c %u %u",
              &household, &category,
              &previous, &current) != 4)
    {
        puts("Invalid input.");
        return 1;
    }

    if (previous > METER_MAX || current > METER_MAX)
    {
        puts("Invalid meter reading.");
        return 1;
    }

    if (current < previous &&
        !(previous >= ROLLOVER_HIGH && current <= ROLLOVER_LOW))
    {
        puts("Invalid decrease: rollover is not plausible.");
        return 1;
    }

    units = used_units((meter_t)previous, (meter_t)current);

    energy = energy_charge(units);

    total = energy + FIXED_CHARGE_PAISE;

    printf("\nHousehold: %d\n", household);
    printf("Category: %c\n", category);
    printf("Units Consumed: %u\n", units);

    printf("Energy Charge: Rs %lld.%02lld\n",
           energy / 100, energy % 100);

    printf("Fixed Charge: Rs 50.00\n");

    printf("Total Bill: Rs %lld.%02lld\n",
           total / 100, total % 100);

    return 0;
}