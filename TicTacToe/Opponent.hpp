#ifndef __Opponent__ 
#define __Opponent__

#include "Game_state.hpp"
#include "bit_operations.hpp"
#include <iostream>
#include <cstdlib>
#include <algorithm>

void random_move(game_state &game) {
        int index;
    do {
        // Generate random row and column numbers (1-3)
        int row = rand() % game.gridsize;
        int col = rand() % game.gridsize;
        index = row + col * game.gridsize;
    } while (((game.board_O | game.board_X) & (1 << index)) != 0);

    game.board_X = set_bit_true(game.board_X, index);
}


class minimax {
    public:


        move minimax_move(game_state &game, int depth) {

            int eval = std::numeric_limits<int>::max();
            move optimal_move;
            int pos_looked_at = 0;

            int index;
            for(int row = 0; row < game.gridsize; row++) {
                for(int col = 0; col < game.gridsize; col++) {
                    index = row + col*game.gridsize; 
                    if(((game.board_O | game.board_X) & (static_cast<uint64_t>(1) << index)) == 0) {
                        game.board_X = set_bit_true(game.board_X, index);
                        pos_looked_at += 1;
                        int temp = MaxSearch(game, depth - 1, pos_looked_at);

                        if (temp < eval) {
                            eval = temp;
                            optimal_move.row = row;
                            optimal_move.col = col;
                        }
                        game.board_X = set_bit_false(game.board_X, index);
                    }
                }
            }
            std::cout << "positions looked at: " << pos_looked_at << " with eval of: " << eval << std::endl;
            return optimal_move;           
        }

        int MaxSearch(game_state &game, int depth, int &pos_looked_at) {
            if (game_won(game.board_X, game.gridsize)) {
                return -1;
            }
            else if (is_tie(game)) {
                return 0;
            }
            else if (depth == 0) {
                return 0;
            }
            int eval = std::numeric_limits<int>::min();
            for (int row = 0; row < game.gridsize; row++) {
                for (int col = 0; col < game.gridsize; col++) {
                    int index = row + col*game.gridsize;
                    if(((game.board_O | game.board_X) & (static_cast<uint64_t>(1) << index)) == 0) {
                        game.board_O = set_bit_true(game.board_O, index);
                        pos_looked_at += 1;
                        eval = std::max(eval, MinSearch(game, depth -1, pos_looked_at));
                        game.board_O = set_bit_false(game.board_O, index);
                    }
                }
            }
            return eval;
        }

        int MinSearch(game_state &game, int depth, int &pos_looked_at) {
            if (game_won(game.board_O, game.gridsize)) {
                return 1;
            }
            else if (is_tie(game)) {
                return 0;
            }
            else if (depth == 0) {
                return 0;
            }
            int eval = std::numeric_limits<int>::max();
            for (int row = 0; row < game.gridsize; row++) {
                for (int col = 0; col < game.gridsize; col++) {
                    int index = row + col*game.gridsize;
                    if(((game.board_O | game.board_X) & (static_cast<uint64_t>(1) << index)) == 0) {
                        game.board_X = set_bit_true(game.board_X, index);
                        pos_looked_at += 1;
                        eval = std::min(eval, MaxSearch(game, depth - 1, pos_looked_at));
                        game.board_X = set_bit_false(game.board_X, index);
                    }
                }
            }
            return eval;
        }
};


void Opponent_turn(game_state &game, int depth) {
    minimax optimal_move_finder;
    move optimal_move = optimal_move_finder.minimax_move(game, depth);
    std::cout << "Optimal Move Row: " << optimal_move.row << " Col: " << optimal_move.col << std::endl;
    int index = optimal_move.row + optimal_move.col*game.gridsize;
    game.board_X = set_bit_true(game.board_X, index);
    if(game_won(game.board_X, game.gridsize)) {
        print_game(game);
        std::cout << "The X's (Opponent) Won!!" << std::endl;
        game.won = true;
    }
    else {
        if (is_tie(game)) {
            std::cout << "The Game was a Draw" << std::endl;
            game.won = true;
            print_game(game);
        }
        else {
            game.turn = !game.turn;
            take_turn(game, depth);  
        }
    }
}

#endif
