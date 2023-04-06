//
//  Created by Tobin Joseph on 2019-06-03.
//

#ifndef BATTLESHIP_AIPLAYER_H
#define BATTLESHIP_AIPLAYER_H
#include <string>
#include "Board.h"
#include "Utility.h"
#include <map>
#include "Player.h"
namespace BattleShip {
//class Move;
    class AiPlayer : public Player {
    public:

        AiPlayer(const std::string &name, Board &placementBoard, Board &firingBoard,
                 std::map<char, Ship> &shipsDetailsMap, char hitPiece, char missPiece,
                 std::vector <ShipLocation> &shipLocationsVec);

        //AiPlayer();
        static void seed_random_number_generator(int seed);

        //virtual void placeShips() override;
        //virtual void initializeName() override;
        static const int getAndIncrementNextAiId();


        static std::mt19937 getRNG();

    public:
        //protected:
        static std::mt19937 randomNumberGenerator;

    private:
        static int nextAiId;
        const int aiId;
    };
}
#endif //BATTLESHIP_AIPLAYER_H
