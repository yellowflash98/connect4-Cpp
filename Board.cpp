//
// Created by Tobin Joseph on 2019-06-03.
//

#include "Board.h"
#include <iostream>
#include "Board.h"
#include <algorithm>
#include <iterator>
#include "Utility.h"

BattleShip::Board::Board(int rows,int columns, char blankChar, int movrow, int movcol) :
        boardState(rows,std::vector<char>(columns,blankChar)),
        blankChar(blankChar), boardRows(rows) , boardColumns(columns),
        moveRow(movrow), moveCol(movcol){

}

BattleShip::Board::Board(const Board& boardChar):
        blankChar(boardChar.blankChar),
        boardRows(boardChar.boardRows),
        boardColumns(boardChar.boardColumns),
        moveRow(boardChar.moveRow),
        moveCol(boardChar.moveCol){

    for( int i=0;i<boardChar.boardRows ; i++) {
        std::vector<char>temp;
        for( int j=0; j<boardChar.boardColumns ;j++) {
            temp.push_back (boardChar.boardState.at(i).at(j));
            //std::cout<< "Printing each values: boardChar.boardState.at(" << i << ").at(" << j << ") -> " << boardChar.boardState.at(i).at(j) << std::endl;
        }
        this->boardState.push_back(temp);
    }
}

const char& BattleShip::Board::at(int row, int col) const {
    return boardState.at(row).at(col);
}

int BattleShip::Board::getBoardRows() const {
    return boardRows;
}
int BattleShip::Board::getBoardColumns() const {
    return boardColumns;
}

bool BattleShip::Board::canPlaceShipAt(struct ShipLocation tmp_struct){

    // std::cout << "reached here 44 board.cpp " << tmp_struct.shipLength << " - "  << tmp_struct.shipOrientation
    //           << "-" << tmp_struct.row << "- " << tmp_struct.col <<
    //           "\n";


    if (tmp_struct.shipOrientation == 'h') {
        for (int m=0 ; m<tmp_struct.shipLength;  m++) {
            //std::cout << "at - " << at(tmp_struct.row, tmp_struct.col+ m) << "\n";
            if (!(isBlankSpace(tmp_struct.row, tmp_struct.col+ m)))
                return false;
        }
    }
    if (tmp_struct.shipOrientation == 'v') {
        for (int n=0 ; n<tmp_struct.shipLength;  n++) {
            //std::cout << "at - " << at(tmp_struct.row, tmp_struct.col+ n) << "\n";
            if (!isBlankSpace(tmp_struct.row+n, tmp_struct.col))
                return false;
        }
    }
    return true;
}

void BattleShip::Board::display() const {

    //print column headers
    std::cout << "  ";
    for (int j = 0; j < getBoardColumns(); j++) {
        std::cout << j << ' ';
    }
    std::cout << std::endl;

    //int rowIndex = getBoardRows()-1;


    //for (int i= getBoardRows()-1; i>=0 ; i--){
    for (int i= 0; i<getBoardRows() ; i++){
        //std::cout << rowIndex << ' ';
        std::cout << i << ' ';
        for (int j= 0; j<= getBoardColumns()-1 ; j++ ){
            std::cout << boardState[i][j] << ' ';
        }
        //rowIndex++;
        std::cout << std::endl;

    }

}

bool BattleShip::Board::inBounds(int row, int col) const {
    return isBetween(row, 0, getBoardRows() - 1) &&
           isBetween(col, 0, getBoardColumns()- 1);
}

bool BattleShip::Board::isBetween(int val, int lower, int upper) {
    return val >= lower && val <= upper;
}

bool BattleShip::Board::isBlankSpace(int row, int col) const {
    return boardState.at(row).at(col) == blankChar;
}


void BattleShip::Board::placeShip(char shipSymbol, char shipOrientation, int shipLength,
                                  int placementRow, int placementColumn) {
    int moveRow, moveCol;

    if (shipOrientation == 'h') {
        for (int i=0 ; i<shipLength;  i++) {
            moveRow = placementRow;
            moveCol = placementColumn + i;
            boardState.at(moveRow).at(moveCol) = shipSymbol;
        }

    }

    if (shipOrientation == 'v') {
        for (int i=0 ; i<shipLength;  i++) {
            moveRow = placementRow +i;
            moveCol = placementColumn;
            boardState.at(moveRow).at(moveCol) = shipSymbol;
        }
        //std::cout << "reached addship 119 Board.cpp \n";

    }

}

void BattleShip::Board::set(int row, int col, char val) {

    boardState.at(row).at(col) = val;
}



