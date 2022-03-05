#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <vector>

using namespace std;

class GameLogic
{
public:
    GameLogic();

    vector<vector<bool>> calculateNextStep(vector<vector<bool>>& currentState); // calculating next step based on its current state
    void nextStep();

    vector<vector<bool>> gameState;
    short cellsInRow;

};

#endif // GAMELOGIC_H
