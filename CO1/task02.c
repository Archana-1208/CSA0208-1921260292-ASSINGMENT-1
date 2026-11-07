#include <stdio.h>
#include <limits.h>
#include <float.h>

typedef unsigned short meter_t;

unsigned int consumption(meter_t previous, meter_t current)
{
    return (unsigned int)(meter_t)(current - previous);
}

int main(void)
{
    printf("Size of meter_t: %zu bytes\n", sizeof(meter_t));
    printf("Maximum meter reading: %u\n", (unsigned)USHRT_MAX);

    printf("Normal Consumption: %u units\n",
           consumption(1200, 1530));

    printf("Rollover Consumption: %u units\n",
           consumption(65400, 120));

    printf("Size of float: %zu bytes\n", sizeof(float));
    printf("Size of long long: %zu bytes\n", sizeof(long long));

    printf("FLT_MAX = %g\n", (double)FLT_MAX);
    printf("LLONG_MAX = %lld\n", LLONG_MAX);

    return 0;
}