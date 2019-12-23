#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(0));
    int n = rand() % 12 + 1;
    printf("%d\n", n);
    for (int i = 0; i < n * n * n * n * n * n; i++)
    {
        int num1 = (rand() - (RAND_MAX / 2)) % (n + 1) + 1;
        int num2 = (rand() - (RAND_MAX / 2)) % (n + 1) + 1;
        printf("%d ", num1);
        printf("%d\n", num2);
    }
    return 0;
}