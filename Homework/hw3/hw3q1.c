/*-------------------------------------------------------------------------
    Include files:
-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>

/*-------------------------------------------------------------------------
    Constants and definitions:
-------------------------------------------------------------------------*/
#define N 11
#define MAX_TICKS N *N
#define EMPTY_SPACE '_'
#define PLAYER_ONE 'X'
#define PLAYER_TWO 'O'
#define NUM_OF_PLAYERS 2
#define PLAYER_ONE_NUM 1
#define PLAYER_TWO_NUM 0
#define EVEN 0
#define UNEVEN 1
#define ONE_INDEX 1

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
void game_ticker(char game_board[N][N], char game_history[MAX][N][N], int board_size);
void add_history_entry(char game_board[N][N], char history_board[MAX][N][N], int board_size, int current_tick);
int tick_handler(char game_board[N][N], char game_history[MAX][N][N], int board_size, int current_tick, int *valid_board);
void reverse_board(char game_board[N][N], char game_history[MAX][N][N], int board_size, int current_tick, int ticks);
int validate_column(char game_board[N][N], int board_size, int column);
int validate_row(char game_board[N][N], int board_size, int row);
int validate_primary_diagonal(char game_board[N][N], int board_size);
int validate_secondary_diagonal(char game_board[N][N], int board_size);
int validate_board(char game_board[N][N], int board_size, int column, int row);
int is_board_full(char game_board[N][N], int board_size);
int handle_reverse(char game_board[N][N], char history_board[MAX][N][N], int board_size, int current_tick, int ticks);
int handle_entry(char game_board[N][N], char history_board[MAX][N][N], int board_size, int row, int column, int current_tick, int *valid_board);
int is_valid_input(int *col, int row, int board_size, char game_board[N][N]);
int main();

/*-------------------------------------------------------------------------
    Implementation
-------------------------------------------------------------------------*/

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

/***********************************************
 * NAME:        main
 * 
 * DESCRIPTION: Main program function
 * 
 * LENGTH:
 *      2 lines
***********************************************/
int main()
{
    initialize_game();
    return 0;
}

/***********************************************
 * NAME:        initialize_game
 * 
 * DESCRIPTION: Initializes the game-required variables and board
 * 
 * LENGTH:
 *      7 lines
***********************************************/
void initialize_game()
{
    char game_board[N][N], history_board[MAX][N][N];
    int board_size = 0;
    print_welcome();
    print_enter_board_size();
    scanf("%d", &board_size);
    // We received the board size. Initialize the board.
    initialize_game_board(game_board, board_size);
    game_ticker(game_board, history_board, board_size);
}

/***********************************************
 * NAME:        initialize_game_board
 * 
 * DESCRIPTION: Initializes the game board with empty spaces
 * 
 * INPUTS:
 *      char[N][N]      game_board      Visualization of game board
 *      int             board_size      Size of game board
 * 
 * LENGTH:
 *      4 lines
***********************************************/
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

/***********************************************
 * NAME:        game_ticker
 * 
 * DESCRIPTION: Main game logic for turns
 * 
 * INPUTS:
 *      char[N][N]              game_board      Visualization of game board
 *      char[MAX_TICKS][N][N]   game_history    History of the game board
 *      int                     board_size      Size of game board
 * 
 * LENGTH:
 *      8 lines
***********************************************/
void game_ticker(char game_board[N][N], char game_history[MAX][N][N], int board_size)
{
    int current_game_tick = 0, is_board_valid = true;
    print_player_turn(PLAYER_ONE_NUM);
    while (is_board_valid)
        current_game_tick = tick_handler(game_board, game_history, board_size, current_game_tick, &is_board_valid);
    // The board is no longer valid. That means someone won or there's a tie.
    if (current_game_tick == board_size * board_size)
        print_tie();
    else
        print_winner((current_game_tick % NUM_OF_PLAYERS) + 1);
}

/***********************************************
 * NAME:        history_entry
 * 
 * DESCRIPTION: Adds a copy of the game board to the history array
 * 
 * INPUTS:
 *      char[N][N]              game_board      Visualization of game board
 *      char[MAX_TICKS][N][N]   game_history    History of the game board
 *      int                     board_size      Size of game board
 *      int                     current_tick    Number of current turn
 * 
 * LENGTH:
 *      3 lines
***********************************************/
void add_history_entry(char game_board[N][N], char history_board[MAX][N][N], int board_size, int current_tick)
{
    for (int row = 0; row < board_size; row++)
    {
        for (int col = 0; col < board_size; col++)
        {
            history_board[current_tick][row][col] = game_board[row][col];
        }
    }
}

/***********************************************
 * NAME:        tick_handler
 * 
 * DESCRIPTION: Handles the logic for each seperate game tick
 * 
 * INPUTS:
 *      char[N][N]              game_board      Visualization of game board
 *      char[MAX_TICKS][N][N]   game_history    History of the game board
 *      int                     board_size      Size of game board
 *      int                     current_tick    Number of current turn
 *      int*                    valid_board     Pointer to state of board validity (0/1)
 * 
 * OUTPUT:
 *      current_tick            The tick the game should be continued on:
 *                                  - Current game tick if input is invalid
 *                                  - Next game tick if valid entry
 *                                  - current_tick - reverse if undo function
 * 
 * LENGTH:
 *      11 lines
***********************************************/
int tick_handler(char game_board[N][N], char game_history[MAX][N][N], int board_size, int current_tick, int *valid_board)
{
    int row = 0, col = 0;
    scanf("%d", &row);
    if (row < 0)
        return handle_reverse(game_board, game_history, board_size, current_tick, row);
    else
    {
        if (is_valid_input(&col, row, board_size, game_board))
        {
            print_error();
            return current_tick;
        }
        else
            return handle_entry(game_board, game_history, board_size, row, col, current_tick, valid_board);
    }
    return current_tick;
}

/***********************************************
 * NAME:        reverse_board
 * 
 * DESCRIPTION: Reverses the game board by a specific number of turns
 * 
 * INPUTS:
 *      char[N][N]              game_board      Visualization of game board
 *      char[MAX_TICKS][N][N]   game_history    History of the game board
 *      int                     board_size      Size of game board
 *      int                     current_tick    Number of current turn
 *      int                     ticks           Number of ticks to reverse board by
 * 
 * LENGTH:
 *      3 lines
***********************************************/
void reverse_board(char game_board[N][N], char game_history[MAX][N][N], int board_size, int current_tick, int ticks)
{
    for (int row = 0; row < board_size; row++)
    {
        for (int col = 0; col < board_size; col++)
        {
            game_board[row][col] = game_history[current_tick + ticks][row][col];
        }
    }
}

/***********************************************
 * NAME:        validate_column
 * 
 * DESCRIPTION: Validates the given column within the board
 * 
 * INPUTS:
 *      char[N][N]              game_board      Visualization of game board
 *      int                     board_size      Size of game board
 *      int                     column          Index of column to validate
 * 
 * OUTPUT:
 *      0           Column is not valid (there is a win)
 *      1           Column is valid, game can continue
 * 
 * LENGTH:
 *      6 lines
***********************************************/
int validate_column(char game_board[N][N], int board_size, int column)
{
    for (int row = 1; row < board_size; row++)
    {
        char current = game_board[row][column], previous = game_board[row - ONE_INDEX][column];
        if (current == EMPTY_SPACE || previous == EMPTY_SPACE || current != previous)
            return true;
    }
    return false;
}

/***********************************************
 * NAME:        validate_row
 * 
 * DESCRIPTION: Validates the given row within the board
 * 
 * INPUTS:
 *      char[N][N]              game_board      Visualization of game board
 *      int                     board_size      Size of game board
 *      int                     row          Index of row to validate
 * 
 * OUTPUT:
 *      0           Row is not valid (there is a win)
 *      1           Row is valid, game can continue
 * 
 * LENGTH:
 *      6 lines
***********************************************/
int validate_row(char game_board[N][N], int board_size, int row)
{
    for (int column = 1; column < board_size; column++)
    {
        char current = game_board[row][column], previous = game_board[row][column - ONE_INDEX];
        if (current == EMPTY_SPACE || previous == EMPTY_SPACE || current != previous)
            return true;
    }
    return false;
}

/***********************************************
 * NAME:        validate_primary_diagonal
 * 
 * DESCRIPTION: Validates the primary diagonal within the board
 * 
 * INPUTS:
 *      char[N][N]              game_board      Visualization of game board
 *      int                     board_size      Size of game board
 * 
 * OUTPUT:
 *      0           Primary diagonal is not valid (there is a win)
 *      1           Primary diagonal is valid, game can continue
 * 
 * LENGTH:
 *      6 lines
***********************************************/
int validate_primary_diagonal(char game_board[N][N], int board_size)
{
    for (int i = 1; i < board_size; i++)
    {
        char current = game_board[i][i], previous = game_board[i - ONE_INDEX][i - ONE_INDEX];
        if (current == EMPTY_SPACE || previous == EMPTY_SPACE || current != previous)
            return true;
    }
    return false;
}

/***********************************************
 * NAME:        validate_secondary_diagonal
 * 
 * DESCRIPTION: Validates the secondary diagonal within the board
 * 
 * INPUTS:
 *      char[N][N]              game_board      Visualization of game board
 *      int                     board_size      Size of game board
 * 
 * OUTPUT:
 *      0           Secondary diagonal is not valid (there is a win)
 *      1           Secondary diagonal is valid, game can continue
 * 
 * LENGTH:
 *      6 lines
***********************************************/
int validate_secondary_diagonal(char game_board[N][N], int board_size)
{
    for (int i = 1; i < board_size; i++)
    {
        char current = game_board[i][board_size - i - ONE_INDEX], previous = game_board[i - ONE_INDEX][board_size - i];
        if (current == EMPTY_SPACE || previous == EMPTY_SPACE || current != previous)
            return true;
    }
    return false;
}

/***********************************************
 * NAME:        validate_board
 * 
 * DESCRIPTION: Checks validity of the board and whether the game can continue.
 *              Function is called once an input is valid.
 * 
 * INPUTS:
 *      char[N][N]              game_board      Visualization of game board
 *      int                     board_size      Size of game board
 *      int                     column          Column of the last given input
 *      int                     row             Row of the last given input
 * 
 * OUTPUT:
 *      0           Board is not valid (there is a win/tie)
 *      1           Board is valid, game can continue
 * 
 * LENGTH:
 *      4 lines
***********************************************/
int validate_board(char game_board[N][N], int board_size, int column, int row)
{
    return validate_primary_diagonal(game_board, board_size) && validate_secondary_diagonal(game_board, board_size) &&
           validate_column(game_board, board_size, column) && validate_row(game_board, board_size, row) && !is_board_full(game_board, board_size);
}

/***********************************************
 * NAME:        is_board_full
 * 
 * DESCRIPTION: Checks whether the board is full or not
 * 
 * INPUTS:
 *      char[N][N]              game_board      Visualization of game board
 *      int                     board_size      Size of game board
 * 
 * OUTPUT:
 *      0           Board is full, tie
 *      1           Board still has empty cells, game can continue
 * 
 * LENGTH:
 *      5 lines
***********************************************/
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

/***********************************************
 * NAME:        handle_reverse
 * 
 * DESCRIPTION: Validates the given reverse request and performs it
 * 
 * INPUTS:
 *      char[N][N]              game_board      Visualization of game board
 *      char[MAX_TICKS][N][N]   history_board   History of the game board
 *      int                     board_size      Size of game board
 *      int                     current_tick    Current game tick (turn)
 *      int                     ticks           Number of ticks to reverse by
 * 
 * OUTPUT:
 *      current_tick            Returns the tick the game should carry on from:
 *                                  - Current tick if reverse is invalid
 *                                  - Current tick - requested ticks reversed
 * 
 * LENGTH:
 *      7 lines
***********************************************/
int handle_reverse(char game_board[N][N], char history_board[MAX][N][N], int board_size, int current_tick, int ticks)
{
    if (ticks % NUM_OF_PLAYERS == EVEN)
    {
        print_error();
        return current_tick;
    }
    reverse_board(game_board, history_board, board_size, current_tick, ticks);
    print_board(game_board, board_size);
    print_player_turn((current_tick + ONE_INDEX) % NUM_OF_PLAYERS + ONE_INDEX);
    return current_tick + ticks;
}

/***********************************************
 * NAME:        handle_reverse
 * 
 * DESCRIPTION: Validates the given reverse request and performs it
 * 
 * INPUTS:
 *      char[N][N]              game_board      Visualization of game board
 *      char[MAX_TICKS][N][N]   history_board   History of the game board
 *      int                     board_size      Size of game board
 *      int                     row             Row index of last gievn input
 *      int                     column          Column index of last given input
 *      int                     current_tick    Current game tick (turn)
 *      int*                    valid_board     Pointer to state of validity of game board
 * 
 * OUTPUT:
 *      current_tick + 1
 * 
 * LENGTH:
 *      7 lines
***********************************************/
int handle_entry(char game_board[N][N], char history_board[MAX][N][N], int board_size, int row, int column, int current_tick, int *valid_board)
{
    add_history_entry(game_board, history_board, board_size, current_tick);
    game_board[row - ONE_INDEX][column - ONE_INDEX] = current_tick % NUM_OF_PLAYERS == EVEN ? PLAYER_ONE : PLAYER_TWO;
    print_board(game_board, board_size);
    *valid_board = validate_board(game_board, board_size, column - ONE_INDEX, row - ONE_INDEX);
    if (*valid_board)
    {
        print_player_turn((current_tick + ONE_INDEX) % NUM_OF_PLAYERS + ONE_INDEX);
    }
    return current_tick + ONE_INDEX;
}

/***********************************************
 * NAME:        is_valid_input
 * 
 * DESCRIPTION: Fool-proofs the row and column inputs given by the user, makes sure they are valid and useable
 * 
 * INPUTS:
 *      char[N][N]              game_board      Visualization of game board
 *      int                     board_size      Size of game board
 *      int                     row             Row index of last given input
 *      int*                    col             Pointer to column index of last given input
 * 
 * OUTPUT:
 *      1               Input is valid
 *      0               Input invalid
 * 
 * LENGTH:
 *      7 lines
***********************************************/
int is_valid_input(int *col, int row, int board_size, char game_board[N][N])
{
    return !scanf("%d", col) || row > board_size || *col > board_size ||
           *col == 0 || row == 0 || game_board[row - ONE_INDEX][*col - ONE_INDEX] != EMPTY_SPACE;
}
