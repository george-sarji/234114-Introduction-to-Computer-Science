/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>



/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/



/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
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

int main()
{
	return 0;
}

void print_warriors_details(){
	printf("Enter warriors id and demand at the end:\n\n");
}

void print_army_size(int size){
	printf("The army size is: %d\n", size);
}

void print_biggest_platoon_and_size(int index, int size){
	printf("The biggest platoon index is: %d and its size is: %d\n", index, size);
}

void print_active_platoons_and_avg(int size, double avg){
	printf("There are %d active platoons \n\nThe avg size of a platoon is: %.2f\n", size, avg);
}

void print_show_army(){
	printf("Show army!\n\n");
}

void print_number(int num){
	printf("%d", num);
}

void print_enter(){
	printf("\n");
}

void print_star(){
	printf("*");
}

void print_space(){
	printf(" ");
}