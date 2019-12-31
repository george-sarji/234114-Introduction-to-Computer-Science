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
        return ch - MIN_UNDERLETTER + (KEY_SIZE / 2);
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

int read_words(char *words[], int size, int max_str_len)
{
    int word_counter = 0;
    char *currentString = (char *)malloc(max_str_len * sizeof(char));
    if (currentString == NULL)
        return EOF;
    char newLine;
    while (word_counter < size && scanf(" %s%c", currentString, &newLine) != EOF)
    {
        // Perform dynamic allocation.
        char *dynamicAlloc = (char *)malloc((int)(strlen(currentString) + 1) * sizeof(char));
        strcpy(dynamicAlloc, currentString);
        free(currentString);
        words[word_counter++] = dynamicAlloc;
        if (newLine == '\n')
        {
            break;
        }
        currentString = (char *)malloc(max_str_len * sizeof(char));
        if (currentString == NULL)
        {
            return EOF;
        }
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

void encrypt_words(char *words[], int num_words, unsigned char key[KEY_SIZE])
{
    for (int i = 0; i < num_words; i++)
    {
        char *currentWord = words[i];
        for (unsigned int letter = 0; letter < strlen(currentWord); letter++)
        {
            currentWord[letter] = encrypt_char(key, currentWord[letter]);
        }
    }
}
