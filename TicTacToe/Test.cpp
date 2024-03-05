#include "Game_state.hpp"

#include<iostream>


int main() {
    game_state game;
    std::cout << "Welcome to a simple TicTacToe Game!" << std::endl;
    std::cout << "Please choose the grid size you want(1-8): ";
    std::cin >> game.gridsize;
    game.board_O = 0;
    game.board_X = 0;
    game.turn = true;
    game.won = false;
    take_turn(game);
    return 0;
}
