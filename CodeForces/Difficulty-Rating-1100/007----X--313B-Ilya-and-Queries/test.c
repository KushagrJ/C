#include <stdio.h>





/* Exceeds time limit -

#include <stdio.h>


int main(void)
{

    char s[100002];
    fgets(s + 1, 100001, stdin);

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++)
    {
        int l, r;
        scanf("%d %d", &l, &r);

        int answer = 0;

        for (int j = l; j < r; j++)
        {
            if (s[j] == s[j + 1])
                (answer)++;
        }

        printf("%d\n", answer);
    }

    return 0;

}

*/
