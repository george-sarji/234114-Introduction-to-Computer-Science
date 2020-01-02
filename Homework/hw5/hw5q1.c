#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void PrintWellcomeMessage()
{
    printf("Please enter a number:\n");
}

void PrintIsPalindrome()
{
    printf("It's a palindrome!");
}
void PrintIsNotPalindrome()
{
    printf("It's not a palindrome!");
}

bool CheckPalindrome(int palindrome, int originalNum, int sum);
int DigitCount(int number);

int main()
{
    PrintWellcomeMessage();
    int number = 0;
    scanf("%d", &number);
    if (CheckPalindrome(number, number, 0))
    {
        PrintIsPalindrome();
    }
    else
    {
        PrintIsNotPalindrome();
    }
    return 1;
}

int DigitCount(int number)
{
    if (number % 10 == 0)
        return 0;
    return 1 + DigitCount(number / 10);
}

bool CheckPalindrome(int palindrome, int originalNum, int sum)
{
    if (palindrome != 0)
    {
        sum = sum * 10 + palindrome % 10;
        return CheckPalindrome(palindrome /= 10, originalNum, sum);
    }
    else if (sum == originalNum)
        return true;
    return false;
}
