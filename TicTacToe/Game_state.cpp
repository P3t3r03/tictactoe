#include "Game_state.hpp"
#include "bit_operations.hpp"
#include "Opponent.hpp"

#include <iostream>
#include <bitset>

void print_game(const game_state &game) {
    if((game.board_O & game.board_X) == 0){
        std::cout <<  "-------" << std::endl;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                std::cout << "|";
                if(get_bit(game.board_O, i + j*3)) {
                    std::cout << "O";
                }
                else if(get_bit(game.board_X, i + j*3)) {
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


bool game_won(const uint16_t &board) {
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
    for(int i = 0; i < 3; i++) {
        bool row = true;
        bool col = true;
        tl_br &= get_bit(board, 4*i);
        tr_bl &= get_bit(board, 2 + 2*i);
        for(int j = 0; j < 3; j++){
            row &= get_bit(board, i + 3*j);
            std::cout << row << std::endl;
            col &= get_bit(board, 3*j + i);
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
        index = row + col * 3;
        if(row < 3 && col < 3 && (((game.board_O | game.board_X) & (1 << index)) == 0)) {
            game.board_O = set_bit(game.board_O, index);
            if(game_won(game.board_O)) {
                print_game(game);
                std::cout << "The O's Won!!" << std::endl;
                game.won = true;
            }
            else {
                if ((game.board_O | game.board_X) == 511) { //511 is the representation of 111111111
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
