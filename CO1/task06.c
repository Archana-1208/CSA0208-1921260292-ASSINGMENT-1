#include <stdio.h>

int main(void)
{
    int household;
    unsigned int units;
    long long total_paise;

    printf("Enter household number and units: ");

    if (scanf("%d %u", &household, &units) != 2)
    {
        printf("Invalid input. Enter numeric values.\n");
        return 1;
    }

    if (units > 1000000U)
    {
        printf("Units are outside the accepted range.\n");
        return 1;
    }

    total_paise = 5000LL + (long long)units * 225LL;

    printf("Household: %d\n", household);

    printf("Sample Total: Rs %lld.%02lld\n",
           total_paise / 100,
           total_paise % 100);

    return 0;
}
