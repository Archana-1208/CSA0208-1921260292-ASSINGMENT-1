#include <stdio.h>

int main(void)
{
    double price[] = {120.0, 75.0, 100.0};
    int qty[] = {2, 3, 12};
    int senior[] = {1, 0, 1};

    for (int i = 0; i < 3; i++)
    {
        double gross = price[i] * qty[i];
        double discount = senior[i] ? gross * 0.15 : 0.0;
        double taxable = gross - discount;
        double tax = taxable * 0.05;
        double total = taxable + tax;
        double net = (total > 1000.0) ? total - 50.0 : total;

        printf("Bill %d: gross=%.2f discount=%.2f "
               "tax=%.2f total=%.2f net=%.2f\n",
               i + 1, gross, discount, tax, total, net);
    }

    return 0;
}