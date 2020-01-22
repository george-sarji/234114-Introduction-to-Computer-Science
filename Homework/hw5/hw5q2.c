#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 4
#define MAX_STEPS DIM *DIM

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
int calculate_route(int source, int dest, int origin, int currentLength, int steps, int map[DIM][DIM], int used[DIM], int path[DIM], int *stepsCount);
void copy_arr(int *arr, int *to, int size);
void receive_road(int map[DIM][DIM], int *source, int *dest);
void printPath(int path[DIM], int steps);
int isInPath(int path[DIM], int steps, int city);

int main()
{
    int map[DIM][DIM] = {{0}}, source = 0, dest = 0;
    receive_road(map, &source, &dest);
    // Print map for debug

    // printf("MAP: \n\n");
    // for (int i = 0; i < DIM; i++)
    // {
    //     for (int j = 0; j < DIM; j++)
    //     {
    //         PrintNumber(map[i][j]);
    //         PrintSpace();
    //     }
    //     printf("\n");
    // }

    // Get the route.
    int currentPath[DIM] = {-1}, used[DIM] = {0}, finalStepsCount = 0;
    calculate_route(source, dest, source, 0, 0, map, used, currentPath, &finalStepsCount);
    printf("The shortest path is:\n");
    // for (int i = 0; i <= finalStepsCount; i++)
    // {
    //     PrintNumber(currentPath[i]);
    // }
    printPath(currentPath, finalStepsCount);
    // printf("Length: %d, steps %d\n", length, finalStepsCount);
    return 0;
}

int calculate_route(int source, int dest, int origin, int currentLength, int steps, int map[DIM][DIM], int used[DIM], int path[DIM], int *stepsCount)
{
    // if (source == dest)
    // {
    //     path[steps] = source;
    //     *stepsCount = steps;
    //     printf("Arrived at dest in %d steps through path: ", steps);
    //     printPath(path, steps);
    //     return currentLength;
    // }
    // if (currentLength > map[origin][dest] || steps > DIM || isInPath(path, steps, source))
    //     return -1;

    // // Add current source to path.
    // path[steps] = source;
    // used[source] = 1;
    // int minLength = map[source][dest], minPath[DIM] = {source, dest}, city;
    // for (int i = 0; i < DIM; i++)
    // {
    //     // Check if checking with current city.
    //     if (source == i || isInPath(path, steps, i))
    //         continue;

    //     // Check the length.
    //     int currLength = calculate_route(i, dest, origin, currentLength + map[source][i], steps + 1, map, used, path, stepsCount);
    //     if (currLength == -1)
    //         continue;
    //     printf("Called check from %d between %d and %d: %d\n", source,
    //            i, dest, currLength);
    //     if (steps == 0 || currLength < minLength)
    //     {
    //         printf("Steps: %d, ", steps);
    //         printf("Found min length between %d and %d through %d: length %d\n", source, dest, i, currLength);
    //         printf("Path: ");
    //         printPath(path, steps);
    //         minLength = currLength;
    //         copy_arr(path, minPath, DIM);
    //     }
    // }

    // path = minPath;
    // return minLength;

    if (source == dest)
    {
        // Arrived. Make sure you add dest to path and set steps.
        *stepsCount = steps;
        path[steps] = source;
        // Return the current length of the path.
        // printf("Arrived at dest with length %d.\n", currentLength);
        // printf("Path to dest: ");
        // printPath(path, steps);
        return currentLength;
    }
    // Check if the path taken is legal.
    if (currentLength > map[origin][dest] || steps >= DIM || isInPath(path, steps, source))
    {
        // Return error.
        return EOF;
    }

    // We have a legal attempt. Check.
    // Add current city to path.
    path[steps] = source;
    used[source] = 1;
    // Go over all possibilities.
    int minLength = map[source][dest] + currentLength, minPath[DIM] = {0};
    copy_arr(path, minPath, steps);
    minPath[steps] = source;
    minPath[steps + 1] = dest;
    for (int i = 0; i < DIM; i++)
    {
        // Do not iterate over same city.
        if (source == i)
            continue;

        // Get possible length for current path.
        int currLength = calculate_route(i, dest, origin, currentLength + map[source][i], steps + 1, map, used, path, stepsCount);
        if (currLength == EOF)
            // Illegal move. Skip.
            continue;
        // printf("Currently at %d, Length between %d and %d: %d\n", source, i, dest, currLength);
        if (currLength < minLength)
        {
            // New minimum length. Use it.
            minLength = currLength;
            copy_arr(path, minPath, DIM);
            // printf("Located new minimum length: %d, standing at %d, travelling from %d to %d.\n", minLength, source, i, dest);
        }
    }

    // Return the current length.
    return minLength;
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
    // printf("\n");
}
