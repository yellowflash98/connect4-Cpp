//
// Created by Tobin Joseph on 2019-06-03.
//

#ifndef BATTLESHIP_2_MOVE_H
#define BATTLESHIP_2_MOVE_H
#include <sstream>

namespace BattleShip {
    class Player;
    class Board;

    class Move {
    public:

        Move(const Player& maker);
        Move(Player& maker);

        Move(const Player& maker, int row, int col);
        void parseInput(std::stringstream& input);
        bool isValid(const Board& board) const;
        const Player& getMaker() const;
        int getRow() const;
        int getCol() const;
        void setRowOfMove (int rowVal);
        void setColOfMove (int colVal);


        void make(Board& board,char hitMissChar);

    private:
        const Player& maker;
        int row;
        int col;
        bool parsedSuccessfully;

    };
}

#endif //BATTLESHIP_2_MOVE_H
