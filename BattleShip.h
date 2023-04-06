//
// Created by Tobin Joseph on 2019-06-03.
//

#ifndef BATTLESHIP_2_BATTLESHIP_H
#define BATTLESHIP_2_BATTLESHIP_H
#include <vector>
#include <memory>
#include "Player.h"
#include <string>

namespace BattleShip {

//class Player;
//class Move; //forward declaration

    class BattleShip {
    public:

        explicit BattleShip(std::string configFileName, std::string seedForRNG);
        virtual ~BattleShip() = default;
        void play();
        void loadGameConfigFile(std::string configFileName, std::string seedForRNG);

        void getTypeOfGame();
        int getAiType();
        void addAiPlayer(int aiType);
        void addPlayer1ToGame();
        void addPlayer2ToGame();
        void addHumanPlayer();

        void addCheatingAI();
        void addRandomAI();
        void addHuntDestroyAI();

        bool validateName (std::string name);
        char selectRandom(const std::vector<char>& values);
        Move getValidMoveAIvsAI() ;


    private:
        void determineStartingPlayer();
        const Player& getCurrentPlayer() const;
        Player& getCurrentPlayerModify();
        const Player& getOtherPlayer() const;
        Player& getOtherPlayer();
        Move getValidMove() const;
        bool isGameOver() const;
        void changeTurn();

    public:
        struct GameAttributes gameAttrStruct;
    private:
        std::vector<std::unique_ptr<Player>> players;
        int playerTurn;
        int otherPlayer;
    };
}
#endif //BATTLESHIP_2_BATTLESHIP_H
