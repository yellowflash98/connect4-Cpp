//
// Created by Tobin Joseph on 2019-06-03.
//

#ifndef BATTLESHIP_2_BOARD_H
#define BATTLESHIP_2_BOARD_H
#include <vector>
#include <string>
#include "Utility.h"

namespace BattleShip {
    class Board {
    public:
        /*
            using iterator = std::vector<std::string>::iterator;
            using const_iterator = std::vector<std::string>::const_iterator;
        */

        explicit Board(int rows,int columns, char blankChar, int row, int col);

        //Copy constructor
        explicit Board(const Board& boardChar);

        //int getSize() const;
        int getBoardRows() const;
        int getBoardColumns() const;
        void display() const;

        bool inBounds(int row, int col) const;
        bool isBlankSpace(int row, int col) const;
        void set(int row, int col, char val);
        const char& at(int row, int col) const;

        int getAvailableRow(int col) const;
        bool isColumnFull(int col) const;
        int getMoveRow() const;
        int getMoveCol() const;
        bool canPlaceShipAt(struct ShipLocation tmp_struct);
        void placeShip(char shipSymbol, char shipOrientation,int shipLength, int placementRow, int placementColumn);

/*
        iterator begin();
        iterator end();
        const_iterator cbegin() const;
        const_iterator cend() const;

*/

        const char getBlankChar() const;

        bool full() const;

    private:
        static bool isBetween(int val, int lower, int upper);

    private:
        std::vector<std::vector<char> > boardState;
        const char blankChar;

        int boardRows;
        int boardColumns;
        int moveRow, moveCol;
    };
}
#endif //BATTLESHIP_2_BOARD_H
