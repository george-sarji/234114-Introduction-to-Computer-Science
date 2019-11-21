/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
// The provided max size of the matrix in the question is 25.
#define MAX_SIZE 25

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
int receive_matrices(int first_matrix[MAX_SIZE][MAX_SIZE], int second_matrix[MAX_SIZE][MAX_SIZE], int matrix_size);
int receive_matrix(int size, int matrix[MAX_SIZE][MAX_SIZE]);
void mutiply_matrices(int first_matrix[MAX_SIZE][MAX_SIZE], int second_matrix[MAX_SIZE][MAX_SIZE], int size);
void add_matrices(int first_matrix[MAX_SIZE][MAX_SIZE], int second_matrix[MAX_SIZE][MAX_SIZE], int size);
void multiply_row_column(int first_matrix[MAX_SIZE][MAX_SIZE], int second_matrix[MAX_SIZE][MAX_SIZE], int size, int row, int column);
int handle_operations(int first_matrix[MAX_SIZE][MAX_SIZE], int second_matrix[MAX_SIZE][MAX_SIZE], int matrix_size);

int main()
{
	// This function will handle the main calls required by the code to properly work.
	// The first thing the function does is receive the size of the matrices. If the input is invalid,
	// an error is printed to the console and the program will exit.
	print_enter_matrix_size();
	int matrix_size = 0, first_matrix[MAX_SIZE][MAX_SIZE], second_matrix[MAX_SIZE][MAX_SIZE];
	if (!scanf("%d", &matrix_size))
	{
		print_invalid_input();
		return 0;
	}
	// The conditional here will call the receive matrices function, which receives the two required matrices.
	// If the function returns EOF, an invalid input message is shown and the program exits.
	// For further clarification, review the receive matrices function.
	if (receive_matrices(first_matrix, second_matrix, matrix_size) == EOF)
	{
		print_invalid_input();
		return 0;
	}
	// This conditional calls the function responsible for handling the operator that is input by the user.
	// In the case that the user inputs an incorrect symbol, an invalid input message is shown and the program exits.
	// For further clarification, review the handle operations function.
	if (handle_operations(first_matrix, second_matrix, matrix_size) == EOF)
	{
		print_invalid_input();
		return 0;
	}
	return 0;
}

void print_enter_matrix_size()
{
	printf("Please enter the matrix size:\n");
}

void print_enter_first_matrix()
{
	printf("Please enter the first matrix:\n");
}

void print_enter_second_matrix()
{
	printf("Please enter the second matrix:\n");
}

void print_invalid_input()
{
	printf("Invalid input.");
}

void print_enter_required_operation()
{
	printf("Please enter the required operation:\n");
}

void print_number(int number)
{
	printf("%d ", number);
}

void print_enter()
{
	printf("\n");
}

// This function is in charge of receiving the two matrices that the user provides.
// As seen, the two matrices are provided within the arguements of the function, as you can not return arrays from functions.
int receive_matrices(int first_matrix[MAX_SIZE][MAX_SIZE], int second_matrix[MAX_SIZE][MAX_SIZE], int matrix_size)
{
	// The function requests the user to input the first matrix.
	print_enter_first_matrix();
	// The generic function receive_matrix performs the logic required to receive the matrix per the requirements of the question.
	// Review the receive matrix function for further clarification.
	// If the receive matrix function returns EOF, this whole function will return EOF to print an invalid input message.
	if (receive_matrix(matrix_size, first_matrix) == EOF)
	{
		return EOF;
	}
	// Same as earlier, but the section here receives the second matrix.
	print_enter_second_matrix();
	if (receive_matrix(matrix_size, second_matrix) == EOF)
	{
		return EOF;
	}
	return 1;
}

// This function is in charge of recording the input of the user and constructing the matrix properly according to the provided size.
// The function receives the requested size of the matrix, along with the matrix that will be edited to host the input.
int receive_matrix(int size, int matrix[MAX_SIZE][MAX_SIZE])
{
	// The function goes from left to right, top to bottom in order for the input to be added into the matrix.
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			// Receive the number and assign into the matrix.
			if (!scanf("%d", &matrix[i][j]))
			{
				// The input was not a valid number. Function will return EOF to trigger an invalid input message.
				return EOF;
			}
		}
	}
	return 0;
}

// This function, as mentioned in the name of it, is in charge of multiplying two matrices.
// The function receives two matrices in the arguements, alongside the size of the matrices.
void mutiply_matrices(int first_matrix[MAX_SIZE][MAX_SIZE], int second_matrix[MAX_SIZE][MAX_SIZE], int size)
{
	// The function goes from left to right, top to bottom in order to multiple the matrices.
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			// We arrived at a(i, j). We need to perform the multiplication between the two matrices.
			multiply_row_column(first_matrix, second_matrix, size, i, j);
		}
		// Go down a new line since we finished the row.
		print_enter();
	}
}

// This function handles the individual multiplication of a specific row and column from each matrix.
void multiply_row_column(int first_matrix[MAX_SIZE][MAX_SIZE], int second_matrix[MAX_SIZE][MAX_SIZE], int size, int row, int column)
{
	// We define a sum that is used to add up the resultant of the multiplications.
	int sum = 0;
	// This for loop will iterate through the matrix. (e.g: a11*b11, a21 * b12, etc.)
	for (int element = 0; element < size; element++)
	{
		sum += first_matrix[row][element] * second_matrix[element][column];
	}
	// We have finished the multiplication, print the sum.
	print_number(sum);
}

// This function is in charge of adding up two matrices to each other.
void add_matrices(int first_matrix[MAX_SIZE][MAX_SIZE], int second_matrix[MAX_SIZE][MAX_SIZE], int size)
{
	// Left to right, top to bottom sequence.
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			// Print the resultant of the addition.
			print_number(first_matrix[i][j] + second_matrix[i][j]);
		}
		// Go down a new line as the row is complete
		print_enter();
	}
}

// This function is in charge of handling the operation input by the user.
// The function receives two matrices, alongside their size in the arguements.
int handle_operations(int first_matrix[MAX_SIZE][MAX_SIZE], int second_matrix[MAX_SIZE][MAX_SIZE], int matrix_size)
{
	print_enter_required_operation();
	char operation;
	// Receive the required operation and check whether it is legal or not.
	if (scanf(" %c", &operation) && (operation == '+' || operation == '*'))
	{
		// perform the required operation
		if (operation == '*')
		{
			mutiply_matrices(first_matrix, second_matrix, matrix_size);
		}
		else
		{
			add_matrices(first_matrix, second_matrix, matrix_size);
		}
	}
	// The input was either 1) not castable to a char or 2) not + or *, thus return EOF to trigger an invalid input message.
	else
	{
		return EOF;
	}

	return 1;
}