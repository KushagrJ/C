// See https://stackoverflow.com/questions/70985365/

#include <stdio.h>
#include <stdbool.h>


int main(void)
{

    int a[100000], b[100000];

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d %d", &a[i], &b[i]);

    bool alex_is_correct = false;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (((a[i] > a[j]) && (b[i] < b[j])) ||
                    ((a[i] < a[j]) && (b[i] > b[j])))
            {
                alex_is_correct = true;
                break;
            }
        }

        if (alex_is_correct)
            break;
    }

    if (alex_is_correct)
        printf("Happy Alex\n");
    else
        printf("Poor Alex\n");

    return 0;

}
