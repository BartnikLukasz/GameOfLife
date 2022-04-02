#ifndef CONVERTERS_H
#define CONVERTERS_H

#include "agingcell.h"
#include "livingcell.h"

#include <QVector>
#include <vector>

using namespace std;

namespace converters {

    vector<vector<bool>> convertAgingCellToBool(vector<vector<AgingCell>> agingCellGameState);

    vector<vector<AgingCell>> convertBoolToAgingCell(vector<vector<bool>> boolGameState);

    QVector<QVector<bool>> std2DVectorTo2DQVector(vector<vector<bool>> vector);

    vector<vector<bool>> qVectorToStd2DVector(QVector<QVector<bool>> qVector);

    AgingCell convertLivingCellToAgingCell(LivingCell livingCell);

    LivingCell convertAgingCellToLivingCell(AgingCell agingCell);

}

namespace cvt = converters;

#endif // CONVERTERS_H
