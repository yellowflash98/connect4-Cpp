//
// Created by Tobin Joseph on 2019-06-03.
//

#include "Move.h"
#include <string>
#include "Move.h"
#include "Player.h"
#include "Board.h"

BattleShip::Move::Move( BattleShip::Player& maker) : maker(maker), row(-98), col(-98),
                                                     parsedSuccessfully(false) {

}

BattleShip::Move::Move( const BattleShip::Player& maker) : maker(maker), row(-98), col(-98),
                                                           parsedSuccessfully(false) {

}


BattleShip::Move::Move(const BattleShip::Player& maker, int row, int col) : maker(maker), row(row), col(col),
                                                                            parsedSuccessfully(true) {

}

void BattleShip::Move::parseInput(std::stringstream& input) {

    //std::stringstream& input;
    parsedSuccessfully = static_cast<bool>(input); //input must start out as being good

    input >> row >> col;
    //we must have read both row and col
    parsedSuccessfully = parsedSuccessfully && static_cast<bool>(input);
    std::string leftovers;
    input >> leftovers;
    //and we weren't able to read anything after the row and col
    parsedSuccessfully = parsedSuccessfully && !input;

}

bool BattleShip::Move::isValid(const Board& board) const{

    return parsedSuccessfully && board.inBounds(row,col) && board.isBlankSpace(row,col);
}

const BattleShip::Player& BattleShip::Move::getMaker() const {
    return maker;
}

//void BattleShip::Move::make(BattleShip::Board& board, char hitMissChar) {
//  board.set(row, col, hitMissChar );
//}

int BattleShip::Move::getRow() const {
    return row;
}
int BattleShip::Move::getCol() const {
    return col;
}

void BattleShip::Move::setRowOfMove (int rowVal) {
    row = rowVal;
}

void BattleShip::Move::setColOfMove (int colVal) {
    col = colVal;
}
