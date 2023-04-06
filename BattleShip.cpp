#include "BattleShip.h"
#include "Player.h"
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <cctype>
#include "Board.h"
#include "Move.h"
#include <iterator>
#include <algorithm>
#include "Utility.h"
#include <iostream>
#include <stdexcept>
#include <random>
#include <typeinfo>
//#include "AiPlayer.h"

BattleShip::BattleShip::BattleShip(std::string configFileName, std::string seedForRNG) :
        playerTurn(-1) {
    loadGameConfigFile(configFileName, seedForRNG);
    getTypeOfGame();
    addPlayer1ToGame();
    addPlayer2ToGame();
}

void BattleShip::BattleShip::loadGameConfigFile(std::string configFileName, std::string seedForRNG) {
    std::string tempLineReadStr;
    int numberOfRows, numberOfColumns, numberOfShips;
    std::map<char, int> shipsMap;
    std::ifstream myFile(configFileName);
    if (!myFile) {
        exit(1);
    }
    getline(myFile, tempLineReadStr);
    numberOfRows = stoi(tempLineReadStr);
    getline(myFile, tempLineReadStr);
    numberOfColumns = stoi(tempLineReadStr);
    getline(myFile, tempLineReadStr);
    numberOfShips = stoi(tempLineReadStr);
    std::string part1Str, part2Str;
    while (!myFile.eof()) {
        std::getline(myFile, tempLineReadStr);
        std::istringstream iss(tempLineReadStr);
        if (iss)
            iss >> part1Str;
        if (iss)
            iss >> part2Str;
        shipsMap.insert(std::pair<char, int>(part1Str.at(0), stoi(part2Str)));
    }
    myFile.close();
    gameAttrStruct.gameRows = numberOfRows;
    gameAttrStruct.gameColumns = numberOfColumns;
    gameAttrStruct.shipsCount = numberOfShips;
    gameAttrStruct.shipsInfoMap = shipsMap;
    gameAttrStruct.seedForRNG = seedForRNG;
}

bool BattleShip::BattleShip::validateName (std::string name) {
    for (int i = 0; i < name.length (); i++) {
        if (isspace (name.at (i))) {
            return false;
        }
    }
    return true;
}

void BattleShip::BattleShip::play() {

    determineStartingPlayer();

    //std::cout << typeid(abcObject).name() << std::endl;

    if (gameAttrStruct.gameType == 3) {

        while (true) {
            //std::cout << "1 "; getCurrentPlayer().printShipLocationVec() ;
            //std::cout << "1 "; getOtherPlayer().printShipLocationVec() ;

            std::cout << (*players.at(playerTurn)).getName() << "'s Firing Board";
            (*players.at(playerTurn)).getFiringBoard().display();

            std::cout << (*players.at(playerTurn)).getName() << "'s Placement Board";
            (*players.at(playerTurn)).getPlacementBoard().display();

            //get move from current player
            Move move = getValidMoveAIvsAI();
            //std::cout << move.getRow() << "- " << move.getCol() << "-" << getCurrentPlayer().getName()<< "\n";
            //int zz;
            //std::cin >> zz;
            Move fireMove(getOtherPlayer(), move.getRow(), move.getCol());

            //std::cout << "hit/miss -> " << getOtherPlayer().getHitOrMiss(fireMove) << std::endl;

            char hitMiss = getOtherPlayer().getHitOrMiss(fireMove);
            char hitMiss_v2;
            if (hitMiss == '*')
                hitMiss_v2 = (*players.at(playerTurn)).getMissPiece();
            else
                hitMiss_v2 = (*players.at(playerTurn)).getHitPiece();

            //make move on firing board
            (*players.at(playerTurn)).setFiring(move.getRow(), move.getCol(), hitMiss_v2);
            (*players.at(otherPlayer)).setPlacement(move.getRow(), move.getCol(), hitMiss_v2);
            //move.make( (*players.at(playerTurn)).getFiringBoard(), hitMiss);

            std::cout << (*players.at(playerTurn)).getName() << "'s Firing Board";
            (*players.at(playerTurn)).getFiringBoard().display();

            std::cout << (*players.at(playerTurn)).getName() << "'s Placement Board";
            (*players.at(playerTurn)).getPlacementBoard().display();

            if (hitMiss != '*') {
                std::cout << (*players.at(playerTurn)).getName() << " hit "
                          << getOtherPlayer().getName() << "'s " << hitMiss << "!\n";
            }
            else std::cout << "Missed." << std::endl;
            char destroyShipChar = getOtherPlayer().shipDestroyCheck(fireMove);

            if (destroyShipChar != '*') {
                std::cout << (*players.at(playerTurn)).getName() << " destroyed "
                          << getOtherPlayer().getName() << "'s " << hitMiss << "!\n";
            }

            if (isGameOver()) {
                std::cout << (*players.at(playerTurn)).getName() << " won the game!\n";
                break;
            }
            changeTurn();
        }
    } //Game Type == 3




    if (gameAttrStruct.gameType == 1) {

        while (true) {
            //std::cout << "1 "; getCurrentPlayer().printShipLocationVec() ;
            //std::cout << "1 "; getOtherPlayer().printShipLocationVec() ;

            std::cout << (*players.at(playerTurn)).getName() << "'s Firing Board";
            (*players.at(playerTurn)).getFiringBoard().display();

            std::cout << (*players.at(playerTurn)).getName() << "'s Placement Board";
            (*players.at(playerTurn)).getPlacementBoard().display();

            //get move from current player
            Move move = getValidMove();

            Move fireMove(getOtherPlayer(), move.getRow(), move.getCol());

            //std::cout << "hit/miss -> " << getOtherPlayer().getHitOrMiss(fireMove) << std::endl;

            char hitMiss = getOtherPlayer().getHitOrMiss(fireMove);
            char hitMiss_v2;
            if (hitMiss == '*')
                hitMiss_v2 = (*players.at(playerTurn)).getMissPiece();
            else
                hitMiss_v2 = (*players.at(playerTurn)).getHitPiece();

            //make move on firing board
            (*players.at(playerTurn)).setFiring(move.getRow(), move.getCol(), hitMiss_v2);
            (*players.at(otherPlayer)).setPlacement(move.getRow(), move.getCol(), hitMiss_v2);
            //move.make( (*players.at(playerTurn)).getFiringBoard(), hitMiss);

            std::cout << (*players.at(playerTurn)).getName() << "'s Firing Board";
            (*players.at(playerTurn)).getFiringBoard().display();

            std::cout << (*players.at(playerTurn)).getName() << "'s Placement Board";
            (*players.at(playerTurn)).getPlacementBoard().display();

            if (hitMiss != '*') {
                std::cout << (*players.at(playerTurn)).getName() << " hit "
                          << getOtherPlayer().getName() << "'s " << hitMiss << "!\n";
            }
            else std::cout << "Missed." << std::endl;
            char destroyShipChar = getOtherPlayer().shipDestroyCheck(fireMove);

            if (destroyShipChar != '*') {
                std::cout << (*players.at(playerTurn)).getName() << " destroyed "
                          << getOtherPlayer().getName() << "'s " << hitMiss << "!\n";
            }

            if (isGameOver()) {
                std::cout << (*players.at(playerTurn)).getName() << " won the game!\n";
                break;
            }
            changeTurn();
        }
    } //Game Type == 1



}

BattleShip::Move BattleShip::BattleShip::getValidMoveAIvsAI()  {
    Move playerMove(getCurrentPlayer());

    std::string playerClassName = typeid( getCurrentPlayer() ).name();

    if (playerClassName.find("CheatingAiPlayer") > 0){
        playerMove.setRowOfMove (getOtherPlayer().getRowOfCheatMove());
        playerMove.setColOfMove (getOtherPlayer().getColOfCheatMove());
    }

    if (playerClassName.find("RandomAiPlayer") > 0){

        BoardRandomMove randomMoveStruct; // = BoardRandomMove();
        randomMoveStruct = getCurrentPlayerModify().getMove();

        playerMove.setRowOfMove (randomMoveStruct.row);
        playerMove.setColOfMove (randomMoveStruct.col);
    }

    return playerMove;
}



bool BattleShip::BattleShip::isGameOver() const {
    return getOtherPlayer().getPlayerHealth();
}

BattleShip::Move BattleShip::BattleShip::getValidMove() const {
    Move playerMove(getCurrentPlayer());
    do {
        std::cout << (*players.at(playerTurn)).getName() << ", where would you like to fire?" << std::endl;
        std::cout << "Enter your attack coordinate in the form row col: ";
        std::string line;
        std::getline(std::cin, line);
        std::stringstream userIn(line);
        playerMove.parseInput(userIn);
    } while (!playerMove.isValid(getCurrentPlayer().getFiringBoard()));
    return playerMove;
}

void BattleShip::BattleShip::changeTurn() {
    playerTurn = (playerTurn + 1) % players.size();
    otherPlayer = (playerTurn + 1) % players.size();
}

void BattleShip::BattleShip::getTypeOfGame(){
    int gameType;
    std::cout << "What type of game do you want to play?" << std::endl;
    std::cout << "1. Human vs Human" << std::endl;
    std::cout << "2. Human vs AI" << std::endl;
    std::cout << "3. AI vs AI" << std::endl;
    std::cout << "Your choice: ";
    std::cin >> gameType;
    std::cin.ignore();
    gameAttrStruct.gameType = gameType;

    std::string leftovers;
    std::getline(std::cin, leftovers);
}

int BattleShip::BattleShip::getAiType(){
    int aiType;
    std::cout << "What AI do you want?" << std::endl;
    std::cout << "1. Cheating AI" << std::endl;
    std::cout << "2. Random AI" << std::endl;
    std::cout << "3. Hunt Destroy AI" << std::endl;
    std::cout << "Your choice: ";
    std::cin >> aiType;
    std::cin.ignore();

    //gameAttrStruct.gameType = gameType;
    std::string leftovers;
    std::getline(std::cin, leftovers);
    return aiType;
}

void BattleShip::BattleShip::addPlayer1ToGame(){
    int aiType = -1;
    if (gameAttrStruct.gameType == 1 or gameAttrStruct.gameType == 2) {
        std::cout << "Player 1 please enter your name: ";
        addHumanPlayer();
    }
    //First player is an AI..
    if (gameAttrStruct.gameType == 3) {
        std::cout << "Player 1 please enter your name: ";
        aiType = getAiType();
        addAiPlayer(aiType);
    }
}

void BattleShip::BattleShip::addAiPlayer(int aiType){
    if (aiType == 1)
        addCheatingAI();
    else if (aiType == 2)
        addRandomAI();
    else
        addHuntDestroyAI();
}

void BattleShip::BattleShip::addPlayer2ToGame(){
    int aiType = -1;
    if (gameAttrStruct.gameType == 1) {
        std::cout << "Player 2 please enter your name: ";
        addHumanPlayer();
    }

    if (gameAttrStruct.gameType == 3 || gameAttrStruct.gameType == 2 ) {
        //std::cout << "Player 1 please enter your name: ";
        aiType = getAiType();
        addAiPlayer(aiType);
    }
}

void BattleShip::BattleShip::addCheatingAI(){

    std::string playerName = "AI " + std::to_string(AiPlayer::getAndIncrementNextAiId()-1);
    char shipSymbol;
    int shipLength;
    char shipOrientation;

    Board shipPlacementBoard (gameAttrStruct.gameRows, gameAttrStruct.gameColumns, '*', -98, -99);
    Board firingBoard (gameAttrStruct.gameRows, gameAttrStruct.gameColumns, '*', -98, -99);

    std::map<char, Ship> shipsDetailsMap;
    std::vector<ShipLocation> shipLocationsVec;

    std::map<char, int>::iterator itr;

    std::vector<char> orientation_choice{'h', 'v'};
    const int numRows = gameAttrStruct.gameRows;
    const int numCols = gameAttrStruct.gameColumns;
    ShipLocation tmp_struct = ShipLocation();

    //???
    //srand(time(nullptr));

    for (itr = gameAttrStruct.shipsInfoMap.begin(); itr != gameAttrStruct.shipsInfoMap.end(); ++itr) {
        shipSymbol = itr->first;
        shipLength = itr->second;
        tmp_struct.shipSymbol = shipSymbol;
        tmp_struct.shipLength = shipLength;

        shipOrientation = *chooseRandom(orientation_choice, AiPlayer::randomNumberGenerator);
        //shipOrientation = selectRandom(orientation_choice);

        //???
        //shipOrientation = orientation_choice[rand()%1];
        //shipOrientation = 'v';

        tmp_struct.shipOrientation = shipOrientation;

        do{
            if (shipOrientation == 'h') {

                tmp_struct.row = getRandInt(0, numRows - 1, AiPlayer::randomNumberGenerator);
                tmp_struct.col = getRandInt(0, numCols - shipLength, AiPlayer::randomNumberGenerator);

                //???
                //tmp_struct.row = rand()%6;
                //tmp_struct.col = rand()%(6-shipLength);

            } else {

                tmp_struct.row = getRandInt(0, numRows - shipLength, AiPlayer::randomNumberGenerator);
                tmp_struct.col = getRandInt(0, numCols - 1, AiPlayer::randomNumberGenerator);

                //???
                //tmp_struct.row = rand()%(6-shipLength);
                //tmp_struct.col = rand()%(6);

            }
            /* std::cout  << tmp_struct.row << "- " << tmp_struct.col<< "Length =" << tmp_struct.shipLength << " - "  << tmp_struct.shipOrientation
              << "-" <<  tmp_struct.shipSymbol <<
               "\n";
              bool check = !shipPlacementBoard.canPlaceShipAt(tmp_struct);
              std::cout << "check = " << check << "\n";
              int kk;
            std::cin >> kk;
            */
        } while( !shipPlacementBoard.canPlaceShipAt(tmp_struct));

        shipPlacementBoard.placeShip(shipSymbol, shipOrientation,shipLength,
                                     tmp_struct.row, tmp_struct.col);
        std::cout << playerName << "'s Board" << std::endl;
        shipPlacementBoard.display();

        //Building shiplocatons vector

        if (shipOrientation == 'h') {
            for (int m=0 ; m<shipLength;  m++) {
                ShipLocation tmp2_struct = ShipLocation();
                tmp2_struct.row = tmp_struct.row;
                tmp2_struct.col = tmp_struct.col + m;
                tmp2_struct.shipSymbol = tmp_struct.shipSymbol;
                tmp2_struct.shipLength = tmp_struct.shipLength;
                tmp2_struct.hit = 0;
                shipLocationsVec.push_back(tmp2_struct);

            }
        }
        if (shipOrientation == 'v') {
            for (int n=0 ; n<shipLength;  n++) {

                ShipLocation tmp2_struct = ShipLocation();
                tmp2_struct.row = tmp_struct.row +n;
                tmp2_struct.col = tmp_struct.col;
                tmp2_struct.shipSymbol = tmp_struct.shipSymbol;
                tmp2_struct.shipLength = tmp_struct.shipLength;
                tmp2_struct.hit = 0;
                shipLocationsVec.push_back(tmp2_struct);
            }
        }

        Ship tmpShip(tmp_struct.shipSymbol, tmp_struct.shipOrientation,tmp_struct.shipLength,
                     tmp_struct.row, tmp_struct.col);
        shipsDetailsMap.insert(std::pair<char, Ship>(shipSymbol, tmpShip));

    }

    players.emplace_back(std::make_unique<CheatingAiPlayer>(playerName, shipPlacementBoard,
                                                            firingBoard, shipsDetailsMap, 'X', 'O', shipLocationsVec));
    shipLocationsVec.clear();

}


void BattleShip::BattleShip::addRandomAI(){

    std::string playerName = "AI " + std::to_string(AiPlayer::getAndIncrementNextAiId()-1);
    char shipSymbol;
    int shipLength;
    char shipOrientation;

    Board shipPlacementBoard (gameAttrStruct.gameRows, gameAttrStruct.gameColumns, '*', -98, -99);
    Board firingBoard (gameAttrStruct.gameRows, gameAttrStruct.gameColumns, '*', -98, -99);

    std::map<char, Ship> shipsDetailsMap;
    std::vector<ShipLocation> shipLocationsVec;

    std::map<char, int>::iterator itr;

    std::vector<char> orientation_choice{'h', 'v'};
    const int numRows = gameAttrStruct.gameRows;
    const int numCols = gameAttrStruct.gameColumns;
    ShipLocation tmp_struct = ShipLocation();

    //??????
    //srand(time(nullptr));

    for (itr = gameAttrStruct.shipsInfoMap.begin(); itr != gameAttrStruct.shipsInfoMap.end(); ++itr) {
        shipSymbol = itr->first;
        shipLength = itr->second;
        tmp_struct.shipSymbol = shipSymbol;
        tmp_struct.shipLength = shipLength;

        shipOrientation = *chooseRandom(orientation_choice, AiPlayer::randomNumberGenerator);
        //shipOrientation = selectRandom(orientation_choice);

        //???
        //shipOrientation = orientation_choice[rand()%1];
        //shipOrientation = 'v';

        tmp_struct.shipOrientation = shipOrientation;

        do{
            if (shipOrientation == 'h') {
                tmp_struct.row = getRandInt(0, numRows - 1, AiPlayer::randomNumberGenerator);
                tmp_struct.col = getRandInt(0, numCols - shipLength, AiPlayer::randomNumberGenerator);

                //???
                //tmp_struct.row = rand()%6;
                //tmp_struct.col = rand()%(6-shipLength);

            } else {
                tmp_struct.row = getRandInt(0, numRows - shipLength, AiPlayer::randomNumberGenerator);
                tmp_struct.col = getRandInt(0, numCols - 1, AiPlayer::randomNumberGenerator);

                //???
                //tmp_struct.row = rand()%(6-shipLength);
                //tmp_struct.col = rand()%(6);

            }
            /* std::cout  << tmp_struct.row << "- " << tmp_struct.col<< "Length =" << tmp_struct.shipLength << " - "  << tmp_struct.shipOrientation
              << "-" <<  tmp_struct.shipSymbol <<
               "\n";
              bool check = !shipPlacementBoard.canPlaceShipAt(tmp_struct);
              std::cout << "check = " << check << "\n";
              int kk;
            std::cin >> kk;
            */
        } while( !shipPlacementBoard.canPlaceShipAt(tmp_struct));
        //std::cout << "reached here 272 " ;

        shipPlacementBoard.placeShip(shipSymbol, shipOrientation,shipLength,
                                     tmp_struct.row, tmp_struct.col);
        std::cout << playerName << "'s Board" << std::endl;
        shipPlacementBoard.display();

        //Building shiplocatons vector

        if (shipOrientation == 'h') {
            for (int m=0 ; m<shipLength;  m++) {
                ShipLocation tmp2_struct = ShipLocation();
                tmp2_struct.row = tmp_struct.row;
                tmp2_struct.col = tmp_struct.col + m;
                tmp2_struct.shipSymbol = tmp_struct.shipSymbol;
                tmp2_struct.shipLength = tmp_struct.shipLength;
                tmp2_struct.hit = 0;
                shipLocationsVec.push_back(tmp2_struct);

            }
        }
        if (shipOrientation == 'v') {
            for (int n=0 ; n<shipLength;  n++) {

                ShipLocation tmp2_struct = ShipLocation();
                tmp2_struct.row = tmp_struct.row +n;
                tmp2_struct.col = tmp_struct.col;
                tmp2_struct.shipSymbol = tmp_struct.shipSymbol;
                tmp2_struct.shipLength = tmp_struct.shipLength;
                tmp2_struct.hit = 0;
                shipLocationsVec.push_back(tmp2_struct);
            }
        }

        Ship tmpShip(tmp_struct.shipSymbol, tmp_struct.shipOrientation,tmp_struct.shipLength,
                     tmp_struct.row, tmp_struct.col);
        shipsDetailsMap.insert(std::pair<char, Ship>(shipSymbol, tmpShip));

    }

    players.emplace_back(std::make_unique<RandomAiPlayer>(playerName, shipPlacementBoard,
                                                          firingBoard, shipsDetailsMap, 'X', 'O', shipLocationsVec));
    shipLocationsVec.clear();


}
void BattleShip::BattleShip::addHuntDestroyAI(){
    std::cout<<"addHuntDestroyAI\n";
}

void BattleShip::BattleShip::addHumanPlayer(){
    std::string playerName;
    char shipSymbol;
    int shipLength;
    char shipshipOrientation;
    std::string shipOrientationString;
    int placementRow, placementColumn;
    std::cin >> playerName;
    std::cin.ignore();
    Board shipPlacementBoard (gameAttrStruct.gameRows, gameAttrStruct.gameColumns, '*', -98, -99);
    Board firingBoard (gameAttrStruct.gameRows, gameAttrStruct.gameColumns, '*', -98, -99);

    shipPlacementBoard.display();
    std::map<char, Ship> shipsDetailsMap;
    std::vector<ShipLocation> shipLocationsVec;

    std::map<char, int>::iterator itr;
    std::string leftovers;

    for (itr = gameAttrStruct.shipsInfoMap.begin(); itr != gameAttrStruct.shipsInfoMap.end(); ++itr) {
        shipSymbol = itr->first;
        shipLength = itr->second;

        std::cout << playerName << ", do you want to place "<< shipSymbol <<" horizontally or vertically?" << std::endl;
        std::cout << "Enter h for horizontal or v for vertical" << std::endl;
        std::cout << "Your choice: ";
        std::cin >> shipOrientationString;
        std::cin.ignore();
        shipshipOrientation = tolower(shipOrientationString.at(0));

        std::cout << playerName << ", enter the row and column you want to place " << shipSymbol << ", which is "<< shipLength <<" long, at with a space in between row and col: ";
        std::cin >> placementRow >> placementColumn;
        std::cin.ignore();
        std::getline(std::cin, leftovers);
        //std::cout << "shipSymbol = " << shipSymbol << "  shipshipOrientation = " << shipshipOrientation << std::endl;
        //std::cout << "shipLength = " << shipLength << "  placementRow = " << placementRow << std::endl;
        //std::cout << "placementColumn = " << placementColumn  << std::endl;
        shipPlacementBoard.placeShip(shipSymbol, shipshipOrientation,shipLength,
                                     placementRow, placementColumn);
        shipPlacementBoard.display();
        //Building shiplocatons vector
        if (shipshipOrientation == 'h') {
            for (int m=0 ; m<shipLength;  m++) {
                ShipLocation tmp_struct = ShipLocation();
                tmp_struct.row = placementRow;
                tmp_struct.col = placementColumn + m;
                tmp_struct.shipSymbol = shipSymbol;
                tmp_struct.shipLength = shipLength;
                tmp_struct.hit = 0;
                shipLocationsVec.push_back(tmp_struct);

            }
        }
        if (shipshipOrientation == 'v') {
            for (int n=0 ; n<shipLength;  n++) {

                ShipLocation tmp_struct = ShipLocation();
                tmp_struct.row = placementRow +n;
                tmp_struct.col = placementColumn;
                tmp_struct.shipSymbol = shipSymbol;
                tmp_struct.shipLength = shipLength;
                tmp_struct.hit = 0;
                shipLocationsVec.push_back(tmp_struct);
            }
        }
        Ship tmpShip(shipSymbol, shipshipOrientation,shipLength, placementRow, placementColumn);
        shipsDetailsMap.insert(std::pair<char, Ship>(shipSymbol, tmpShip));
    }
    //shipPlacementBoard.display();
    players.emplace_back(std::make_unique<HumanPlayer>(playerName, shipPlacementBoard,
                                                       firingBoard, shipsDetailsMap, 'X', 'O', shipLocationsVec)); //Here now??
    shipLocationsVec.clear();
}


void BattleShip::BattleShip::determineStartingPlayer () {
    playerTurn = 0;
    otherPlayer = 1;
}

BattleShip::Player& BattleShip::BattleShip::getCurrentPlayerModify()  {
    return *players.at(playerTurn);
}

const BattleShip::Player& BattleShip::BattleShip::getCurrentPlayer() const {
    return *players.at(playerTurn);
}



const BattleShip::Player& BattleShip::BattleShip::getOtherPlayer() const {
    return *players.at(otherPlayer);
}

BattleShip::Player& BattleShip::BattleShip::getOtherPlayer()  {
    return *players.at(otherPlayer);
}

//std::vector<char> orientation_choice{'h', 'v'};
char BattleShip::BattleShip::selectRandom(const std::vector<char>& values) {
    auto itr = values.cbegin();
    auto max_choice = std::distance(values.cbegin(), values.cend()) - 1;
    std::uniform_int_distribution<unsigned int> dis(0, max_choice);
    auto move_amount = dis(AiPlayer::randomNumberGenerator);
    std::advance(itr, move_amount);
    return  *itr;
}
