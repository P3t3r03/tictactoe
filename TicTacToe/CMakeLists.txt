cmake_minimum_required(VERSION 3.5)

project(TicTacToe)

# Add the executable target
add_executable(test 
    Test.cpp
    Game_state.cpp
    Game_state.hpp
    Opponent.hpp
)