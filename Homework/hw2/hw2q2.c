/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
// The max number of platoons.
#define PLATOONS 10
// The number for each operation/demand
#define SUM_OPT 1
#define BIGGEST_PLAT 2
#define ACTIVE_NUM 3
#define PRINT_PLAT 4

/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)

  This program will receive serial numbers of soldiers that consist of 3 digits.
  Each soldier will be sent to a specific platoon according to their personally assigned number.
  The assignment of each soldier is the first digit of the sum of their number.
  e.g: 940 gets assigned to platoon 3 (9+4+0 = 13), 230 gets assigned to platoon 5.

  After all the soldier serial numbers are keyed in by the user, there will be a single
  digit that highlights a specific demand from the program. The demands are as follows:
  1) Size of the army. (Sum of all the soldiers)
  2) Biggest platoon's number and sum of soldiers in it (bigger index wins)
  3) Number of platoons with at least one soldier in it, average size of platoon to the second decimal
  4) Print platoons with stars. First row is number of platoon, second row stars for first soldier and so forth.
 -------------------------------------------------------------------------*/

void print_warriors_details();
void print_army_size(int size);
void print_biggest_platoon_and_size(int index, int size);
void print_active_platoons_and_avg(int size, double avg);
void print_show_army();
void print_number(int num);
void print_enter();
void print_star();
void print_space();
void handle_option_2(int platoon[PLATOONS]);
void handle_option_3(int platoon[PLATOONS]);
void print_army(int platoons[PLATOONS], int counter);
void handle_army_details(int counter, int platoons[PLATOONS], int demand);
void receive_numbers();
void handle_demand(int counter, int platoons[PLATOONS], int demand);
void print_army_header();
int print_army_row(int platoons[PLATOONS]);

int main()
{
	print_warriors_details();
	receive_numbers();
	return 0;
}

void print_warriors_details()
{
	printf("Enter warriors id and demand at the end:\n\n");
}

void print_army_size(int size)
{
	printf("The army size is: %d\n", size);
}

void print_biggest_platoon_and_size(int index, int size)
{
	printf("The biggest platoon index is: %d and its size is: %d\n", index, size);
}

void print_active_platoons_and_avg(int size, double avg)
{
	printf("There are %d active platoons \n\nThe avg size of a platoon is: %.2f\n", size, avg);
}

void print_show_army()
{
	printf("Show army!\n\n");
}

void print_number(int num)
{
	printf("%d", num);
}

void print_enter()
{
	printf("\n");
}

void print_star()
{
	printf("*");
}

void print_space()
{
	printf(" ");
}

void receive_numbers()
{
	// This function will receive the numbers of the soldiers and the demand at the end.
	// Initialize the platoons array as a counter array.
	int currentNumber = 0, currentAssignment = 0, counter = 0, platoons[PLATOONS] = {0};
	// Scan for 3 digit numbers and place them in currentNumber. Check whether the number is actually a 1 digit number (highlights a demand).
	// If the number is not a 1 digit number, continue on with processing the warrior IDs.
	while (scanf("%3d", &currentNumber) && currentNumber > 10)
	{
		// Add into the main army size counter.
		counter++;
		// Calculate assignment.
		currentAssignment = ((currentNumber / 100) % 10 + (currentNumber / 10) % 10 + currentNumber % 10) % 10;
		// Add 1 into the assigned platoon counter.
		platoons[currentAssignment]++;
	}
	// The current number at this point will be the demand of the commander.
	handle_demand(counter, platoons, currentNumber);
}

void handle_option_2(int platoons[PLATOONS])
{
	// This function will handle the biggest platoons and its sum.
	int biggest_platoon = 0;
	// By default wwe have platoon that has the biggest size. Thus, we start at index 0.
	for (int i = 0; i < PLATOONS; i++)
	{
		// As we want the biggest index of the biggest platoon, if the biggest platoon's size is the same as the current, switch the index.
		if (platoons[i] >= platoons[biggest_platoon])
		{
			biggest_platoon = i;
		}
	}
	// Call the provided function.
	print_biggest_platoon_and_size(biggest_platoon, platoons[biggest_platoon]);
}

void handle_option_3(int platoons[PLATOONS])
{
	// Define a counter and a sum in order to provide an average.
	double counter = 0, sum = 0;
	for (int i = 0; i < PLATOONS; i++)
	{
		if (platoons[i] > 0)
		{
			counter++;
			sum += platoons[i];
		}
	}
	// Call the provided function.
	print_active_platoons_and_avg(counter, sum / counter);
}

void print_army(int platoons[PLATOONS], int counter)
{
	// Print the show army text (provided function)
	print_show_army();
	// Print the army header (0123456789)
	print_army_header();
	// While there are warriors left over and not printed, print a row of the platoons.
	while (counter > 0)
	{
		counter -= print_army_row(platoons);
	}
}

void handle_demand(int counter, int platoons[PLATOONS], int demand)
{
	// Handle the demand of the commander.
	switch (demand)
	{
	case SUM_OPT:
	{
		// Print the size of the army
		print_army_size(counter);
		break;
	}
	case BIGGEST_PLAT:
	{
		// Print the biggest platoon index and size
		handle_option_2(platoons);
		break;
	}

	case ACTIVE_NUM:
	{
		// Print the number of active platoons and their average size
		handle_option_3(platoons);
		break;
	}

	case PRINT_PLAT:
	{
		// Print the whole army divided into platoons.
		print_army(platoons, counter);
		break;
	}
	}
}

// This function prints the header of the army printing section (0123456789).
void print_army_header()
{
	for (int i = 0; i < PLATOONS; i++)
	{
		print_number(i);
	}
	print_enter();
}

// This function is in charge of printing the individual rows of the platoons (stars) depicting the number of warrios in the platoon.
// The function will return the amount of times a star was printed in the current row iteration (used for counter calculation)
int print_army_row(int platoons[PLATOONS])
{
	int print_count = 0;
	for (int i = 0; i < PLATOONS; i++)
	{
		if (platoons[i] > 0)
		{
			platoons[i]--;
			print_count++;
			print_star();
		}
		else
		{
			print_space();
		}
	}
	print_enter();
	return print_count;
}