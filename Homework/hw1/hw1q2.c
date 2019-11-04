#include <stdio.h>

int decodeWord(int reversedNumber)
{
    int wordCounter = 0;
    int currentNum = 0, currentDigit = 10;
    while (reversedNumber != 0)
    {
        // Have we reached 3 digits already?
        if (currentDigit == 10000)
        {
            // Delete the first digit and repeat the process.
            currentNum = 0;
            reversedNumber /= 10;
            currentDigit = 1;
        }
        // Take next digit.
        currentNum = reversedNumber % currentDigit;

        if ((currentNum >= 'a' && currentNum <= 'z'))
        {
            // Successful decode.
            if (wordCounter == 0)
            {
                // First decode.
                printf("The decoded word is: ");
            }
            if (currentNum % 2 == 0)
            {
                // Make capital letter.
                currentNum = currentNum - 'a' + 'A';
            }
            printf("%c", currentNum);

            // Reset parameters.
            currentNum = 0;
            reversedNumber /= currentDigit;
            wordCounter++;
            currentDigit = 10;
        }
        else
        {
            currentDigit *= 10;
        }
    }
    // Go down new line.
    printf("\n");
    if (wordCounter == 0)
    {
        printf("There is nothing there :(");
    }
    else
    {
        printf("Done and even had time for coffee :)");
    }
    return wordCounter;
}

int ReverseNumber()
{
    int providedNum, reversedNum = 0;
    int temporaryNum;
    printf("Enter an encoded word and I'll do my best: \n");
    scanf("%d", &providedNum);
    // Reverse the number.
    while (providedNum != 0)
    {
        temporaryNum = providedNum % 10;
        reversedNum = reversedNum * 10 + temporaryNum;
        providedNum /= 10;
    }
    decodeWord(reversedNum);
    return 0;
}

int main()
{
    ReverseNumber();
    return 0;
}
