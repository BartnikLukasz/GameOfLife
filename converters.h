#ifndef CONVERTERS_H
#define CONVERTERS_H

#include "agingcell.h"

#include <QVector>
#include <vector>

using namespace std;

/*!
 * namespace zawierający metody konwertujące różne rodzaje wektorów na inne rodzaje, wykorzystywane w celu zapisu rozgrywki.
 * Zawiera również metody konwertujące AgingCell na LivingCell.
 */
namespace converters {

/*!
     * \brief Metoda convertAgingCellToBool
     *
     * Konwertuje vector obiektów AgingCell na vector typów bool
     * \param agingCellGameState vector obiektów AgingCell
     * \return vector typów bool
     */
    vector<vector<bool>> convertCellToBool(vector<vector<shared_ptr<Cell>>> cellGameState);

    /*!
     * \brief Metoda convertBoolToAgingCell
     *
     * Konwertuje vector typów bool na vector obiektów AgingCell
     * \param boolGameState vector typów bool
     * \return vector obiektów AgingCell
     */
    vector<vector<shared_ptr<Cell>>> convertBoolToCell(vector<vector<bool>> boolGameState);

    /*!
     * \brief Metoda std2DVectorTo2DQVector
     *
     * Konwertuje vector typów bool na QVector typów bool.
     * \param vector vector typów bool
     * \return QVector typów bool
     */
    QVector<QVector<bool>> std2DVectorTo2DQVector(vector<vector<bool>> vector);

    /*!
     * \brief Metoda qVectorToStd2DVector
     *
     * Konwertuje QVector typów bool na vector typów bool
     * \param qVector QVector typów bool
     * \return  vector typów bool;
     */
    vector<vector<bool>> qVectorToStd2DVector(QVector<QVector<bool>> qVector);

}

namespace cvt = converters;

#endif // CONVERTERS_H
