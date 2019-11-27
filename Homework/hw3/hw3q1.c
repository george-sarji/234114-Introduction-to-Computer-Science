/*-------------------------------------------------------------------------
    Include files:
-------------------------------------------------------------------------*/
#include <stdio.h>

/*-------------------------------------------------------------------------
    Constants and definitions:
-------------------------------------------------------------------------*/
#define N 11

/*-------------------------------------------------------------------------
    Function declaration
-------------------------------------------------------------------------*/
void print_welcome();
void print_enter_board_size();
void print_board(char board[N][N], int n);
void print_player_turn(int player_index);
void print_error();
void print_winner(int player_index);
void print_tie();
void start_game();
void initialize_board(char board[N][N], int size);
void game_ticker(char board[N][N], int size);
int validate_board(char board[N][N], int size);
int main();

/*-------------------------------------------------------------------------
    Implementation
-------------------------------------------------------------------------*/

int main()
{
    start_game();
}

//print welcome message
//1 lines
void print_welcome()
{
    printf("*** Welcome to AVOIDANCE TIC-TAC-TOE game ***\n\n");
}

//print message to enter board size
//1 lines
void print_enter_board_size()
{
    printf("Please enter board size (1 to %d):\n", N);
}

//print the board
//7 lines
void print_board(char board[N][N], int n)
{
    printf("\nCurrent board:\n");
    for (int i = 0; i < n; i++)
    {
        printf("|");
        for (int j = 0; j < n; j++)
        {
            printf("%c|", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//print a request for player with index "player_index" to move
//1 lines
void print_player_turn(int player_index)
{
    printf("\nPlayer ** %d **, enter next move:\n", player_index);
}

//print error message
//1 lines
void print_error()
{
    printf("Illegal move!!!, please try again:\n");
}

//print the winner
//1 lines
void print_winner(int player_index)
{
    printf("Player %d Wins! Hooray!\n", player_index);
}

//print message to announce there is a tie (no one wins)
//1 lines
void print_tie()
{
    printf("It's a tie!\n");
}

// This function will start the game sequence by asking for the size of the matrix and handles the initialization in general
void start_game()
{
    print_welcome();
    print_enter_board_size();
    int size = 0;
    scanf("%d", &size);
    char board[N][N];
    initialize_board(board, size);
    print_board(board, size);
    game_ticker(board, size);
}
void initialize_board(char board[N][N], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            board[i][j] = '_';
        }
    }
}

int validate_board(char board[N][N], int size)
{
    int col_counter = 0, row_counter = 0;
    for (int i = 0; i < size; i++)
    {
        col_counter = row_counter = 0;
        for (int j = 1; j < size; j++)
        {
            if (board[i][j - 1] == board[i][j] && board[i][j] != '_')
            {
                row_counter++;
            }
            if (board[j - 1][i] == board[j][i] && board[j][i] != '_')
            {
                col_counter++;
            }
        }
        if (row_counter == size - 1 || col_counter == size - 1)
        {
            return 0;
        }
    }

    col_counter = row_counter = 0;
    // Check sideways.
    for (int i = 1; i < size; i++)
    {
        if (board[i][i] == board[i - 1][i - 1] && board[i][i] != '_')
        {
            row_counter++;
        }
        if (board[size - i][i - 1] == board[size - i - 1][i] && board[size - i][i - 1] != '_')
        {
            col_counter++;
        }
    }
    if (row_counter == size - 1 || col_counter == size - 1)
    {
        return 0;
    }
    return 1;
}

void game_ticker(char board[N][N], int size)
{
    int turns = 0, player_index = 1, current_sign = 'X', valid_board = 1, current_col = 0, current_row = 0;
    print_player_turn(1);
    while (valid_board)
    {
        player_index = (turns % 2 == 0) ? 2 : 1;
        if (!scanf("%d", &current_row) || !scanf("%d", &current_col) || board[current_row - 1][current_col - 1] != '_')
        {
            print_error();
            continue;
        }
        // If not an error, this code processes.
        // Entered
        board[current_row - 1][current_col - 1] = current_sign;
        print_board(board, size);
        if (!validate_board(board, size))
        {
            print_winner(player_index);
            return;
        }
        current_sign = current_sign == 'X' ? 'O' : 'X';
        if (turns + 1 == size * size)
        {
            // Tie. End game.
            print_tie();
            return;
        }
        print_player_turn(player_index);
        turns++;
    }
}