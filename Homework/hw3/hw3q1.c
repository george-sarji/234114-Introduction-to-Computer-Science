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
void tick_handler(char game_board[N][N], char game_history[MAX_TICKS][N][N], int board_size, int current_tick);

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
}

void game_ticker(char game_board[N][N], char game_history[MAX_TICKS][N][N], int board_size)
{
    bool is_board_valid = true;
    int current_game_tick = 0;
    while (is_board_valid)
    {
        tick_handler(game_board, game_history, board_size, current_game_tick);
        current_game_tick++;
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

void tick_handler(char game_board[N][N], char game_history[MAX_TICKS][N][N], int board_size, int current_tick)
{
    // Handle the tick.
    // Receive input.
    int row = 0, col = 0;
    bool throw_error = false;
    // Print player input
    print_player_turn(current_tick % 2 + 1);
    if (!scanf("%d", &row))
    {
        // Throw error
        throw_error = true;
    }
    else
    {
        // Check if this is a reverse or a valid input operation
        if (row < 0)
        {
            // Reverse
        }
        else
        {
            if (!scanf("%d", &col) || row > board_size || col > board_size || col == 0 || row == 0 || game_board[row][col] != EMPTY_SPACE)
            {
                print_error();
            }
            else
            {
                // Allowed move.
                game_board[row][col] = current_tick % 2 == 0 ? PLAYER_ONE : PLAYER_TWO;
                print_board(game_board, board_size);
            }
        }
    }
}
