//
// Created by Tobin Joseph on 2019-06-03.
//

#include <iostream>
#include "BattleShip.h"
#include "Player.h"
#include "Utility.h"
#include <random>
#include <vector>
#include <iterator>

int main(int argc, char** argv) {
    if (argc < 2 || argc > 3) return -1;
    std::string tempSeedString = "";
    if (argc == 3) {
        tempSeedString = argv[2];
    }

    if (argc == 2)
        BattleShip::AiPlayer::seed_random_number_generator(time(nullptr));
    else
        BattleShip::AiPlayer::seed_random_number_generator(stoi(tempSeedString));

    BattleShip::BattleShip game(argv[1], tempSeedString);
    game.play();
    return 0;
}
