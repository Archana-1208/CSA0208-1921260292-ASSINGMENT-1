#include <stdio.h>
#include <limits.h>

int main(void)
{
    printf("5 / 2 = %d\n", 5 / 2);

    printf("5 / 2.0 = %.2f\n", 5 / 2.0);

    printf("0.1 added 10 times = %.9f\n",
           0.1f + 0.1f + 0.1f + 0.1f + 0.1f +
           0.1f + 0.1f + 0.1f + 0.1f + 0.1f);

    printf("Integer Paise = %lld\n", 10LL * 10);

    printf("INT_MAX = %d\n", INT_MAX);

    printf("LLONG_MAX = %lld\n", LLONG_MAX);

    return 0;
}