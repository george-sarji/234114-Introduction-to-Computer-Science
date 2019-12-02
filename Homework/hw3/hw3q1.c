/*-------------------------------------------------------------------------
    Include files:
-------------------------------------------------------------------------*/
#include <stdio.h>

/*-------------------------------------------------------------------------
    Constants and definitions:
-------------------------------------------------------------------------*/
#define N 11
// TODO: Add definitions required by history system

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
int validate_rows(char board[N][N], int size);
int validate_cols(char board[N][N], int size);
int validate_diagonals(char board[N][N], int size);
int main();
int handle_game_tick(char board[N][N], int size, int player_index, int game_tick, int *valid_board);
// TODO: Add function to reverse the board by x game ticks

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

// This function will handle the validation of the board.
int validate_board(char board[N][N], int size)
{
    return validate_cols(board, size) && validate_rows(board, size) && validate_diagonals(board, size);
}

// This function receives the board and its size and validates the rows.
int validate_rows(char board[N][N], int size)
{
    int counter = 0;
    for (int i = 0; i < size; i++)
    {
        counter = 0;
        for (int j = 1; j < size; j++)
        {
            if (board[i][j - 1] == board[i][j] && board[i][j] != '_')
            {
                counter++;
            }
        }
        if (counter == size - 1)
        {
            return 0;
        }
    }
    return 1;
}

// This function receives the board and its size and validates the columns.
int validate_cols(char board[N][N], int size)
{
    int counter = 0;
    for (int i = 0; i < size; i++)
    {
        counter = 0;
        for (int j = 1; j < size; j++)
        {
            if (board[j - 1][i] == board[j][i] && board[j][i] != '_')
            {
                counter++;
            }
        }
        if (counter == size - 1)
        {
            return 0;
        }
    }
    return 1;
}

// This function receives the board and its size and validates the two diagonals.
int validate_diagonals(char board[N][N], int size)
{
    int alt_counter = 0, main_counter = 0;
    // Check sideways.
    for (int i = 1; i < size; i++)
    {
        if (board[i][i] == board[i - 1][i - 1] && board[i][i] != '_')
        {
            main_counter++;
        }
        if (board[size - i][i - 1] == board[size - i - 1][i] && board[size - i][i - 1] != '_')
        {
            alt_counter++;
        }
    }
    return !(main_counter == size - 1 || alt_counter == size - 1);
}

// This function receives the board and its size and runs the main game logic.
void game_ticker(char board[N][N], int size)
{
    int turns = 0, player_index = 1, current_sign = 'X', valid_board = 1, current_col = 0, current_row = 0;
    print_player_turn(1);
    while (valid_board)
    {
        player_index = (turns % 2 == 0) ? 2 : 1;
        turns = handle_game_tick(board, size, player_index, turns, &valid_board);
    }
}

// This function receives the board, its size, the current game tick and current player index.
// Function will handle the logic for every single game tick (turn)
int handle_game_tick(char board[N][N], int size, int player_index, int game_tick, int *valid_board)
{
    // Receive the required numbers:
    int current_col = 0, current_row = 0;
    if (!scanf("%d", &current_row) || !scanf("%d", &current_col) || (current_row > 0 && board[current_row - 1][current_col - 1] != '_'))
    {
        print_error();
        return game_tick;
    }
    else if (current_row < 0)
    {
        // Requested undo. Perform history switch.
        // TODO: Perform history logic here and utilize function to reverse the board by the received x ticks
    }
    else
    {
        // There was a successful entry.
        board[current_row - 1][current_col - 1] = game_tick % 2 == 0 ? 'X' : 'O';
        print_board(board, size);
        if (!validate_board(board, size))
        {
            *valid_board = 0;
            print_winner(player_index);
            return game_tick;
        }
        if (game_tick + 1 == size * size)
        {
            // Tie. End game.
            print_tie();
            return game_tick;
        }
        print_player_turn(player_index);
    }
    return game_tick + 1;
}