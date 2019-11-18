#include <stdio.h>

unsigned long int reverseNumber(unsigned long int encodedNumber)
{
    unsigned long int reversedNumber = 0;
    while (encodedNumber > 0)
    {
        reversedNumber = reversedNumber * 10 + encodedNumber % 10;
        encodedNumber /= 10;
    }
    return reversedNumber;
}

char capitalizeCharacter(int keycode)
{
    // If even number, capitalize.
    if (keycode % 2 == 0)
    {
        if (keycode >= 'a' && keycode <= 'z')
        {
            return (char)(keycode - 'a' + 'A');
        }
    }
    else
    {
        if (keycode >= 'A' && keycode <= 'Z')
        {
            return (char)(keycode - 'A' + 'a');
        }
    }
    // If uneven number, small letter.

    return (char)keycode;
}

int decodeWord(unsigned long int reversedNumber)
{
    int counter = 0;
    while (reversedNumber > 0)
    {
        if (reversedNumber % 100 >= 'a' && reversedNumber % 100 <= 'z')
        {
            // Able to decode. Decode and print.
            if (counter == 0)
            {
                printf("The decoded word is: ");
            }
            printf("%c", capitalizeCharacter(reversedNumber % 100));
            reversedNumber /= 100;
            counter++;
        }
        else if (reversedNumber % 1000 >= 'a' && reversedNumber % 1000 <= 'z')
        {
            if (counter == 0)
            {
                printf("The decoded word is: ");
            }
            printf("%c", capitalizeCharacter(reversedNumber % 1000));
            reversedNumber /= 1000;
            counter++;
        }
        else
        {
            return counter;
        }
    }
    return counter;
}

int main()
{
    int result = 0;
    unsigned long int encodedNumber = 0;
    printf("Enter an encoded word and I'll do my best:\n");
    result = scanf(" %lu", &encodedNumber);
    if (result < 1)
    {
        return -1;
    }
    encodedNumber = reverseNumber(encodedNumber);
    if (decodeWord(encodedNumber) > 0)
    {
        printf("\nDone and even had time for coffee :)");
    }
    else
    {
        printf("\nThere is nothing there :(");
    }
    return 0;
}