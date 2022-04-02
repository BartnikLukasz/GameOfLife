#include "gamelogic.h"
#include "gamewindow.h"
#include "iostream"
#include "random"
#include "converters.h"

#include <vector>

using namespace std;

GameLogic::GameLogic()
{

}

vector<vector<AgingCell> > GameLogic::calculateNextStep(vector<vector<AgingCell> > &currentState,  bool aging)
{
    vector<vector<AgingCell>> nextState(columns, vector<AgingCell>(rows, AgingCell())); //creating matrix representing state of the game

    for(int i = 0; i < currentState.size(); i++) {

        for(int j = 0; j < currentState[i].size(); j++) {

            if(currentState[i][j].isAlive()) {
                if(aging){
                    currentState[i][j].getOlder();
                }
                else {
                    LivingCell livingCell = cvt::convertAgingCellToLivingCell(currentState[i][j]);
                    livingCell.getOlder();
                    currentState[i][j] = cvt::convertLivingCellToAgingCell(livingCell);
                }
            }

        }

    }


    for(int i = 0; i < nextState.size(); i++) {

        for(int j = 0; j < nextState[i].size(); j++) {

            short numberOfAliveNeighbors = 0;

            if(i == 0 && j == 0) {
                numberOfAliveNeighbors += currentState[0][1].isAlive() + currentState[1][0].isAlive() + currentState[1][1].isAlive(); //top left corner
            }
            else if(i == 0 && j == rows-1) {
                numberOfAliveNeighbors += currentState[0][j-1].isAlive() + currentState[1][j-1].isAlive() + currentState[1][j].isAlive(); //bottom left corner
            }
            else if(i == columns-1 && j == 0) {
                numberOfAliveNeighbors += currentState[i-1][0].isAlive() + currentState[i-1][1].isAlive() + currentState[i][1].isAlive(); //top right corner
            }
            else if(i == columns-1 && j == rows-1) {
                numberOfAliveNeighbors += currentState[i-1][j].isAlive() + currentState[i-1][j-1].isAlive() + currentState[i][j-1].isAlive(); // bottom right corner
            }
            else if(i == 0) {
                numberOfAliveNeighbors += currentState[0][j-1].isAlive() + currentState[1][j-1].isAlive() + currentState[1][j].isAlive() +
                        currentState[1][j+1].isAlive() + currentState[0][j+1].isAlive(); // left border
            }
            else if(j == 0) {
                numberOfAliveNeighbors += currentState[i-1][0].isAlive() + currentState[i-1][1].isAlive() + currentState[i][1].isAlive() +
                        currentState[i+1][1].isAlive() + currentState[i+1][0].isAlive(); // top border
            }
            else if(i == columns-1) {
                numberOfAliveNeighbors += currentState[i][j-1].isAlive() + currentState[i-1][j-1].isAlive() + currentState[i-1][j].isAlive() +
                        currentState[i-1][j+1].isAlive() + currentState[i][j+1].isAlive(); // right border
            }
            else if(j == rows-1) {
                numberOfAliveNeighbors += currentState[i-1][j].isAlive() + currentState[i-1][j-1].isAlive() + currentState[i][j-1].isAlive() +
                        currentState[i+1][j-1].isAlive() + currentState[i+1][j].isAlive(); //bottom border
            }
            else {
                numberOfAliveNeighbors += currentState[i-1][j-1].isAlive() + currentState[i][j-1].isAlive() + currentState[i+1][j-1].isAlive() + currentState[i+1][j].isAlive() +
                        currentState[i+1][j+1].isAlive() + currentState[i][j+1].isAlive() + currentState[i-1][j+1].isAlive() + currentState[i-1][j].isAlive(); // middle
            }

            if(currentState[i][j].isAlive()) {
                switch (numberOfAliveNeighbors) {
                    case 2:
                    case 3:
                        nextState[i][j].stayAlive(currentState[i][j].getAge()); //TODO do poprawy sprawdzanie wieku
                        break;
                    default:
                        nextState[i][j].die();
                        break;
                }
            }
            else {
                switch (numberOfAliveNeighbors) {
                    case 3:
                        nextState[i][j].beBorn();
                        break;
                    default:
                        nextState[i][j].die();
                        break;
                }
            }
        }
    }

    return nextState;
}

void GameLogic::nextStep(GameWindow *gameWindow, bool aging)
{
    this->gameState = calculateNextStep(this->gameState, aging);
    gameWindow->updateUI();
}

void GameLogic::createBoard(short cellsInRow) {
    AgingCell tempCell = AgingCell();
    this->gameState = vector<vector<AgingCell>>(columns, vector<AgingCell>(rows, tempCell));
    this->cellsInRow = cellsInRow;
}

void GameLogic::randomizeGameState() {
    random_device random;
    for(int i = 0; i < this->gameState.size(); i++) {
        for(int j = 0; j < this->gameState[i].size(); j++) {

            mt19937 rng(random());

            if(uniform_int_distribution<int>(0, 9)(rng) >6) {
                this->gameState[i][j].beBorn();
            }
        }
    }
}

void GameLogic::reload(GameWindow *gameWindow) {
    this->cellsInRow = gameWindow->getChosenNumberOfCellsInRow();
    this->columns = this->cellsInRow;
    this->rows = gameWindow->getChosenNumberOfCellsInColumn();
    this->gameState = vector<vector<AgingCell>>(columns, vector<AgingCell>(rows, AgingCell()));
}
