#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void PrintLength()
{
    printf("Please enter length:\n");
}

void PrintArray()
{
    printf("Please enter array:\n");
}

void PrintSum()
{
    printf("Please enter sum:\n");
}

void PrintExist()
{
    printf("Such elements do exist.");
}

void PrintDoNotExist()
{
    printf("Such elements do not exist.");
}

int maxIndex(int *arr, int size)
{
    int max = 0;
    for (int i = 1; i < size; i++)
    {
        if (*(arr + i) > *(arr + max))
            max = i;
    }
    return max;
}

void swap(int *arr, int i, int j)
{
    int tmp = *(arr + i);
    *(arr + i) = *(arr + j);
    *(arr + j) = tmp;
}

void sortByMax(int *arr, int size)
{
    for (int i = size - 1; i > 0; i--)
    {
        int index = maxIndex(arr, size);
        swap(arr, i, index);
    }
}

bool doesSumExist(int *arr, int size, int sum)
{
    for (int i = 0; i < size; i++)
    {
        int j = i + 1, f = size - 1;
        while (j < f)
        {
            int currentSum = *(arr + i) + *(arr + j) + *(arr + f);
            if (currentSum == sum)
                return true;
            else if (currentSum < sum)
                f--;
            else
                j++;
        }
    }
    return false;
}

int main()
{
    // Receive the array
    int size = 0, sum = 0;
    PrintLength();
    scanf("%d", &size);
    // Get the array itself.
    PrintArray();
    int *arr = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        scanf("%d", arr + i);
    }
    PrintSum();
    scanf("%d", &sum);
    sortByMax(arr, size);
    if (doesSumExist(arr, size, sum))
        PrintExist();
    else
        PrintDoNotExist();

    return 0;
}