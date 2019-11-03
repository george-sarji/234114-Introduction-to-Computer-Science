#include <stdio.h>

int main()
{
    printf("Please enter the letter C for calculating CheckDigit and the letter V for validating an ID by its CheckDigit: \n");
    char choice;
    int providedNum;
    scanf(" %c", &choice);
    switch (choice)
    {
    case ('V'):
    {
        if (ValidateID() == -1)
        {
            printf("ERROR");
        }
        break;
    }
    case ('C'):
    {
        if (CheckDigit() == -1)
        {
            printf("ERROR");
        }
        break;
    }
    default:
    {
        printf("Please enter the appropriate letter.");
        break;
    }
    }
    return 0;
}

int CheckDigit()
{
    int result, providedNum;
    printf("Calculating CheckDigit, please enter 8 digits:\n");
    result = scanf("%8d", &providedNum);
    if (result != 1)
    {
        return -1;
    }
    printf("CheckDigit = %i", ValidatorFunc(providedNum));
    return 0;
}

int ValidateID()
{
    int result, providedNum;
    printf("Validating ID, please enter 9 digits ID:\n");
    result = scanf("%9d", &providedNum);
    if (result != -1)
    {
        return -1;
    }
    int currentDigit = providedNum % 10;
    int calculatedDigit = ValidatorFunc(providedNum / 10);
    printf("You have entered CheckDigit = %i\n", currentDigit);
    printf("Calculated CheckDigit = %i\n", calculatedDigit);
    printf(currentDigit == calculatedDigit ? "Legal ID :)" : "Illegal ID :(");
    return 0;
}

int ValidatorFunc(int idNum)
{
    int sumDigits = 0;
    for (int i = 0; i < 8; i++)
    {
        int currentDigit = idNum % 10 * (i % 2 == 0 ? 2 : 1);
        sumDigits += currentDigit % 10 + currentDigit / 10;
        idNum /= 10;
    }
    return 10 - sumDigits % 10;
}