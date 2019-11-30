/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
#define DRAGON_A_MODULO 5
#define DRAGON_A_MIN_LENGTH 4
#define DRAGON_C_MAX_LENGTH 6
#define LETTER_S 's'
#define END_OF_INPUT '!'


/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
  The program will receive the name of an enemy and will dispatch a specific
  dragon according to the given input. There are 4 criterias that are applicable.
  1) Sum of ASCII digits of name
  2) ASCII values display a monotone array
  3) Name length
  4) Name contains 's'

  There is a priority system for the dispatched dragons.
  The dragons are sorted from first to last: C, B, A.
  Only ONE dragon should get dispatched.

  If none of the required criterias are met, no dragon will be dispatched.

  Dragon A's criteria:
	1) Sum of ASCII digits % 5 != 0 OR name length > 4

  Dragon B's criteria:
	1) ASCII digits display a monotone array that is always rising

  Dragon C's criteria:
	1) Name length < 6 AND name does not contain 's'

 -------------------------------------------------------------------------*/

int print_enter_enemy_name();
int print_dragonA_sent();
int print_dragonB_sent();
int print_dragonC_sent();
int print_no_dragon_sent();
int sendDragonC();
int sendDragonB();
int sendDragonA();
int handleDragons();
int process_digit_total();
int receive_enemy_name();

int main()
{
	print_enter_enemy_name();
	receive_enemy_name();
	return 0;
}

int receive_enemy_name()
{
	char enemyName;
	int ascii_total = 0, previousChar = -1, length = 0, isMonotone = 1, contains_s = 0;
	while (scanf(" %c", &enemyName) != EOF && enemyName != END_OF_INPUT)
	{
		// Check if the ascii values are a monotone array.
		isMonotone = isMonotone && previousChar <= enemyName;
		// Add up to the length counter
		length++;
		// Check whether the name so far has contained an S
		contains_s = contains_s || enemyName == LETTER_S;
		// Add up the ASCII total of the name
		ascii_total += enemyName;
		// Update the previous char to the current, preparing for the new scan.
		previousChar = enemyName;
	}
	return handleDragons(length, contains_s, ascii_total, isMonotone);
}

// This function will check whether dragon A should be sent and accordingly send it.
int sendDragonA(int ascii_sum, int length)
{
	return (ascii_sum % DRAGON_A_MODULO != 0 || length > DRAGON_A_MIN_LENGTH) && print_dragonA_sent();
}

// This function will check whether dragon A should be sent and accordingly send it.
int sendDragonB(int is_monotone)
{
	return is_monotone && print_dragonB_sent() != EOF;
}

// This function will check whether dragon A should be sent and accordingly send it.
int sendDragonC(int length, int contains_s)
{
	return length < DRAGON_C_MAX_LENGTH && !contains_s && print_dragonC_sent();
}

// This function will handle the sending of the dragons.
int handleDragons(int length, int contains_s, int ascii_sum, int is_monotone)
{
	// According to the lazy evaluation process, this function will only send one dragon or none at all.
	return sendDragonC(length, contains_s) || sendDragonB(is_monotone) || sendDragonA(ascii_sum, length) || print_no_dragon_sent();
}

int print_enter_enemy_name()
{
	return printf("Please enter enemy name:\n");
}

int print_dragonA_sent()
{
	return printf("\nKhalisi sent dragonA into the battle!!!\n");
}

int print_dragonB_sent()
{
	return printf("\nKhalisi sent dragonB into the battle!!!\n");
}

int print_dragonC_sent()
{
	return printf("\nKhalisi sent dragonC into the battle!!!\n");
}

int print_no_dragon_sent()
{
	return printf("\nNO Dragon has been sent into the battle!!!\n");
}