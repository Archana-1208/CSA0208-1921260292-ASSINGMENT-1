
#include <stdio.h>
#include <string.h>

#define MAX 100

struct Date {
    int day, month, year;
};

struct BloodPressure {
    int systolic;
    int diastolic;
};

struct Patient {
    char name[50];
    int age;
    char phone[11];
    struct BloodPressure bp;
    struct Date visitDate;
};

void addPatient(struct Patient *p, const char n[],
                int a, const char ph[],
                int s, int d, struct Date date) {
    strcpy(p->name, n);
    p->age = a;
    strcpy(p->phone, ph);
    p->bp.systolic = s;
    p->bp.diastolic = d;
    p->visitDate = date;
}

int main() {
    struct Patient patients[MAX];
    int count = 0;

    if (count < MAX) {
        struct Date date = {13, 11, 2026};

        addPatient(&patients[count], "Arun", 25,
                   "9876543210", 120, 80, date);
        count++;
    }

    for (int i = 0; i < count; i++) {
        printf("Patient Name: %s\n", patients[i].name);
        printf("Age: %d\n", patients[i].age);
        printf("Phone: %s\n", patients[i].phone);
        printf("Blood Pressure: %d/%d\n",
               patients[i].bp.systolic,
               patients[i].bp.diastolic);
        printf("Visit Date: %02d/%02d/%d\n",
               patients[i].visitDate.day,
               patients[i].visitDate.month,
               patients[i].visitDate.year);
    }

    return 0;
}
