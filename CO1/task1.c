#include <stdio.h>

#define FIXED_CHARGE 5000LL
#define RATE1 0LL
#define RATE2 225LL
#define RATE3 450LL

int main(void)
{
    int household = 1204;
    char category = 'D';
    int previous = 1200;
    int current = 1350;

    int units = current - previous;

    int first = units < 100 ? units : 100;
    int second = units > 100 ?
                 (units < 200 ? units - 100 : 100) : 0;
    int third = units > 200 ? units - 200 : 0;

    long long energy = first * RATE1
                     + second * RATE2
                     + third * RATE3;

    long long total = energy + FIXED_CHARGE;

    printf("Household Number: %d\n", household);
    printf("Category: %c\n", category);
    printf("Previous Reading: %d\n", previous);
    printf("Current Reading: %d\n", current);
    printf("Units Consumed: %d\n", units);
    printf("Energy Charge: Rs %lld.%02lld\n",
           energy / 100, energy % 100);
    printf("Fixed Charge: Rs 50.00\n");
    printf("Total Amount: Rs %lld.%02lld\n",
           total / 100, total % 100);

    return 0;
}