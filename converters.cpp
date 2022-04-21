#include "gamewindow.h"
#include "converters.h"
#include <vector>

using namespace std;

namespace converters {

    vector<vector<bool>> convertCellToBool(vector<vector<shared_ptr<Cell>>> cellGameState) {

        vector<vector<bool>> returnedVector = vector<vector<bool>>(cellGameState.size(), vector<bool>(cellGameState[0].size(), false));

        for(int i = 0; i < cellGameState.size(); i++) {

            for(int j = 0; j<cellGameState[i].size(); j++) {

                returnedVector[i][j] = cellGameState[i][j]->isAlive();

            }
        }

        return returnedVector;
    }

    vector<vector<shared_ptr<Cell>>> convertBoolToCell(vector<vector<bool>> boolGameState) {

        vector<vector<shared_ptr<Cell>>> returnedVector(boolGameState.size(), vector<shared_ptr<Cell>>(boolGameState[0].size()));

        for(int i=0; i<returnedVector.size(); i++) {
            vector<shared_ptr<Cell>> tempRow(boolGameState[0].size());
            generate(tempRow.begin(), tempRow.end(), [] { return make_shared<Cell>(); });
            returnedVector[i] = tempRow;
        }

        for(int i = 0; i < boolGameState.size(); i++) {

            for(int j = 0; j<boolGameState[i].size(); j++) {

                if(boolGameState[i][j]) {
                    returnedVector[i][j]->beBorn();
                }
                else {
                    returnedVector[i][j]->die();
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
}

namespace cvt = converters;
