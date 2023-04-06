//
//  Created by Tobin Joseph on 2019-06-03.
//

#include <sstream>
#include <ctime>
#include "Utility.h"
#include "AiPlayer.h"
#include "Player.h"

#include <string>
//#include "Move.h"

#include "Board.h"
#include "Move.h"




#include <map>

int BattleShip::AiPlayer::nextAiId = 1;
std::mt19937 BattleShip::AiPlayer::randomNumberGenerator((time(nullptr)));

BattleShip::AiPlayer::AiPlayer(const std::string& name, Board& placementBoard,
                               Board& firingBoard, std::map<char, Ship>& shipsDetailsMap, char hitPiece, char missPiece,
                               std::vector<ShipLocation>& shipLocationsVec) :
        Player(name, placementBoard, firingBoard, shipsDetailsMap, hitPiece, missPiece,shipLocationsVec), aiId(1) {
}


void BattleShip::AiPlayer::seed_random_number_generator(int seed) {
    BattleShip::AiPlayer::randomNumberGenerator.seed(seed);
}

std::mt19937 BattleShip::AiPlayer::getRNG(){
    return randomNumberGenerator;
}

const int BattleShip::AiPlayer::getAndIncrementNextAiId(){
    return ++nextAiId;
}
