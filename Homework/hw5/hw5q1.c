#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

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
bool CheckPalindrome2(int palindrome, int digitCount);

int main()
{
    PrintWellcomeMessage();
    int number = 0;
    scanf("%d", &number);

    // if (CheckPalindrome(number, number, 0))
    // {
    //     PrintIsPalindrome();
    // }
    // else
    // {
    //     PrintIsNotPalindrome();
    // }
    if (CheckPalindrome2(number, DigitCount(number)))
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
    if (number == 0)
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

bool CheckPalindrome2(int palindrome, int digitNumber)
{
    if (digitNumber <= 0)
        return true;
    int currentDigitPow = pow(10, digitNumber - 1);
    int firstNum = palindrome % 10, secondNum = palindrome / currentDigitPow;
    // printf("Received num: %d, comparing %d = %d\n", palindrome, firstNum, secondNum);
    return firstNum == secondNum && CheckPalindrome2((palindrome % currentDigitPow / 10), digitNumber - 2);
}