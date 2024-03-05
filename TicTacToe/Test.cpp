#include "Game_state.hpp"

#include<iostream>


int main() {

    game_state game;
    game.board_O = 0;
    game.board_X = 0;
    game.turn = true;
    game.won = false;
    game.gridsize = 4;
    take_turn(game);
    return 0;
}
