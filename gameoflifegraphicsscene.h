#ifndef GAMEOFLIFEGRAPHICSSCENE_H
#define GAMEOFLIFEGRAPHICSSCENE_H

#include "agingcell.h"

#include <QGraphicsScene>
#include <QMainWindow>

using namespace std;

class GameOfLifeGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameOfLifeGraphicsScene(QObject *parent = nullptr);

    GameOfLifeGraphicsScene(QMainWindow * parent = 0);
    GameOfLifeGraphicsScene(QGraphicsScene * parent = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void drawCells(vector<vector<AgingCell> > gameState, short cellsInRow);

    short width;

    short height;

};

#endif // GAMEOFLIFEGRAPHICSSCENE_H
