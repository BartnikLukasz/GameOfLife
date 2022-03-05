#include "gamelogic.h"

#include <vector>

using namespace std;

#define rows 20
#define columns 20

GameLogic::GameLogic()
{

}

vector<vector<bool>> GameLogic::calculateNextStep(vector<vector<bool>> & currentState)
{
    vector<vector<bool>> nextState(rows, vector<bool>(columns, false)); //creating matrix representing state of the game

    for(int i = 0; i < columns; i++) {

        for(int j = 0; j < rows; j++) {

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
                        currentState[i+1][j+1] + currentState[i][j+1] + currentState[i-1][j+1] + currentState[i-1][j]; // middle]
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
