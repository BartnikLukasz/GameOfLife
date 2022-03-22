#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "agingcell.h"

#include <vector>

using namespace std;

class GameLogic
{
public:
    GameLogic();

    vector<vector<AgingCell>> calculateNextStep(vector<vector<AgingCell>>& currentState); // calculating next step based on its current state
    void nextStep();
    void createBoard(short cellsInRow);

    vector<vector<AgingCell>> gameState;

    vector<vector<AgingCell>> gameStartingState;

    short cellsInRow;

    void randomizeGameState();

    void reload();
private:
    short columns;
    short rows;
};

#endif // GAMELOGIC_H
