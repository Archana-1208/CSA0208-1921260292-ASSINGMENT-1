#include <stdio.h>

int main(void)
{
    double balance = 10000.00;
    const double rate = 0.02;
    const double payment = 2000.00;
    double total_interest = 0.0;
    int month = 0;
    const int LIMIT = 360;

    if (balance <= 0.0 || payment <= 0.0 ||
        rate < 0.0 || rate >= 1.0)
    {
        puts("Invalid loan inputs.");
        return 1;
    }

    if (payment <= balance * rate)
    {
        puts("Repayment does not exceed monthly interest; loan will not amortize.");
        return 1;
    }

    while (balance > 0.005)
    {
        if (month >= LIMIT)
        {
            puts("Safety limit reached: review the repayment plan.");
            break;
        }

        double interest = balance * rate;
        double due = balance + interest;
        double actual_payment = (payment < due) ? payment : due;
        double closing = due - actual_payment;

        total_interest += interest;
        month++;

        printf("%2d opening=%9.2f interest=%7.2f "
               "paid=%9.2f closing=%9.2f\n",
               month, balance, interest, actual_payment, closing);

        balance = (closing < 0.005) ? 0.0 : closing;
    }

    if (balance <= 0.005)
        printf("Repaid in %d months; total interest = Rs %.2f\n",
               month, total_interest);

    return 0;
}