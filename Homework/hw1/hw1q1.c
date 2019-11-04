#include <stdio.h>

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

int CheckDigit()
{
    int result, providedNum = 0;
    printf("\nCalculating CheckDigit, please enter 8 digits:\n");
    for (int i = 0; i < 8; i++)
    {
        int currentNum;
        result = scanf("%1d", &currentNum);
        if (result != 1)
        {
            return -1;
        }
        providedNum = providedNum * 10 + currentNum;
    }
    printf("\nCheckDigit = %i", ValidatorFunc(providedNum));
    return 0;
}

int ValidateID()
{
    int result, providedNum = 0;
    printf("\nValidating ID, please enter 9 digits ID:\n");
    for (int i = 0; i < 9; i++)
    {
        int currentNum;
        result = scanf("%1d", &currentNum);
        if (result != 1)
        {
            return -1;
        }
        providedNum = providedNum * 10 + currentNum;
    }
    int currentDigit = providedNum % 10;
    int calculatedDigit = ValidatorFunc(providedNum / 10);
    printf("\nYou have entered CheckDigit = %i\n", currentDigit);
    printf("Calculated CheckDigit = %i\n\n", calculatedDigit);
    printf(currentDigit == calculatedDigit ? "Legal ID :)" : "Illegal ID :(");
    return 0;
}

int main()
{
    printf("Please enter the letter C for calculating CheckDigit and the letter V for validating an ID by its CheckDigit: \n");
    char choice;
    scanf(" %c", &choice);
    switch (choice)
    {
    case ('V'):
    {
        if (ValidateID() == -1)
        {
            printf("\nERROR");
        }
        break;
    }
    case ('C'):
    {
        if (CheckDigit() == -1)
        {
            printf("\nERROR");
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
