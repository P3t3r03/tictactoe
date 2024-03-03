#ifndef __Opponent__ 
#define __Opponent__

#include "Game_state.hpp"
#include "bit_operations.hpp"
#include <iostream>
#include <cstdlib>

void random_move(game_state &game) {
        int index;
    do {
        // Generate random row and column numbers (1-3)
        int row = rand() % 3;
        int col = rand() % 3;
        index = row + col * 3;
    } while (((game.board_O | game.board_X) & (1 << index)) != 0);

    game.board_X = set_bit(game.board_X, index);
}


void Opponent_turn(game_state &game) {
    random_move(game);
    if(game_won(game.board_X)) {
        print_game(game);
        std::cout << "The X's (Opponent) Won!!" << std::endl;
        game.won = true;
    }
    else {
        game.turn = !game.turn;
        take_turn(game);   
    }
}

#endif
