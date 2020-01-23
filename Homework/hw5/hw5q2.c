#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define DIM 4
#define MAX_STEPS DIM *DIM
#define DEBUG true

void PrintWelcomeMessage()
{
    printf("Please enter road matrix:\n");
}

void PrintSourceCityMessage()
{
    printf("Please enter source city:\n");
}

void PrintDestinationCityMessage()
{
    printf("Please enter destination city:\n");
}

void PrintSpace()
{
    printf(" ");
}

void PrintNumber(int num)
{
    printf("%d", num);
}

int main();
int calculate_road(int source, int dest, int origin, int map[DIM][DIM], int path[DIM], int steps, int *finalSteps, int currentPathLength, int *minimumLength);

void copy_arr(int *arr, int *to, int size);
void receive_road(int map[DIM][DIM], int *source, int *dest);
void printPath(int path[DIM], int steps);
int isInPath(int path[DIM], int steps, int city);

int main()
{
    int map[DIM][DIM] = {{0}}, source = 0, dest = 0;
    receive_road(map, &source, &dest);
    // Get the route.
    int currentPath[DIM] = {-1}, finalStepsCount = 0, direct = map[source][dest];
    calculate_road(source, dest, source, map, currentPath, 0, &finalStepsCount, 0, &direct);
    printf("The shortest path is:\n");
    printPath(currentPath, finalStepsCount);
    return 0;
}

int calculate_road(int source, int dest, int origin, int map[DIM][DIM], int path[DIM], int steps, int *finalSteps, int currentPathLength, int *minimumLength)
{
    if (currentPathLength > *minimumLength || isInPath(path, steps, source))
    {
        return EOF;
    }

    if (source == dest)
    {
        *minimumLength = currentPathLength;
        *finalSteps = steps;
        path[steps] = dest;
        return currentPathLength;
    }

    path[steps] = source;
    int minPath[DIM] = {0};
    copy_arr(path, minPath, DIM);
    for (int i = 0; i < DIM; i++)
    {
        if (i == source)
            continue;

        int currentLength = calculate_road(i, dest, origin, map, path, steps + 1, finalSteps, currentPathLength + map[source][i], minimumLength);
        if (currentLength == EOF)
            continue;
        else if (currentLength <= *minimumLength && path[steps + 1] == i)
        {
            // We found minimum length path. Make it the path we want.
            // Copy the array to minpath.
            DEBUG ? printf("Minimun length with source %d, i %d at length %d\n", source, i, currentLength) : 0;
            copy_arr(path, minPath, DIM);
        }
    }

    return currentPathLength;
}

void receive_road(int map[DIM][DIM], int *source, int *dest)
{
    PrintWelcomeMessage();
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            scanf("%d", &map[i][j]);
        }
    }
    PrintSourceCityMessage();
    scanf("%d", source);
    PrintDestinationCityMessage();
    scanf("%d", dest);
}

void copy_arr(int *arr, int *to, int size)
{
    for (int i = 0; i < size; i++)
    {
        *(to + i) = *(arr + i);
    }
}

int isInPath(int path[DIM], int steps, int city)
{
    for (int i = 0; i < steps; i++)
    {
        if (path[i] == city)
            return 1;
    }
    return 0;
}

void printPath(int path[DIM], int steps)
{
    for (int i = 0; i <= steps; i++)
    {
        PrintNumber(path[i]);
        PrintSpace();
    }
}
