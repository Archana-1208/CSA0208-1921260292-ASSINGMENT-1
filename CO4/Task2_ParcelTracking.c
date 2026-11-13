
#include <stdio.h>
#include <string.h>

struct date {
    int day, month, year;
};

struct address {
    char city[20];
    int pincode;
};

struct parcel {
    int id;
    float weight;
    struct address to;
    struct date booked;
};

void print_parcel(const struct parcel *p) {
    printf("%d %.1f kg %s-%d %02d/%02d/%d\n",
           p->id,
           p->weight,
           p->to.city,
           p->to.pincode,
           p->booked.day,
           p->booked.month,
           p->booked.year);
}

void sort_by_weight(struct parcel p[], int n) {
    int min;
    struct parcel temp;

    for (int i = 0; i < n - 1; i++) {
        min = i;

        for (int j = i + 1; j < n; j++) {
            if (p[j].weight < p[min].weight) {
                min = j;
            }
        }

        if (min != i) {
            temp = p[i];
            p[i] = p[min];
            p[min] = temp;
        }
    }
}

int main(void) {
    struct parcel list[3] = {
        {501, 4.5f, {"Madurai", 625001}, {12, 10, 2026}},
        {502, 1.2f, {"Chennai", 600077}, {12, 10, 2026}},
        {503, 2.8f, {"Coimbatore", 641001}, {13, 10, 2026}}
    };

    sort_by_weight(list, 3);

    for (int i = 0; i < 3; i++) {
        print_parcel(&list[i]);
    }

    printf("\nReceiver PIN: %d\n", list[2].to.pincode);

    struct parcel *ptr = list;
    printf("Receiver PIN using pointer: %d\n",
           (ptr + 2)->to.pincode);

    printf("Bytes copied in one swap: %zu\n",
           sizeof(struct parcel));

    return 0;
}
