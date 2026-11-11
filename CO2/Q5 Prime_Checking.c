#include <stdio.h>

unsigned long checks = 0;

int is_prime(unsigned long n)
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

int main(void)
{
    unsigned long tickets[] = {97, 100, 7919, 1000003};

    for (int k = 0; k < 4; k++)
    {
        int p = is_prime(tickets[k]);

        printf("%8lu %-9s divisions = %lu\n",
               tickets[k],
               p ? "prime" : "not prime",
               checks);
    }

    return 0;
}