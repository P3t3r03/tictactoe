#ifndef __tictactoe_state__
#define __tictactoe_state__

#include<stdint.h>


struct game_state {
    uint64_t board_O;  // using as I want to use a uint64 for a chess engine in the future
    uint64_t board_X; // using as I want to use a uint64 for a chess engine in the future
    bool turn; //true for O false for X 
    bool won; 
    int gridsize;
};

void print_game(const game_state &game);

bool game_won(const uint64_t &board, const int &gridsize);

void take_turn(game_state &game);

#endif
