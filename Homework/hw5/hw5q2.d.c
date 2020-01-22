#include <stdio.h>
#include <stdlib.h>

#define DIM 4

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

int check_routes(int source, int dest, int path[DIM * DIM], int map[DIM][DIM], int current, int currentStep)
{
    if (current == dest)
    {
        // successful route
    }
    int paths[DIM][DIM * DIM] = {-1};
    for (int col = 0; col < DIM; col++)
    {
        if (col == current)
            continue;
        path[currentStep + 1] = col;
        if (check_routes(col, dest, path, map, col, currentStep + 1) + map[current, col] < map[source, dest])
        {
            // Valid path. Add it to paths array for minimization.
            *(paths[col]) = *(path);
        }
    }

    // Check for the most minimal route.

    return -1;
}

void calculate_best_route(int map[DIM][DIM], int source, int dest)
{
    int path[DIM * DIM] = {-1};
    int result = check_route(source, source, dest, map, 0, 0, path);
    if (result == -1)
    {
        printf("ERROR");
        exit(-1);
    }
    else
    {
        // Print the route.
        for (int i = 0; i < DIM * DIM; i++)
        {
            if (map[i] == -1)
                break;
            PrintNumber(map[i]);
            PrintSpace();
        }
    }
}

int main()
{
    PrintWelcomeMessage();
    int map[DIM][DIM] = {0}, source = 0, dest = 0;
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            scanf("%d", &map[i][j]);
        }
    }
    PrintSourceCityMessage();
    scanf("%d", &source);
    PrintDestinationCityMessage();
    scanf("%d", &dest);
    calculate_best_route(map, source, dest);
    return 0;
}

int check_route(int origin, int source, int dest, int map[DIM][DIM], int steps, int currentLength, int currentPath[DIM * DIM])
{
    if (currentLength > map[origin][dest])
        return -1;
    if (source == dest)
    {
        // Add to path
        return 0;
    }
    if (steps >= DIM * DIM)
        return -1;
    currentPath[steps] = source;
    int pathLengths[DIM] = {0};
    int paths[DIM][DIM * DIM];
    for (int i = 0; i < DIM; i++)
    {
        if (i == source)
            continue;
        int length = 0;
        *paths[i] = currentPath;
        length = check_route(origin, i, dest, map, steps + 1, currentLength + map[source][i], paths[i]);
        if (length == -1)
            continue;
        pathLengths[i] = length;
    }

    // Get the minimum length.
    int minIndex = getMinIndex(pathLengths, DIM, source);
    // We got the minimum length route. Add it to current path and return with length.
    currentPath[steps] = *paths[minIndex];

    // Get the length for the path.
    int length = 0;
    for (int i = 0; i < steps - 1; i++)
    {
        length += map[currentPath[i]][currentPath[i + 1]];
    }
    return length;
}

int getMinIndex(int arr[], int length, int except)
{
    int index = 0;
    for (int i = 0; i < length; i++)
    {
        if (i == except)
            continue;
        if (arr[i] < arr[index])
            index = i;
    }
    return index;
}