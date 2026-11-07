#include <stdio.h>
#include "tariff.h"

int main(void)
{
    int units = 150;

    long total = compute_bill(units);

    printf("Bill = Rs %ld.%02ld\n",
           total / 100, total % 100);

    return 0;
}