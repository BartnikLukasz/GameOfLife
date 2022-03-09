#include "gamelogic.h"
#include "gamewindow.h"
#include "iostream"
#include "random"

#include <vector>

using namespace std;

extern GameWindow * gameWindow;

#define columns 60
#define rows 30

GameLogic::GameLogic()
{
    this->cellsInRow = 60; //TODO zmienić na wartość ustawialną
}

vector<vector<bool>> GameLogic::calculateNextStep(vector<vector<bool>> & currentState)
{
    vector<vector<bool>> nextState(columns, vector<bool>(rows, false)); //creating matrix representing state of the game


    for(int i = 0; i < nextState.size(); i++) {

        for(int j = 0; j < nextState[i].size(); j++) {

            short numberOfAliveNeighbors = 0;

            if(i == 0 && j == 0) {
                numberOfAliveNeighbors += currentState[0][1] + currentState[1][0] + currentState[1][1]; //top left corner
            }
            else if(i == 0 && j == rows-1) {
                numberOfAliveNeighbors += currentState[0][j-1] + currentState[1][j-1] + currentState[1][j]; //bottom left corner
            }
            else if(i == columns-1 && j == 0) {
                numberOfAliveNeighbors += currentState[i-1][0] + currentState[i-1][1] + currentState[i][1]; //top right corner
            }
            else if(i == columns-1 && j == rows-1) {
                numberOfAliveNeighbors += currentState[i-1][j] + currentState[i-1][j-1] + currentState[i][j-1]; // bottom right corner
            }
            else if(i == 0) {
                numberOfAliveNeighbors += currentState[0][j-1] + currentState[1][j-1] + currentState[1][j] + currentState[1][j+1] + currentState[0][j+1]; // left border
            }
            else if(j == 0) {
                numberOfAliveNeighbors += currentState[i-1][0] + currentState[i-1][1] + currentState[i][1] + currentState[i+1][1] + currentState[i+1][0]; // top border
            }
            else if(i == columns-1) {
                numberOfAliveNeighbors += currentState[i][j-1] + currentState[i-1][j-1] + currentState[i-1][j] + currentState[i-1][j+1] + currentState[i][j+1]; // right border
            }
            else if(j == rows-1) {
                numberOfAliveNeighbors += currentState[i-1][j] + currentState[i-1][j-1] + currentState[i][j-1] + currentState[i+1][j-1] + currentState[i+1][j]; //bottom border
            }
            else {
                numberOfAliveNeighbors += currentState[i-1][j-1] + currentState[i][j-1] + currentState[i+1][j-1] + currentState[i+1][j] +
                        currentState[i+1][j+1] + currentState[i][j+1] + currentState[i-1][j+1] + currentState[i-1][j]; // middle
            }

            if(currentState[i][j]) {
                switch (numberOfAliveNeighbors) {
                    case 2:
                    case 3:
                        nextState[i][j] = true;
                        break;
                    default:
                        nextState[i][j] = false;
                        break;
                }
            }
            else {
                switch (numberOfAliveNeighbors) {
                    case 3:
                        nextState[i][j] = true;
                        break;
                    default:
                        nextState[i][j] = false;
                        break;
                }
            }

        }
    }

    return nextState;
}

void GameLogic::nextStep()
{
    this->gameState = calculateNextStep(this->gameState);
    gameWindow->updateUI();
}

void GameLogic::createBoard(short cellsInRow) {
    this->gameState = vector<vector<bool>>(columns, vector<bool>(rows, false));
    this->cellsInRow = cellsInRow;
}

void GameLogic::randomizeGameState() {
    random_device random;
    for(int i = 0; i < this->gameState.size(); i++) {
        for(int j = 0; j < this->gameState[i].size(); j++) {

            mt19937 rng(random());

            this->gameState[i][j] = (uniform_int_distribution<int>(0, 9)(rng) >6);
        }
    }
}
