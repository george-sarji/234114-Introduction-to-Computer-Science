/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE 52
#define WORDS_ARRAY_SIZE 100
#define MAX_STR_LEN 50
#define MIN_UNDERLETTER 'a'
#define MAX_UNDERLETTER 'z'
#define MIN_CAPITAL 'A'
#define MAX_CAPITAL 'Z'
#define END_OF_STRING '\0'

char encrypt_char(unsigned char key[KEY_SIZE], char ch);
int read_words(char *words[], int size, int max_str_len);
void encrypt_words(char *words[], int num_words, unsigned char key[KEY_SIZE]);
void release_memory(char *words[], int num_words);
int get_keycode(char ch);

void print_words(char *words[], int num_words)
{
    int i;
    for (i = 0; i < num_words; i++)
    {
        printf("%s\n", words[i]);
    }
}

int main()
{
    unsigned char key[KEY_SIZE] = {

        '>', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '~', 'S', 'D',
        'F', 'G', '*', 'J', 'K', 'L', 'Z', 'X', 'C', 'V', 'B', '+', 'M',
        'm', 'b', 'n', 'v', 'z', 'c', '@', 'q', 'r', 'u', 'i', 'e', 'r',
        't', 'o', 'p', 'w', '$', 'j', 'g', 'd', '%', 's', 'f', 'h', 'k'};
    int num_words = 0, i;
    char *words[WORDS_ARRAY_SIZE];

    for (i = 0; i < WORDS_ARRAY_SIZE; i++)
    {
        words[i] = NULL;
    }

    num_words = read_words(words, WORDS_ARRAY_SIZE, MAX_STR_LEN);
    if (num_words == -1)
    {
        printf("Failed to read words.\n");
        return 0;
    }
    encrypt_words(words, num_words, key);
    print_words(words, num_words);
    release_memory(words, num_words);
    return 0;
}

int get_keycode(char ch)
{
    if (ch >= MIN_UNDERLETTER && ch <= MAX_UNDERLETTER)
    {
        return ch - MIN_UNDERLETTER;
    }
    else
    {
        return ch - MIN_CAPITAL;
    }
}

char encrypt_char(unsigned char key[KEY_SIZE], char ch)
{
    return key[get_keycode(ch)];
}


// TODO: Unused parameter: max_str_len
int read_words(char *words[], int size, int max_str_len)
{
    int word_counter = 0;
    char *currentString = "";
    while (word_counter < size && scanf("%s", currentString) && *currentString != EOF)
    {
        // Create the dynamic allocation according to the size of the string
        char *dynamicAllocation = (char *)malloc(sizeof(*currentString));
        *dynamicAllocation = *currentString;
        // TODO: Pointer issue resolve
        (words[word_counter]) = dynamicAllocation;
        word_counter++;
    }

    return word_counter;
}
void release_memory(char *words[], int num_words)
{
    for (int i = 0; i < num_words; i++)
    {
        free(words[i]);
    }
}