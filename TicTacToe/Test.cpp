#include "Game_state.hpp"

#include<iostream>
#include<chrono>


int main() {
    game_state game;
    int depth;
    std::cout << "Welcome to a simple TicTacToe Game!" << std::endl;
    std::cout << "Please choose the grid size you want(1-8): ";
    std::cin >> game.gridsize;
    std::cout << "Please choose a depth for the minimax algorithm to search(recommended 6 for higher then 3x3): ";
    std::cin >> depth;
    //Starting time
    game.board_O = 0;
    game.board_X = 0;
    game.turn = true;
    game.won = false;
    take_turn(game, depth);
    return 0;
}
