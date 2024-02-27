#include "Game_state.hpp"

#include<iostream>


int main() {
    uint16_t X = 33;
    uint16_t O = 2;
    bool turn = false;
    bool game_won = false;
    game_state game;
    game.board_O = O;
    game.board_X = X;
    game.turn = turn;
    while(!game_won) {
        take_turn(game);
        take_turn(game);
        take_turn(game);
    }
    take_turn(game);
    return 0;
}
