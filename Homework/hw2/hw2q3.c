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

void print_enter_matrix_size();
void print_enter_first_matrix();
void print_enter_second_matrix();
void print_invalid_input();
void print_enter_required_operation();
void print_number(int number);
void print_enter();

int main()
{
    return 0;
}

void print_enter_matrix_size(){
	printf("Please enter the matrix size:\n");
}

void print_enter_first_matrix(){
	printf("Please enter the first matrix:\n");
}

void print_enter_second_matrix(){
	printf("Please enter the second matrix:\n");
}

void print_invalid_input(){
	printf("Invalid input.");
}

void print_enter_required_operation(){
	printf("Please enter the required operation:\n");
}

void print_number(int number){
	printf("%d ", number);
}

void print_enter(){
	printf("\n");
}