
#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 10
#define MAX_SALES 20

struct Date {
    int day, month, year;
};

struct Packaged {
    float price;
    struct Date expiry;
    int stock;
};

struct Cooked {
    float price;
    char preparedTime[10];
    int stock;
};

struct Combo {
    float price;
    int count;
    int itemID[3];
    int quantity[3];
};

enum ItemType {
    PACKAGED, COOKED, COMBO
};

struct Item {
    int id;
    char name[30];
    enum ItemType type;

    union {
        struct Packaged packaged;
        struct Cooked cooked;
        struct Combo combo;
    } details;
};

struct Sale {
    int id;
    int quantity;
    float revenue;
};

struct Item items[MAX_ITEMS];
struct Sale sales[MAX_SALES];

int itemCount = 3;
int saleCount = 0;

/* Find item using ID */
int findItem(int id) {
    for (int i = 0; i < itemCount; i++) {
        if (items[i].id == id)
            return i;
    }
    return -1;
}

/* Get item price */
float getPrice(struct Item *p) {
    switch (p->type) {
        case PACKAGED:
            return p->details.packaged.price;

        case COOKED:
            return p->details.cooked.price;

        case COMBO:
            return p->details.combo.price;
    }
    return 0;
}

/* Check available stock */
int checkStock(struct Item *p, int qty) {
    if (p->type == PACKAGED)
        return p->details.packaged.stock >= qty;

    if (p->type == COOKED)
        return p->details.cooked.stock >= qty;

    if (p->type == COMBO) {
        for (int i = 0; i < p->details.combo.count; i++) {
            int index = findItem(
                p->details.combo.itemID[i]);

            if (index == -1 ||
                !checkStock(&items[index],
                p->details.combo.quantity[i] * qty))
                return 0;
        }
        return 1;
    }

    return 0;
}

/* Update stock */
void updateStock(struct Item *p, int qty) {
    if (p->type == PACKAGED) {
        p->details.packaged.stock -= qty;
    }
    else if (p->type == COOKED) {
        p->details.cooked.stock -= qty;
    }
    else if (p->type == COMBO) {
        for (int i = 0; i < p->details.combo.count; i++) {
            int index = findItem(
                p->details.combo.itemID[i]);

            updateStock(&items[index],
                p->details.combo.quantity[i] * qty);
        }
    }
}

/* Record a sale */
void recordSale(int id, int qty) {
    int index = findItem(id);

    if (index == -1 || qty <= 0) {
        printf("Invalid item or quantity!\n");
        return;
    }

    struct Item *p = &items[index];

    if (!checkStock(p, qty)) {
        printf("Insufficient stock for %s!\n", p->name);
        return;
    }

    float revenue = getPrice(p) * qty;

    updateStock(p, qty);

    if (saleCount < MAX_SALES) {
        sales[saleCount].id = id;
        sales[saleCount].quantity = qty;
        sales[saleCount].revenue = revenue;
        saleCount++;
    }

    printf("Sale successful: %s, Revenue = Rs. %.2f\n",
           p->name, revenue);
}

/* Convert date into day number */
int dateToDays(struct Date d) {
    int monthDays[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    int days = d.year * 365;

    for (int y = 1; y < d.year; y++) {
        if ((y % 400 == 0) ||
            (y % 4 == 0 && y % 100 != 0))
            days++;
    }

    for (int m = 1; m < d.month; m++) {
        days += monthDays[m - 1];

        if (m == 2 &&
            ((d.year % 400 == 0) ||
             (d.year % 4 == 0 && d.year % 100 != 0)))
            days++;
    }

    return days + d.day;
}

/* Expiry warning */
void expiryWarning(struct Date today) {
    printf("\nExpiry Warnings:\n");

    for (int i = 0; i < itemCount; i++) {
        if (items[i].type == PACKAGED) {
            struct Date e = items[i].details.packaged.expiry;

            int difference =
                dateToDays(e) - dateToDays(today);

            if (difference >= 0 && difference <= 2) {
                printf("%s is expiring within two days!\n",
                       items[i].name);
            }
        }
    }
}

/* Sort sales by revenue */
void sortSales(void) {
    struct Sale temp;

    for (int i = 0; i < saleCount - 1; i++) {
        for (int j = i + 1; j < saleCount; j++) {
            if (sales[i].revenue < sales[j].revenue) {
                temp = sales[i];
                sales[i] = sales[j];
                sales[j] = temp;
            }
        }
    }
}

/* Print sales summary */
void printSummary(void) {
    sortSales();

    printf("\nSales Summary (Highest Revenue First):\n");

    for (int i = 0; i < saleCount; i++) {
        printf("Item ID: %d Quantity: %d Revenue: Rs. %.2f\n",
               sales[i].id,
               sales[i].quantity,
               sales[i].revenue);
    }
}

int main(void) {
    struct Date today = {13, 11, 2026};

    /* Packaged item */
    items[0].id = 101;
    strcpy(items[0].name, "Milk");
    items[0].type = PACKAGED;
    items[0].details.packaged.price = 30;
    items[0].details.packaged.expiry =
        (struct Date){15, 11, 2026};
    items[0].details.packaged.stock = 10;

    /* Cooked item */
    items[1].id = 102;
    strcpy(items[1].name, "Sandwich");
    items[1].type = COOKED;
    items[1].details.cooked.price = 50;
    strcpy(items[1].details.cooked.preparedTime, "10:30 AM");
    items[1].details.cooked.stock = 5;

    /* Combo item */
    items[2].id = 103;
    strcpy(items[2].name, "Combo Meal");
    items[2].type = COMBO;
    items[2].details.combo.price = 75;
    items[2].details.combo.count = 2;

    items[2].details.combo.itemID[0] = 101;
    items[2].details.combo.quantity[0] = 1;

    items[2].details.combo.itemID[1] = 102;
    items[2].details.combo.quantity[1] = 1;

    printf("COLLEGE CANTEEN INVENTORY\n\n");

    recordSale(101, 2);
    recordSale(101, 20);
    recordSale(102, 1);
    recordSale(103, 1);

    expiryWarning(today);

    printSummary();

    return 0;
}
