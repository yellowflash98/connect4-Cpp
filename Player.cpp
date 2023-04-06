//
// Created by Tobin Joseph on 2019-06-03.
//

#include "Player.h"

#include <string>
//#include "Move.h"
#include "Player.h"
#include "Board.h"
#include "Move.h"

#include <sstream>
#include <ctime>
#include "Utility.h"
#include <map>


BattleShip::Ship::Ship(char shipSymbol, int shipLength, char shipOrientation, int placementRow, int placementColumn)
        :shipSymbol(shipSymbol),shipLength(shipLength),
         shipOrientation(shipOrientation), placementRow(placementRow),placementColumn(placementColumn)  {

}


//////////////////////////////////////////////////////////////////////////////////


BattleShip::Player::~Player() {}

BattleShip::Player::Player(const std::string& name, Board& placementBoard, Board& firingBoard,
                           std::map<char, Ship>& shipsDetailsMap, char hitPiece, char missPiece
        ,std::vector<ShipLocation>& shipLocsVec) :
        name(name), placementBoard(placementBoard), firingBoard(firingBoard), shipsDetailsMap(shipsDetailsMap),
        hitPiece(hitPiece),  missPiece(missPiece) {

    for (int n = 0; n < shipLocsVec.size(); n++) {

        ShipLocation tmp_struct = ShipLocation();
        tmp_struct.row = shipLocsVec[n].row;
        tmp_struct.col = shipLocsVec[n].col;
        tmp_struct.shipSymbol = shipLocsVec[n].shipSymbol;
        tmp_struct.shipLength = shipLocsVec[n].shipLength;
        tmp_struct.hit = shipLocsVec[n].hit;
        tmp_struct.shipOrientation = shipLocsVec[n].shipOrientation;
        shipLocationsVec.push_back(tmp_struct);

    }
}
const std::string& BattleShip::Player::getName() const {
    return name;
}

char BattleShip::Player::getHitPiece() const {
    return hitPiece;
}

char BattleShip::Player::getMissPiece() const {
    return missPiece;
}

const BattleShip::Board& BattleShip::Player::getPlacementBoard() const {
    return placementBoard;
}
const BattleShip::Board& BattleShip::Player::getFiringBoard() const {
    return firingBoard;
}

void BattleShip::Player::setPlacement(int row, int col, char val)  {
    placementBoard.set(row, col, val);
}

void BattleShip::Player::setFiring(int row, int col, char val)  {
    firingBoard.set(row, col, val);
}

BattleShip::BoardRandomMove BattleShip::Player::getMove() {
    BoardRandomMove randomMoveStruct; // = BoardRandomMove();
    return randomMoveStruct;
}


const std::vector<BattleShip::ShipLocation>& BattleShip::Player::getshipLocationsVec() const{
    return shipLocationsVec;
}

int BattleShip::Player::getRowOfCheatMove() const{

    for (int j= 0; j< placementBoard.getBoardColumns() ; j++ ){
        for (int i= 0; i<placementBoard.getBoardRows() ; i++){
            if ( placementBoard.at(i,j) != hitPiece && placementBoard.at(i,j) != missPiece &&  placementBoard.at(i,j) != '*')
                return i;
        }
    }
    return -1;
}

int BattleShip::Player::getColOfCheatMove() const {

    for (int j= 0; j< placementBoard.getBoardColumns() ; j++ ){
        for (int i= 0; i<placementBoard.getBoardRows() ; i++){
            if ( placementBoard.at(i,j) != hitPiece && placementBoard.at(i,j) != missPiece &&  placementBoard.at(i,j) != '*')
                return j;
        }
    }
    return -1;
}


bool BattleShip::Player::getPlayerHealth() const {
    int totalHits = 0;
    int totalBlanks = 0;
    for(int i=0; i<shipLocationsVec.size(); i++) {
        if (shipLocationsVec[i].hit == 1 ) {
            totalHits++;
        }
        if (shipLocationsVec[i].shipLength == 0 ) {
            totalBlanks++;
        }
        //std::cout << shipLocationsVec[i].row << " " << shipLocationsVec[i].col << " "
        //<< shipLocationsVec[i].shipSymbol << " " << shipLocationsVec[i].shipLength << " "
        //<< shipLocationsVec[i].hit << " end " << std::endl;

    }
    //std::cout << "totalHits = " << totalHits << "shipLocationsVec.size() = "
    //  << shipLocationsVec.size() << "\n";
    return ((shipLocationsVec.size() - totalBlanks) == totalHits) ;

}

void BattleShip::Player::printShipLocationVec() const{
    for(int i=0; i<shipLocationsVec.size(); i++) {
        std::cout << shipLocationsVec[i].row << " " << shipLocationsVec[i].col << " "
                  << shipLocationsVec[i].shipSymbol << " " << shipLocationsVec[i].shipLength << " "
                  << shipLocationsVec[i].hit << " end " << std::endl;
    }
}

char BattleShip::Player::getHitOrMiss(const  Move& fireMove) {
    int moveRow = fireMove.getRow();
    int moveCol = fireMove.getCol();

    for(int i=0; i<shipLocationsVec.size(); i++) {
        if (shipLocationsVec[i].row == moveRow && shipLocationsVec[i].col == moveCol
            && shipLocationsVec[i].hit == 0) {
            return shipLocationsVec[i].shipSymbol;
        }
    }

    return '*';
}


char BattleShip::Player::shipDestroyCheck(const  Move& fireMove) {
    int moveRow = fireMove.getRow();
    int moveCol = fireMove.getCol();

    char hitShipSymbol = '*';
    int hitShipLength = 0;
    int hitsOnShip = 0;

    for (int i = 0; i < shipLocationsVec.size(); i++) {
        if (shipLocationsVec[i].row == moveRow && shipLocationsVec[i].col == moveCol
            && shipLocationsVec[i].hit == 0) {
            hitShipSymbol = shipLocationsVec[i].shipSymbol;
            hitShipLength = shipLocationsVec[i].shipLength;
            shipLocationsVec[i].hit = 1;
        }
    }
    if (hitShipSymbol != '*') {
        for (int i = 0; i < shipLocationsVec.size(); i++) {
            if (shipLocationsVec[i].shipSymbol == hitShipSymbol) {
                hitsOnShip = hitsOnShip + shipLocationsVec[i].hit;
            }
        }
    }
    if (hitsOnShip > 0 && (hitsOnShip == hitShipLength)){
        return hitShipSymbol;
    }
    return '*';
}

//////////////////////////////////////////////////////////////////////////////////

BattleShip::HumanPlayer::HumanPlayer(const std::string& name, Board& placementBoard,
                                     Board& firingBoard, std::map<char, Ship>& shipsDetailsMap, char hitPiece, char missPiece,
                                     std::vector<ShipLocation>& shipLocationsVec) :
        Player(name, placementBoard, firingBoard, shipsDetailsMap, hitPiece, missPiece,shipLocationsVec) {
}

//////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////

BattleShip::CheatingAiPlayer::CheatingAiPlayer(const std::string& name, Board& placementBoard,
                                               Board& firingBoard, std::map<char, Ship>& shipsDetailsMap, char hitPiece, char missPiece,
                                               std::vector<ShipLocation>& shipLocationsVec) :
        AiPlayer(name, placementBoard, firingBoard, shipsDetailsMap, hitPiece, missPiece,shipLocationsVec) {
}

//BattleShip::CheatingAiPlayer::CheatingAiPlayer(){}
//////////////////////////////////////////////////////////////////////////////////////

BattleShip::RandomAiPlayer::RandomAiPlayer(const std::string& name, Board& placementBoard,
                                           Board& firingBoard, std::map<char, Ship>& shipsDetailsMap, char hitPiece, char missPiece,
                                           std::vector<ShipLocation>& shipLocationsVec) :
        AiPlayer(name, placementBoard, firingBoard, shipsDetailsMap, hitPiece, missPiece,shipLocationsVec) {

    for (int row = 0; row < firingBoard.getBoardRows(); row++) {
        for (int col = 0; col < firingBoard.getBoardColumns(); col++) {

            BoardRandomMove tmp_struct = BoardRandomMove();
            tmp_struct.row = row;
            tmp_struct.col = col;
            possibleMoves.emplace_back(tmp_struct);
        }
    }

    /*
     for (int col = 0; col < firingBoard.getBoardRows(); col++) {
       for (int row = 0; row < firingBoard.getBoardColumns(); row++) {

         BoardRandomMove tmp_struct = BoardRandomMove();
         tmp_struct.row = row;
         tmp_struct.col = col;
         possibleMoves.emplace_back(tmp_struct);
       }
     }
     */
}



BattleShip::BoardRandomMove BattleShip::RandomAiPlayer::getMove(){
    //Move randomMove(*this);
    //Move randomMove = *chooseRandom(possibleMoves, AiPlayer::randomNumberGenerator);
    BoardRandomMove randomMoveStruct;
    //= BoardRandomMove();

    //randomMoveStruct = getRandInt(0, possibleMoves.size() - 1, BattleShip::AiPlayer::randomNumberGenerator);
    randomMoveStruct = possibleMoves.at(getRandInt(0, possibleMoves.size() - 1, AiPlayer::randomNumberGenerator));
    //randomMoveStruct = possibleMoves.at(rand()%possibleMoves.size());

    for (int i = 0; i < possibleMoves.size() ; i++) {
        if ( possibleMoves[i].row == randomMoveStruct.row && possibleMoves[i].col == randomMoveStruct.col )
            possibleMoves.erase(possibleMoves.begin()+i) ;
    }
    return randomMoveStruct;

}
