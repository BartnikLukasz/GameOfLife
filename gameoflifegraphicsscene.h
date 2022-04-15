#ifndef GAMEOFLIFEGRAPHICSSCENE_H
#define GAMEOFLIFEGRAPHICSSCENE_H

#include "agingcell.h"

#include <QGraphicsScene>
#include <QMainWindow>

using namespace std;

/*!
 * \brief Klasa GameOfLifeGraphicsScene
 *
 * Klasa odpowiedzialna za rysowanie stanu planszy na interfejsie graficznym, oraz obsługę interakcji użytkownika z planszą.
 */
class GameOfLifeGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    /*!
     * \brief Konstruktor GameOfLifeGraphicsScene
     * \param parent
     */
    explicit GameOfLifeGraphicsScene(QObject *parent = nullptr);

    /*!
     * \brief Konstruktor GameOfLifeGraphicsScene
     *
     * Ustawia wysokość i szerokość ekranu rozgrywki.
     * \param parent
     */
    GameOfLifeGraphicsScene(QMainWindow * parent = 0);
    /*!
     * \brief Konstruktor GameOfLifeGraphicsScene
     * \param parent
     */
    GameOfLifeGraphicsScene(QGraphicsScene * parent = 0);

    /*!
     * \brief Metoda mousePressEvent
     *
     * Metoda obsługująca kliknięcie myszy na planszę.
     * \param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    /*!
     * \brief Metoda drawCells
     *
     * Rysuje planszę zgodnie z danym jej stanem planszy oraz ilością komórek w rzędzie.
     * \param gameState aktualny stan planszy.
     * \param cellsInRow ilość komórek w rzędzie.
     */
    void drawCells(const vector<vector<shared_ptr<Cell>> > &gameState, short cellsInRow);

    /*!
     * \brief Pole width
     *
     * Pole zawierające informację o szerokości ekranu.
     */
    short width;

    /*!
     * \brief Pole height
     *
     * Pole zawierające informację o wysokości ekranu.
     */
    short height;

};

#endif // GAMEOFLIFEGRAPHICSSCENE_H
