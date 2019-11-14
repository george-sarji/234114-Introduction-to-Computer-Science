#include <stdio.h>

int scanNumber(int num)
{
    // This function will perform the scanning and validation of the input.
    // Return value will be the input number if its valid. If invalid, it will return -1.
    int totalNum = 0, currentNum = 0, scanResult = 0;
    for (int i = 0; i < num; i++)
    {
        scanResult = scanf(" %1d", &currentNum);
        if (scanResult < 1)
        {
            printf("\nERROR");
            return -1;
        }
        totalNum = totalNum * 10 + currentNum;
    }
    return totalNum;
}

int calculateDigit(int num)
{
    // This function will perform the logic to provide the check digit.
    // The multiplication order is: 2, 1, 2, 1, 2, 1, 2, 1
    int totalNumber = 0, counter = 0;
    while (num > 0)
    {
        counter++;
        int currentDigit = num % 10;
        if (counter % 2 == 1)
        {
            currentDigit *= 2;
            totalNumber += currentDigit % 10 + currentDigit / 10;
        }
        else
        {
            totalNumber += currentDigit;
        }
        num /= 10;
    }
    // The return value will be the accordingly calculated digit.
    return (10 - totalNumber % 10) % 10;
}

int main()
{

    printf("Please enter the letter C for calculating CheckDigit and the letter V for validating an ID by its CheckDigit:\n");
    char choice;
    int result = 0, inputNumber = 0, calculatedCheckDigit = 0;
    result = scanf(" %c", &choice);
    if (result < 1)
    {
        return -1;
    }
    printf("\n");
    if (choice == 'C')
    {
        // Perform check digit
        printf("Calculating CheckDigit, please enter 8 digits:\n");
        inputNumber = scanNumber(8);
        if (inputNumber == -1)
        {
            return -1;
        }
        calculatedCheckDigit = calculateDigit(inputNumber);
        printf("\nCheckDigit = %d", calculatedCheckDigit);
    }
    else if (choice == 'V')
    {
        // Perform validation
        printf("Validating ID, please enter 9 digits ID:\n");
        inputNumber = scanNumber(9);
        if (inputNumber == -1)
        {
            return -1;
        }
        calculatedCheckDigit = calculateDigit(inputNumber / 10);
        printf("\nYou have entered CheckDigit = %d\nCalculated CheckDigit = %d\n\n", inputNumber % 10, calculatedCheckDigit);
        if (calculatedCheckDigit == inputNumber % 10)
        {
            printf("Legal ID :)");
        }
        else
        {
            printf("Illegal ID :(");
        }
    }
    // If neither cases are met, no instructions were given. Exit.
    return 0;
}