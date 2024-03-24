#include "Game_state.hpp"
#include "bit_operations.hpp"
#include "Opponent.hpp"

#include <iostream>
#include <bitset>
#include <cmath>

void print_game(const game_state &game) {
    if((game.board_O & game.board_X) == 0){
        std::cout << std::endl << std::endl;
        std::cout <<  std::string(2*(game.gridsize)+1, '-') << std::endl;
        for(int i = 0; i < game.gridsize; i++) {
            for(int j = 0; j < game.gridsize; j++) {
                std::cout << "|";
                if(get_bit(game.board_O, i + j*game.gridsize)) {
                    std::cout << "O";
                }
                else if(get_bit(game.board_X, i + j*game.gridsize)) {
                    std::cout << "X";
                }
                else {
                    std::cout << " ";
                }                
            }
            std::cout << "|" << std::endl << std::string(2*(game.gridsize)+1, '-') << std::endl;
        }

    }
    else {
        std::bitset<64> board_O(game.board_O);
        std::bitset<64> board_X(game.board_X);
        std::cout << board_O << std::endl << board_X << std::endl;
        std::cout << "Error in Game State" << std::endl; 
    }
}


bool game_won(const uint64_t &board, const int &gridsize) {
    bool tl_br = true; // Checks for Diagonals
    bool tr_bl= true;
    for(int i = 0; i < gridsize; i++) {
        bool row = true;
        bool col = true;
        tl_br &= get_bit(board, (gridsize+1)*i);
        tr_bl &= get_bit(board, (gridsize-1) + (gridsize-1)*i);
        for(int j = 0; j < gridsize; j++){
            row &= get_bit(board, i + gridsize*j);
            col &= get_bit(board, gridsize*i + j);
        }
        if(row || col) {
            return true;
        }
    }
    if (tl_br || tr_bl) {
        return true;
    }
    return false;
}

bool is_tie(const game_state &game) {
    //Returns true if it is a tie
    if((game.board_O | game.board_X) == (std::pow(2,(std::pow(game.gridsize,2)))-1)) {
        return true;
    }
    return false;
}

void take_turn(game_state &game, int depth) {
    print_game(game);
    if(game.turn) {

        int row, col, index;
        std::cout << "Enter the Row you would like to play: ";
        std::cin >> row;
        std::cout << "Enter the Column you would like to play: ";
        std::cin >> col;
        row -= 1;
        col -= 1;
        index = row + col * game.gridsize;
        if(row < game.gridsize && col < game.gridsize && (((game.board_O | game.board_X) & (static_cast<uint64_t>(1) << index)) == 0)) {
            game.board_O = set_bit_true(game.board_O, index);
            if(game_won(game.board_O, game.gridsize)) {
                print_game(game);
                std::cout << "The O's Won!!" << std::endl;
                game.won = true;
            }
            else {
                if (is_tie(game)) { 
                    std::cout << "The Game was a Draw" << std::endl;
                    game.won = true;
                    print_game(game);
                }
                else{
                    game.turn = !game.turn;
                    take_turn(game, depth);
                }
            }
        }
            
        else{
            std::cout << "You entered an incorrect value for the row or column please retry" << std::endl;
            take_turn(game, depth);
        }
    }
    else {
        Opponent_turn(game, depth);
    }
}
