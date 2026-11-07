#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void)
{
    const long long paise_per_bill = 1000000LL;

    const int counts[] = {4000, 60000, 800000};

    printf("Size of int = %zu bytes\n", sizeof(int));

    printf("Size of long = %zu bytes\n", sizeof(long));

    printf("Size of long long = %zu bytes\n", sizeof(long long));

    printf("Size of float = %zu bytes\n", sizeof(float));

    printf("Size of double = %zu bytes\n", sizeof(double));

    printf("\nINT_MAX = %d\n", INT_MAX);

    printf("LONG_MAX = %ld\n", LONG_MAX);

    printf("LLONG_MAX = %lld\n", LLONG_MAX);

    printf("FLT_MANT_DIG = %d\n", FLT_MANT_DIG);

    printf("DBL_MANT_DIG = %d\n", DBL_MANT_DIG);

    printf("\nDistrict Bill Totals:\n");

    for (int i = 0; i < 3; i++)
    {
        long long total = paise_per_bill * counts[i];

        printf("%d bills = %lld paise\n",
               counts[i], total);
    }

    return 0;
}