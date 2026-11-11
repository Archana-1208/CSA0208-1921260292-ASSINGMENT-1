#include <stdio.h>

unsigned long checks = 0;

int prime_original(unsigned long n)
{
    checks = 0;

    if (n < 2)
        return 0;

    for (unsigned long i = 2; i < n; i++)
    {
        checks++;

        if (n % i == 0)
            return 0;
    }

    return 1;
}

int prime_sqrt(unsigned long n)
{
    checks = 0;

    if (n < 2)
        return 0;

    for (unsigned long i = 2; i <= n / i; i++)
    {
        checks++;

        if (n % i == 0)
            return 0;
    }

    return 1;
}

int prime_odd(unsigned long n)
{
    checks = 0;

    if (n < 2)
        return 0;

    if (n == 2)
        return 1;

    checks++;

    if (n % 2 == 0)
        return 0;

    for (unsigned long i = 3; i <= n / i; i += 2)
    {
        checks++;

        if (n % i == 0)
            return 0;
    }

    return 1;
}

int main(void)
{
    unsigned long values[] = {97, 100, 7919, 1000003};

    for (int k = 0; k < 4; k++)
    {
        unsigned long n = values[k];

        int p = prime_original(n);
        unsigned long old_count = checks;

        p = prime_sqrt(n);
        unsigned long sqrt_count = checks;

        p = prime_odd(n);
        unsigned long odd_count = checks;

        printf("%lu %s | original=%lu sqrt=%lu odd-only=%lu\n",
               n,
               p ? "prime" : "not prime",
               old_count, sqrt_count, odd_count);
    }

    return 0;
}