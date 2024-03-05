#include "Game_state.hpp"
#include "bit_operations.hpp"
#include "Opponent.hpp"

#include <iostream>
#include <bitset>
#include <cmath>

void print_game(const game_state &game) {
    if((game.board_O & game.board_X) == 0){
        std::cout <<  "-------" << std::endl;
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
            std::cout << "|" << std::endl << "-------" << std::endl;
        }
    }
    else {
        std::cout << "Error in Game State" << std::endl;
    }
}


bool game_won(const uint16_t &board, const uint8_t &gridsize) {
    /*for(int i = 0; i < 3; i++) {
        uint16_t test_vert = (board >> (i*3));  // For Vertical wins
        uint16_t test_hori = (board >> i);
        if((test_vert & 7) == 7) { //Uses 7 here as it's bit representation is 111
            return true;
        }
        if((test_hori & 73) == 73) { // Uses 73 as it's bit representaiton is 1001001 need to and it in case other numbers are in there
            return true;
        }
        if((board & 84) == 84) { // binary representation of 001010100 is 84 also and'd
            return true;
        }
        if((board & 273) == 273) { // binary representation of 100010001 is 273 also and'd
            return true;
        }
    }
    return false;*/
    bool tl_br = true;
    bool tr_bl= true;
    for(int i = 0; i < gridsize; i++) {
        bool row = true;
        bool col = true;
        tl_br &= get_bit(board, (gridsize+1)*i);
        tr_bl &= get_bit(board, (gridsize-1) + (gridsize-1)*i);
        for(int j = 0; j < gridsize; j++){
            row &= get_bit(board, i + gridsize*j);
            col &= get_bit(board, gridsize*i + j);
            std::cout << row << ", " << col << std::endl;
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
void take_turn(game_state &game) {
    print_game(game);
    if(game.turn) {

        int row, col, index;
        std::cout << "Enter the Row you would like to play: ";
        std::cin >> row ;
        std::cout << "Enter the Column you would like to play: ";
        std::cin >> col;
        row -= 1;
        col -= 1;
        index = row + col * game.gridsize;
        if(row < game.gridsize && col < game.gridsize && (((game.board_O | game.board_X) & (1 << index)) == 0)) {
            game.board_O = set_bit(game.board_O, index);
            if(game_won(game.board_O, game.gridsize)) {
                print_game(game);
                std::cout << "The O's Won!!" << std::endl;
                game.won = true;
            }
            else {
                std::cout << (std::pow(2,(std::pow(game.gridsize,2)))-1) << std::endl;
                if ((game.board_O | game.board_X) == (std::pow(2,(std::pow(game.gridsize,2)))-1)) { //511 is the representation of 111111111
                    std::cout << "The Game was a Draw" << std::endl;
                    game.won = true;
                    print_game(game);
                }
                else{
                    game.turn = !game.turn;
                    take_turn(game);
                }
            }
        }
            
        else{
            std::cout << "You entered an incorrect value for the row or column please retry" << std::endl;
            take_turn(game);
        }
    }
    else {
        Opponent_turn(game);
    }
}
