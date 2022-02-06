#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct laptop
{
    int price;
    int quality;
};


int qsort_compare(const void*, const void*);


int main(void)
{

    struct laptop laptops[100000];

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d %d", &(laptops[i].price), &(laptops[i].quality));

    qsort(laptops, n, sizeof (struct laptop), qsort_compare);

    bool alex_is_correct = false;

    for (int i = 0; i < n - 1; i++)
    {
        if (laptops[i].quality > laptops[i + 1].quality)
        {
            alex_is_correct = true;
            break;
        }
    }

    if (alex_is_correct)
        printf("Happy Alex\n");
    else
        printf("Poor Alex\n");

    return 0;

}


int qsort_compare(const void* a, const void* b)
{

    int x = ((const struct laptop*) a)->price;
    int y = ((const struct laptop*) b)->price;

    if (x > y)
        return 1;
    else if (x == y)
        return 0;
    else
        return -1;

}
