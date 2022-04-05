#ifndef CONVERTERS_H
#define CONVERTERS_H

#include "agingcell.h"
#include "livingcell.h"

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
    vector<vector<bool>> convertAgingCellToBool(vector<vector<AgingCell>> agingCellGameState);

    /*!
     * \brief Metoda convertBoolToAgingCell
     *
     * Konwertuje vector typów bool na vector obiektów AgingCell
     * \param boolGameState vector typów bool
     * \return vector obiektów AgingCell
     */
    vector<vector<AgingCell>> convertBoolToAgingCell(vector<vector<bool>> boolGameState);

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

    /*!
     * \brief Metoda convertLivingCellToAgingCell
     *
     * Konwertuje obiekt klasy LivingCell na obiekt klasy AgingCell
     * \param livingCell obiekt klasy LivingCell
     * \return obiekt klasy AgingCell
     */
    AgingCell convertLivingCellToAgingCell(LivingCell livingCell);

    /*!
     * \brief Metoda convertAgingCellToLivingCell
     *
     * Konwertuje obiekt klasy AgingCell na obiekt klasy LivingCell
     * \param agingCell obiekt klasy AgingCell
     * \return obiekt klasy LivingCell
     */
    LivingCell convertAgingCellToLivingCell(AgingCell agingCell);

}

namespace cvt = converters;

#endif // CONVERTERS_H
