#include <stdio.h>
#include <stdint.h>

#define MAX_RECORDS 40000
#define MAX_WH_PER_RECORD 1000000ULL
#define MAX_RATE 1000000LL

int is_peak(int hour)
{
    return hour >= 18 && hour < 22;
}

int main(void)
{
    FILE *cfg = fopen("tariff.cfg", "r");

    long long fixed_paise, offpeak_rate;

    uint64_t peak_wh = 0;
    uint64_t offpeak_wh = 0;

    int n;

    if (cfg == NULL)
    {
        puts("Cannot open tariff.cfg");
        return 1;
    }

    if (fscanf(cfg, "%lld %lld",
               &fixed_paise, &offpeak_rate) != 2 ||
        fixed_paise < 0 ||
        offpeak_rate < 0 ||
        offpeak_rate > MAX_RATE)
    {
        puts("Invalid tariff configuration");
        fclose(cfg);
        return 1;
    }

    fclose(cfg);

    printf("Enter number of interval records: ");

    if (scanf("%d", &n) != 1 ||
        n < 0 || n > MAX_RECORDS)
    {
        puts("Invalid record count");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        int hour, minute;
        unsigned long long wh;

        printf("Enter hour minute Wh for record %d: ", i + 1);

        if (scanf("%d %d %llu",
                  &hour, &minute, &wh) != 3)
        {
            puts("Invalid input");
            return 1;
        }

        if (hour < 0 || hour > 23 ||
            minute < 0 || minute > 59 ||
            wh > MAX_WH_PER_RECORD)
        {
            puts("Invalid interval record");
            return 1;
        }

        if (is_peak(hour))
            peak_wh += (uint64_t)wh;
        else
            offpeak_wh += (uint64_t)wh;
    }

    /*
       Off-peak charge:
       Wh * rate / 1000

       Peak charge:
       Wh * rate * 120 / 100 / 1000

       Round the final energy charge to nearest paise.
    */

    uint64_t energy_numerator =
        offpeak_wh * (uint64_t)offpeak_rate * 100ULL
        + peak_wh * (uint64_t)offpeak_rate * 120ULL;

    long long energy_paise =
        (long long)((energy_numerator + 50000ULL) / 100000ULL);

    long long total_paise = fixed_paise + energy_paise;

    printf("\nOff-Peak Energy: %llu Wh\n",
           (unsigned long long)offpeak_wh);

    printf("Peak Energy: %llu Wh\n",
           (unsigned long long)peak_wh);

    printf("Energy Charge: Rs %lld.%02lld\n",
           energy_paise / 100,
           energy_paise % 100);

    printf("Fixed Charge: Rs %lld.%02lld\n",
           fixed_paise / 100,
           fixed_paise % 100);

    printf("Total Bill: Rs %lld.%02lld\n",
           total_paise / 100,
           total_paise % 100);

    return 0;
}