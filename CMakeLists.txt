cmake_minimum_required(VERSION 3.13)
project(BattleShip)

set(CMAKE_C_STANDARD 11)

add_executable(BattleShip  main.cpp BattleShip.cpp BattleShip.h Board.cpp Board.h Move.h Move.cpp Player.h Player.cpp)