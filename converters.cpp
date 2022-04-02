#include "gamewindow.h"
#include "converters.h"
#include "livingcell.h"
#include <vector>

using namespace std;

namespace converters {

    vector<vector<bool>> convertAgingCellToBool(vector<vector<AgingCell>> agingCellGameState) {

        vector<vector<bool>> returnedVector = vector<vector<bool>>(agingCellGameState.size(), vector<bool>(agingCellGameState[0].size(), false));

        for(int i = 0; i < agingCellGameState.size(); i++) {

            for(int j = 0; j<agingCellGameState[i].size(); j++) {

                returnedVector[i][j] = agingCellGameState[i][j].isAlive();

            }
        }

        return returnedVector;
    }

    vector<vector<AgingCell>> convertBoolToAgingCell(vector<vector<bool>> boolGameState) {

        vector<vector<AgingCell>> returnedVector = vector<vector<AgingCell>>(boolGameState.size(), vector<AgingCell>(boolGameState[0].size(), AgingCell()));

        for(int i = 0; i < boolGameState.size(); i++) {

            for(int j = 0; j<boolGameState[i].size(); j++) {

                if(boolGameState[i][j]) {
                    returnedVector[i][j].beBorn();
                }
                else {
                    returnedVector[i][j].die();
                }
            }
        }

        return returnedVector;
    }

    QVector<QVector<bool>> std2DVectorTo2DQVector(vector<vector<bool>> vector) {

        QVector<QVector<bool>> returnedQVector;

        for(int i = 0; i < vector.size(); i++) {

            QVector<bool> tempQVector = QVector<bool>(vector[i].begin(), vector[i].end());

            returnedQVector.push_back(tempQVector);
        }

        return returnedQVector;
    }

    vector<vector<bool>> qVectorToStd2DVector(QVector<QVector<bool>> qVector) {

        vector<vector<bool>> returnedVector;

        for(int i = 0; i < qVector.size(); i++) {

            vector<bool> tempVector = vector<bool>(qVector[i].begin(), qVector[i].end());

            returnedVector.push_back(tempVector);
        }

        return returnedVector;
    }

    AgingCell convertLivingCellToAgingCell(LivingCell livingCell) {
        AgingCell agingCell = AgingCell();
        agingCell.stayAlive(livingCell.getAge());
        return agingCell;
    }

    LivingCell convertAgingCellToLivingCell(AgingCell agingCell) {
        LivingCell livingCell = LivingCell();
        livingCell.stayAlive(agingCell.getAge());
        return livingCell;
    }
}

namespace cvt = converters;
