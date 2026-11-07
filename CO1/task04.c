#include <stdio.h>

#define RUPEES_TO_PAISE(x) ((long long)(x) * 100LL)

#define SQUARE(x) ((x) * (x))

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

static inline int square_int(int x)
{
    return x * x;
}

static inline int max_int(int a, int b)
{
    return (a > b) ? a : b;
}

int main(void)
{
    int a = 4;
    int i = 3;
    int j = 8;

    printf("Rupees to Paise: %lld\n",
           RUPEES_TO_PAISE(50));

    printf("Square of a+1: %d\n", SQUARE(a + 1));

    printf("Maximum value: %d\n", MAX(i, j));

    printf("Inline Square: %d\n", square_int(a + 1));

    printf("Inline Maximum: %d\n", max_int(i, j));

    return 0;
}