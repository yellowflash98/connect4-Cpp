//
// Created by Tobin Joseph on 2019-06-03.
//


#ifndef BATTLESHIP_2_UTILITY_H
#define BATTLESHIP_2_UTILITY_H

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <random>
#include <map>
#include <string>
#include "Board.h"

namespace BattleShip {


    struct GameAttributes
    {
        int gameRows;
        int gameColumns;
        int shipsCount;
        std::map<char, int> shipsInfoMap;
        int gameType;
        std::string seedForRNG;
    };



    struct ShipLocation {
        int row;
        int col;
        char shipSymbol;
        int shipLength;
        int hit;
        char shipOrientation;
    };


    class View {

    };


    template<typename ValueType, typename ContainerType>
    bool contains(const ValueType& value, const ContainerType& container) {
        return std::find(container.begin(), container.end(), value) != container.end();
    }

    template<typename T>
    void verifiedRead(std::istream& in, T& val) {
        if (in) {
            in >> val;
            if (!in) {
                throw std::logic_error("Failed to read in value. Value formatted incorrectly");
            }
        } else {
            throw std::logic_error("Failed to read as stream is no longer good.");
        }
    }

/*
template<typename RngType>
Move TicTacToeGame::AiPlayer<RngType>::selectRandom(const std::vector<Move>& values) {
  auto itr = values.cbegin();
  auto max_choice = std::distance(values.cbegin(), values.cend()) - 1;
  std::uniform_int_distribution<unsigned int> dis(0, max_choice);
  auto move_amount = dis(generator);
  std::advance(itr, move_amount);
  return  *itr;
}
*/

//std::vector<char> orientation_choice{'h', 'v'};
//shipOrientation = *chooseRandom(orientation_choice, AiPlayer::getRNG());

    template <typename ContainerType, typename RandomGeneratorType>
    typename ContainerType::const_iterator chooseRandom(const ContainerType& container, RandomGeneratorType rand_gen){
        int num_elements = std::distance(container.cbegin(), container.cend());
        std::uniform_int_distribution<> distribution(0,  num_elements -1);
        auto itr = container.cbegin();
        int move_amount = distribution(rand_gen);
        std::advance(itr, move_amount);
        return itr;
    }

//get a random number between [min,max]
    template <typename RandomGeneratorType>
    int getRandInt(int min, int max, RandomGeneratorType generator){
        std::uniform_int_distribution<> distribution(min, max);
        return distribution(generator);
    }

}



#endif //BATTLESHIP_UTILITY_H
