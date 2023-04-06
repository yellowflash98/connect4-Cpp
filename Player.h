//
// Created by Tobin Joseph on 2019-06-03.
//



#ifndef BATTLESHIP_2_PLAYER_H
#define BATTLESHIP_2_PLAYER_H

#include <string>
#include "Board.h"
#include "Utility.h"
#include <map>
//#include "AiPlayer.h"
namespace BattleShip {

    struct BoardRandomMove
    {
        int row;
        int col;

    };

    class Ship {

    private:
        char shipSymbol;
        int shipLength;
        char shipOrientation;
        int placementRow;
        int placementColumn;

/*
unsigned color; // color code: 0=BLACK, 1=BLUE
string status; // status[i]: upper case = good; lower case = damaged
*/
    public:
        Ship(char shipSymbol, int shipLength, char shipOrientation, int placementRow, int placementColumn);
    };


///////////////////////////////////////////////////////////

    class Move;
    class Player {
    public:
        Player(const std::string& name,  Board& placementBoard,  Board& firingBoard,
               std::map<char,Ship>& shipsDetailsMap, char hitPiece, char missPiece,
               std::vector<ShipLocation>& shipLocationsVec);
/*
  players.emplace_back(std::make_unique<HumanPlayer>
      (playerName, shipPlacementBoard,firingBoard, shipsDetailsMap,
          'X', 'O', shipLocationsVec)); //Here now??
*/


        Player() ;
        virtual ~Player();

        const std::string& getName() const;
        char getHitPiece()  const;
        char getMissPiece() const;

        const Board& getFiringBoard() const;
        const Board& getPlacementBoard() const;

        int getRowOfCheatMove()const;
        int getColOfCheatMove()const;


        virtual BoardRandomMove getMove()  ;

        void setPlacement(int row, int col, char val);
        void setFiring(int row, int col, char val);
        bool getPlayerHealth() const;
        char shipDestroyCheck(const  Move& fireMove);
        char getHitOrMiss(const  Move& fireMove);
        void printShipLocationVec() const;

        const  std::vector<ShipLocation>& getshipLocationsVec() const;

    protected:
        std::string name;
        char hitPiece;
        char missPiece;

        Board placementBoard, firingBoard; //1
        std::map<char, Ship> shipsDetailsMap ;
        std::vector<ShipLocation> shipLocationsVec;
    };

////////////////////////////////////////////////////

    class HumanPlayer : public Player {
    public:
        HumanPlayer();
        HumanPlayer(const std::string& name, Board& placementBoard, Board& firingBoard,
                    std::map<char, Ship>& shipsDetailsMap, char hitPiece, char missPiece,
                    std::vector<ShipLocation>& shipLocationsVec);

/*
  players.emplace_back(std::make_unique<HumanPlayer>
      (playerName, shipPlacementBoard,firingBoard, shipsDetailsMap,
          'X', 'O', shipLocationsVec)); //Here now??
*/


    protected:
        //virtual void parseUserInput(Move& playerMove) const;

    };

////////////////////////////////////////////////////////

//class Move;
    class AiPlayer : public Player {
    public:

        AiPlayer(const std::string& name, Board& placementBoard, Board& firingBoard,
                 std::map<char, Ship>& shipsDetailsMap, char hitPiece, char missPiece,
                 std::vector<ShipLocation>& shipLocationsVec);

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

////////////////////////////////////////////////
    class CheatingAiPlayer : public AiPlayer {
    public:

        //CheatingAiPlayer();
        CheatingAiPlayer(const std::string& name, Board& placementBoard, Board& firingBoard,
                         std::map<char, Ship>& shipsDetailsMap, char hitPiece, char missPiece,
                         std::vector<ShipLocation>& shipLocationsVec);

        std::vector<Move> generatePossibleMoves(const Board& board) const;


    };
/////////////////////////////////////////////////////////////////////////////

    class RandomAiPlayer : public AiPlayer {
    public:
        RandomAiPlayer(const std::string& name, Board& placementBoard, Board& firingBoard,
                       std::map<char, Ship>& shipsDetailsMap, char hitPiece, char missPiece,
                       std::vector<ShipLocation>& shipLocationsVec);
        BoardRandomMove getMove() ;

    private:
        std::vector<BoardRandomMove> possibleMoves;

    };

}
#endif //BATTLESHIP_2_PLAYER_H
