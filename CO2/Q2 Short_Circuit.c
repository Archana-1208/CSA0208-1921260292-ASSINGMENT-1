#include <stdio.h>

int calls = 0;

int verify_card(int valid)
{
    calls++;
    return valid;
}

int main(void)
{
    int senior = 0, eligible = 1, valid_card = 1;

    calls = 0;

    if ((senior && eligible) || verify_card(valid_card))
        puts("Concession granted");

    printf("OR arrangement calls = %d\n", calls);

    calls = 0;

    if (verify_card(valid_card) || (senior && eligible))
        puts("Concession granted");

    printf("Reversed OR calls = %d\n", calls);

    calls = 0;

    if (senior && verify_card(valid_card))
        puts("Senior check passed");

    printf("AND arrangement calls = %d\n", calls);

    return 0;
}