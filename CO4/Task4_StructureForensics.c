
#include <stdio.h>

struct account {
    int number;
    float balance;
};

void addInterest(struct account *a, float rate) {
    printf("Address inside function: %p\n", (void *)a);

    a->balance = a->balance +
                 a->balance * rate / 100;
}

int main(void) {
    struct account list[3] = {
        {101, 5000},
        {102, 12000},
        {103, 800}
    };

    struct account *p = list;

    printf("Address in main: %p\n", (void *)p);

    for (int i = 0; i < 3; i++) {
        addInterest(&list[i], 4);
    }

    printf("\nUpdated Account Details:\n");

    for (int i = 0; i < 3; i++) {
        printf("Account Number: %d\n", p[i].number);
        printf("Balance: %.2f\n", p[i].balance);
    }

    return 0;
}
