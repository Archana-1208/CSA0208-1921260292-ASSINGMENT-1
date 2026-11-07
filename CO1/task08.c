#include <stdio.h>

int main(void)
{
    int household = 1204;
    int units = 150;

    long long total_paise = 5000LL + (long long)units * 225LL;

    printf("Household Number: %d\n", household);

    printf("Units Consumed: %d\n", units);

    printf("Total Bill: Rs %lld.%02lld\n",
           total_paise / 100,
           total_paise % 100);

    return 0;
}