/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/*=========================================================================
  Constants and definitions:
==========================================================================*/

/* put your #defines and typedefs here*/
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
void receive_matrices();
int receive_matrix(int size, int matrix[MAX_SIZE][MAX_SIZE]);
void mutiply_matrices(int first_matrix[MAX_SIZE][MAX_SIZE], int second_matrix[MAX_SIZE][MAX_SIZE], int size);
void add_matrices(int first_matrix[MAX_SIZE][MAX_SIZE], int second_matrix[MAX_SIZE][MAX_SIZE], int size);
void multiply_row_column(int first_matrix[MAX_SIZE][MAX_SIZE], int second_matrix[MAX_SIZE][MAX_SIZE], int size, int row, int column);

int main()
{
	receive_matrices();
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

void receive_matrices()
{
	print_enter_matrix_size();
	int matrix_size = 0;
	scanf("%d", &matrix_size);
	print_enter_first_matrix();
	int first_matrix[MAX_SIZE][MAX_SIZE], second_matrix[MAX_SIZE][MAX_SIZE];
	if (receive_matrix(matrix_size, first_matrix) == EOF)
	{
		return;
	}
	print_enter_second_matrix();
	if (receive_matrix(matrix_size, second_matrix) == EOF)
	{
		return;
	}
	print_enter_required_operation();
	char operation;
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
	else
	{
		print_invalid_input();
	}
}

int receive_matrix(int size, int matrix[MAX_SIZE][MAX_SIZE])
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			// Receive the number and assign into the matrix.
			if (!scanf("%d", &matrix[i][j]))
			{
				print_invalid_input();
				return -1;
			}
		}
	}
	return 0;
}

void mutiply_matrices(int first_matrix[MAX_SIZE][MAX_SIZE], int second_matrix[MAX_SIZE][MAX_SIZE], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			// We arrived at a(i, j). We need to perform the multiplication between the two matrices.
			multiply_row_column(first_matrix, second_matrix, size, i, j);
		}
		print_enter();
	}
}

void multiply_row_column(int first_matrix[MAX_SIZE][MAX_SIZE], int second_matrix[MAX_SIZE][MAX_SIZE], int size, int row, int column)
{
	int sum = 0;
	for (int element = 0; element < size; element++)
	{
		sum += first_matrix[row][element] * second_matrix[element][column];
	}
	print_number(sum);
}

void add_matrices(int first_matrix[MAX_SIZE][MAX_SIZE], int second_matrix[MAX_SIZE][MAX_SIZE], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			print_number(first_matrix[i][j] + second_matrix[i][j]);
		}
		print_enter();
	}
}