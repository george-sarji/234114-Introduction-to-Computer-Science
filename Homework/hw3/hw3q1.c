/*-------------------------------------------------------------------------
    Include files:
-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>

/*-------------------------------------------------------------------------
    Constants and definitions:
-------------------------------------------------------------------------*/
#define N 11
#define MAX_TICKS 121
#define EMPTY_SPACE '_'
#define PLAYER_ONE 'X'
#define PLAYER_TWO 'O'

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
void initialize_game();
void initialize_game_board(char game_board[N][N], int board_size);
void game_ticker(char game_board[N][N], char game_history[MAX_TICKS][N][N], int board_size);
void add_history_entry(char game_board[N][N], char history_board[MAX_TICKS][N][N], int board_size, int current_tick);
int tick_handler(char game_board[N][N], char game_history[MAX_TICKS][N][N], int board_size, int current_tick, int *valid_board);
void reverse_board(char game_board[N][N], char game_history[MAX_TICKS][N][N], int board_size, int current_tick, int ticks);
int validate_column(char game_board[N][N], int board_size, int column);
int validate_row(char game_board[N][N], int board_size, int row);
int validate_primary_diagonal(char game_board[N][N], int board_size);
int validate_secondary_diagonal(char game_board[N][N], int board_size);
int validate_board(char game_board[N][N], int board_size, int column, int row);
int is_board_full(char game_board[N][N], int board_size);
int handle_reverse(char game_board[N][N], char history_board[MAX_TICKS][N][N], int board_size, int current_tick, int ticks);
int handle_entry(char game_board[N][N], char history_board[MAX_TICKS][N][N], int board_size, int row, int column, int current_tick, int *valid_board);
int main();

/*-------------------------------------------------------------------------
    Implementation
-------------------------------------------------------------------------*/

int main()
{
    initialize_game();
    return 0;
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

// This function will initialize the game with the required variables.
void initialize_game()
{
    char game_board[N][N], history_board[MAX_TICKS][N][N];
    int board_size = 0;
    print_welcome();
    print_enter_board_size();
    scanf("%d", &board_size);
    // We received the board size. Initialize the board.
    initialize_game_board(game_board, board_size);
    game_ticker(game_board, history_board, board_size);
}

// This function will initialize the game board with empty spaces
void initialize_game_board(char game_board[N][N], int board_size)
{
    for (int row = 0; row < board_size; row++)
    {
        for (int col = 0; col < board_size; col++)
        {
            game_board[row][col] = EMPTY_SPACE;
        }
    }
    print_board(game_board, board_size);
}

void game_ticker(char game_board[N][N], char game_history[MAX_TICKS][N][N], int board_size)
{
    int current_game_tick = 0, is_board_valid = true;
    print_player_turn(1);
    while (is_board_valid)
    {
        current_game_tick = tick_handler(game_board, game_history, board_size, current_game_tick, &is_board_valid);
    }
    // The board is no longer valid. That means someone won or there's a tie.
    if (current_game_tick == board_size * board_size)
    {
        // TIE.
        print_tie();
    }
    else
    {
        print_winner((current_game_tick % 2) + 1);
    }
}

void add_history_entry(char game_board[N][N], char history_board[MAX_TICKS][N][N], int board_size, int current_tick)
{
    for (int row = 0; row < board_size; row++)
    {
        for (int col = 0; col < board_size; col++)
        {
            history_board[current_tick][row][col] = game_board[row][col];
        }
    }
}

// Main logic for handling ticks
int tick_handler(char game_board[N][N], char game_history[MAX_TICKS][N][N], int board_size, int current_tick, int *valid_board)
{
    // Handle the tick.
    // Receive input.
    int row = 0, col = 0, result_tick = current_tick;
    // Print player input
    if (scanf("%d", &row))
    {
        // Check if this is a reverse or a valid input operation
        if (row < 0)
        {
            return handle_reverse(game_board, game_history, board_size, current_tick, row);
        }
        else
        {
            if (!scanf("%d", &col) || row > board_size || col > board_size || col == 0 || row == 0 || game_board[row - 1][col - 1] != EMPTY_SPACE)
            {
                print_error();
                return current_tick;
            }
            else
            {
                // Allowed move.
                return handle_entry(game_board, game_history, board_size, row, col, current_tick, valid_board);
            }
        }
    }
    if (*valid_board)
        print_player_turn((current_tick + 1) % 2 + 1);

    return result_tick;
}

// Reverses the board to a previous state
void reverse_board(char game_board[N][N], char game_history[MAX_TICKS][N][N], int board_size, int current_tick, int ticks)
{
    for (int row = 0; row < board_size; row++)
    {
        for (int col = 0; col < board_size; col++)
        {
            game_board[row][col] = game_history[current_tick + ticks][row][col];
        }
    }
}

// Returns whether the given column is valid for a new tick
int validate_column(char game_board[N][N], int board_size, int column)
{
    for (int row = 1; row < board_size; row++)
    {
        char current = game_board[row][column], previous = game_board[row - 1][column];
        if (current == EMPTY_SPACE || previous == EMPTY_SPACE || current != previous)
            return true;
    }
    return false;
}

// Returns whether the given row is valid for a new tick
int validate_row(char game_board[N][N], int board_size, int row)
{
    for (int column = 1; column < board_size; column++)
    {
        char current = game_board[row][column], previous = game_board[row][column - 1];
        if (current == EMPTY_SPACE || previous == EMPTY_SPACE || current != previous)
            return true;
    }
    return false;
}

// Returns whether the primary diagonal is valid for a new tick
int validate_primary_diagonal(char game_board[N][N], int board_size)
{
    for (int i = 1; i < board_size; i++)
    {
        char current = game_board[i][i], previous = game_board[i - 1][i - 1];
        if (current == EMPTY_SPACE || previous == EMPTY_SPACE || current != previous)
            return true;
    }
    return false;
}

// Returns whether the secondary diagonal within the board is valid for a new tick
int validate_secondary_diagonal(char game_board[N][N], int board_size)
{
    for (int i = 1; i < board_size; i++)
    {
        char current = game_board[i][board_size - i - 1], previous = game_board[i - 1][board_size - i];
        if (current == EMPTY_SPACE || previous == EMPTY_SPACE || current != previous)
            return true;
    }
    return false;
}

// Returns whether the board is valid for a new tick or not
int validate_board(char game_board[N][N], int board_size, int column, int row)
{
    return validate_primary_diagonal(game_board, board_size) && validate_secondary_diagonal(game_board, board_size) &&
           validate_column(game_board, board_size, column) && validate_row(game_board, board_size, row) && !is_board_full(game_board, board_size);
}

// Checks whether the board is completely full.
int is_board_full(char game_board[N][N], int board_size)
{
    for (int row = 0; row < board_size; row++)
    {
        for (int col = 0; col < board_size; col++)
        {
            if (game_board[row][col] == EMPTY_SPACE)
                return false;
        }
    }
    return true;
}

int handle_reverse(char game_board[N][N], char history_board[MAX_TICKS][N][N], int board_size, int current_tick, int ticks)
{
    if (ticks % 2 == 0)
    {
        print_error();
        return current_tick;
    }
    reverse_board(game_board, history_board, board_size, current_tick, ticks);
    print_board(game_board, board_size);
    print_player_turn((current_tick + 1) % 2 + 1);
    return current_tick + ticks;
}

int handle_entry(char game_board[N][N], char history_board[MAX_TICKS][N][N], int board_size, int row, int column, int current_tick, int *valid_board)
{
    add_history_entry(game_board, history_board, board_size, current_tick);
    game_board[row - 1][column - 1] = current_tick % 2 == 0 ? PLAYER_ONE : PLAYER_TWO;
    print_board(game_board, board_size);
    *valid_board = validate_board(game_board, board_size, column - 1, row - 1);
    if (*valid_board)
    {
        print_player_turn((current_tick + 1) % 2 + 1);
    }
    return current_tick + 1;
}
