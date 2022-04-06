#include "gamelogic.h"
#include "gamewindow.h"
#include "iostream"
#include "random"
#include "converters.h"

#include <QTimer>
#include <vector>

using namespace std;

GameLogic::GameLogic()
{
    this->gameActive = false;
    this->algorithmType = 0;
}

vector<vector<AgingCell> > GameLogic::calculateNextStep(vector<vector<AgingCell> > &currentState,  bool aging)
{
    vector<vector<AgingCell>> nextState(columns, vector<AgingCell>(rows, AgingCell())); //utworzenie macierzy reprezentującej planszę

    for(int i = 0; i < currentState.size(); i++) {

        for(int j = 0; j < currentState[i].size(); j++) {

            if(currentState[i][j].isAlive()) { //Jeżeli komórka jest żywa
                if(aging){                      //Jeżeli starzenie się jest włączone, postarz komórkę
                    currentState[i][j].getOlder();
                }
                else {                          //Jeżeli starzenie się jest wyłączone, konwertuj między klasami i wywołaj metodę klasy która się nie starzeje
                    LivingCell livingCell = cvt::convertAgingCellToLivingCell(currentState[i][j]);
                    livingCell.getOlder();
                    currentState[i][j] = cvt::convertLivingCellToAgingCell(livingCell);
                }
            }

        }

    }

    //Zliczanie żyjących sąsiadów
    for(int i = 0; i < nextState.size(); i++) {

        for(int j = 0; j < nextState[i].size(); j++) {

            short numberOfAliveNeighbors = 0;

            if(i == 0 && j == 0) {
                numberOfAliveNeighbors += currentState[0][1].isAlive() + currentState[1][0].isAlive() + currentState[1][1].isAlive();           //Lewy górny róg
            }
            else if(i == 0 && j == rows-1) {
                numberOfAliveNeighbors += currentState[0][j-1].isAlive() + currentState[1][j-1].isAlive() + currentState[1][j].isAlive();       //Lewy dolny róg
            }
            else if(i == columns-1 && j == 0) {
                numberOfAliveNeighbors += currentState[i-1][0].isAlive() + currentState[i-1][1].isAlive() + currentState[i][1].isAlive();       //Prawy górny róg
            }
            else if(i == columns-1 && j == rows-1) {
                numberOfAliveNeighbors += currentState[i-1][j].isAlive() + currentState[i-1][j-1].isAlive() + currentState[i][j-1].isAlive();   //Prawy dolny róg
            }
            else if(i == 0) {
                numberOfAliveNeighbors += currentState[0][j-1].isAlive() + currentState[1][j-1].isAlive() + currentState[1][j].isAlive() +
                        currentState[1][j+1].isAlive() + currentState[0][j+1].isAlive();                                                        //Lewy brzeg
            }
            else if(j == 0) {
                numberOfAliveNeighbors += currentState[i-1][0].isAlive() + currentState[i-1][1].isAlive() + currentState[i][1].isAlive() +
                        currentState[i+1][1].isAlive() + currentState[i+1][0].isAlive();                                                        //Górny brzeg
            }
            else if(i == columns-1) {
                numberOfAliveNeighbors += currentState[i][j-1].isAlive() + currentState[i-1][j-1].isAlive() + currentState[i-1][j].isAlive() +
                        currentState[i-1][j+1].isAlive() + currentState[i][j+1].isAlive();                                                      //Prawy brzeg
            }
            else if(j == rows-1) {
                numberOfAliveNeighbors += currentState[i-1][j].isAlive() + currentState[i-1][j-1].isAlive() + currentState[i][j-1].isAlive() +
                        currentState[i+1][j-1].isAlive() + currentState[i+1][j].isAlive();                                                      //Dolny brzeg
            }
            else {
                numberOfAliveNeighbors += currentState[i-1][j-1].isAlive() + currentState[i][j-1].isAlive() + currentState[i+1][j-1].isAlive() + currentState[i+1][j].isAlive() +
                        currentState[i+1][j+1].isAlive() + currentState[i][j+1].isAlive() + currentState[i-1][j+1].isAlive() + currentState[i-1][j].isAlive(); //Środek
            }

            //Ustawianie stanu komórki zależnie od ilości żywych sąsiadów
            switch (this->algorithmType) {
                case 0:                                                                 //zwykłe zasady
                    if(currentState[i][j].isAlive()) {
                        switch (numberOfAliveNeighbors) {
                            case 2:
                            case 3:
                                nextState[i][j].stayAlive(currentState[i][j].getAge());
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
                break;

                case 1:                                                                 //zasady dla ciężko urodzić, łatwo przeżyć
                    if(currentState[i][j].isAlive()) {
                        switch (numberOfAliveNeighbors) {
                            case 3:
                            case 4:
                            case 5:
                            case 6:
                                nextState[i][j].stayAlive(currentState[i][j].getAge());
                                break;
                            default:
                                nextState[i][j].die();
                                break;
                        }
                    }
                    else {
                        switch (numberOfAliveNeighbors) {
                            case 4:
                            case 5:
                            case 6:
                                nextState[i][j].beBorn();
                                break;
                            default:
                                nextState[i][j].die();
                                break;
                        }
                    }
                break;

                case 2:                                                                 //zasady dla łatwo urodzić, ciężko przeżyć
                    if(currentState[i][j].isAlive()) {
                        switch (numberOfAliveNeighbors) {
                            case 5:
                            case 6:
                                nextState[i][j].stayAlive(currentState[i][j].getAge());
                                break;
                            default:
                                nextState[i][j].die();
                                break;
                        }
                    }
                    else {
                        switch (numberOfAliveNeighbors) {
                            case 3:
                            case 4:
                                nextState[i][j].beBorn();
                                break;
                            default:
                                nextState[i][j].die();
                                break;
                        }
                    }
                break;
                }
        }
    }

    return nextState;
}

void GameLogic::nextStep(GameWindow *gameWindow, bool aging) {

    if (!gameActive) {
        return;
    }

    nextLogicStep(gameWindow, aging);
    gameWindow->getBoard()->drawCells(this->gameState, this->cellsInRow);   //Narysuj nowy stan planszy

    QTimer::singleShot(gameWindow->getTimeBetweenStepsValue(), gameWindow, SLOT(initializeNextStep()));        //Wykonywanie metody co określony czas

    gameWindow->updateUI();
}

void GameLogic::nextLogicStep(GameWindow *gameWindow, bool aging)
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

void GameLogic::pause()
{
    this->gameActive = false;
}

void GameLogic::unpause()
{
    this->gameActive = true;
}

bool GameLogic::isGameActive()
{
    return gameActive;
}
