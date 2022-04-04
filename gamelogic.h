#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "agingCell.h"
#include "gamewindow.h"

#include <string>
#include <vector>

using namespace std;

class GameWindow;

class GameLogic
{
public:
    GameLogic();

    vector<vector<AgingCell>> calculateNextStep(vector<vector<AgingCell>>& currentState, bool aging); // calculating next step based on its current state
    void nextStep(GameWindow *gameWindow, bool aging);
    void createBoard(short AgingCellsInRow);

    vector<vector<AgingCell>> gameState;

    vector<vector<AgingCell>> gameStartingState;

    short cellsInRow;

    short algorithmType;

    void randomizeGameState();

    void reload(GameWindow *gameWindow);
private:
    short columns;
    short rows;
};

#endif // GAMELOGIC_H
