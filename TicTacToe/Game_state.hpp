#ifndef __tictactoe_state__
#define __tictactoe_state__

#include<stdint.h>


struct game_state {
    uint16_t board_O;  // using as I want to use a uint64 for a chess engine in the future
    uint16_t board_X; // using as I want to use a uint64 for a chess engine in the future
    bool turn; //true for O false for X 
    bool won; 
    uint8_t gridsize;
};

void print_game(const game_state &game);

bool game_won(const uint16_t &board, const uint8_t &gridsize);

void take_turn(game_state &game);

#endif
