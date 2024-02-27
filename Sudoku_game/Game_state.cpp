#include "Game_state.hpp"
#include "bit_operations.hpp"

#include <iostream>
#include <bitset>

void print_game(const game_state &game) {
    if((game.board_O & game.board_X) == 0){
        std::cout << "In here lol " << std::endl;
        std::cout << std::bitset<9>(game.board_O) << std::endl;
        std::cout << std::bitset<9>(game.board_X) << std::endl;
        std::cout <<  "-------" << std::endl;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                std::cout << "|";
                if(get_bit(game.board_O, i + j*3)) {
                    std::cout << "O";
                }
                else if(get_bit(game.board_X, i*3 + j)) {
                    std::cout << "X";
                }
                else {
                    std::cout << " ";
                }                
            }
            std::cout << "|" << std::endl << "-------" << std::endl;
        }
    }
    else {
        std::cout << "Error in Game State" << std::endl;
    }
}


bool game_won(const game_state &game) {
    return false;
}
void take_turn(game_state &game) {
    print_game(game);

    int row, col, index;
    std::cout << "Enter the Row you would like to play: ";
    std::cin >> row ;
    std::cout << "Enter the Column you would like to play: ";
    std::cin >> col;
    row -= 1;
    col -= 1;
    if(row < 3 && col < 3) {
        index = row + col * 3;
        game.board_O = set_bit(game.board_O, index);
        game.turn |= game.turn;
    }
    else{
        std::cout << "You entered an incorrect value for the row or column please retry" << std::endl;
        take_turn(game);
    }
}
