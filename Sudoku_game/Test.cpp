#include "Game_state.hpp"

#include<iostream>


int main() {

    game_state game;
    game.board_O = 0;
    game.board_X = 0;
    game.turn = false;
    game.won = false;
    take_turn(game);
    return 0;
}
