#include "Cell.h"
#include "gameoflifegraphicsscene.h"
#include "gamewindow.h"
#include "iostream"

#include <QGraphicsSceneMouseEvent>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QRgb>

using namespace std;

extern GameWindow * gameWindow;

GameOfLifeGraphicsScene::GameOfLifeGraphicsScene(QObject *parent)
    : QGraphicsScene{parent}
{

}

GameOfLifeGraphicsScene::GameOfLifeGraphicsScene(QMainWindow *parent)
{
    this->height = 670;
    this->width = 1380;
}

GameOfLifeGraphicsScene::GameOfLifeGraphicsScene(QGraphicsScene *parent)
{

}

void GameOfLifeGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    gameWindow->toggleCell(event->scenePos().x(), event->scenePos().y(), this);
}

void GameOfLifeGraphicsScene::drawCells(vector<vector<AgingCell>> gameState, short cellsInRow)
{
    short cellSize = width / cellsInRow;
    short cellsInColumn = height / cellSize;

    QImage image(width, height, QImage::Format_RGB32);

    QRgb deadColor = qRgb(200, 200, 200);

    QPainter painter(&image);

    painter.fillRect(0, 0, width, height, qRgb(255, 255, 255));

    for(int i = 0; i < cellsInRow; i++) {

        for(int j = 0; j < cellsInColumn; j++) {

            QRect *cell = new QRect(QPoint(i*cellSize, j*cellSize), QPoint(((i+1)*cellSize)-2, ((j+1)*cellSize)-2));

            if(gameState[i][j].isAlive() && gameState[i][j].getAge()!=-1) {
                short calculatedShade = gameState[i][j].getAge()*30 + 50;
                painter.fillRect(*cell, qRgb(calculatedShade, calculatedShade, calculatedShade));
            }
            else {
                painter.fillRect(*cell, deadColor);
            }
        }
    }

    setSceneRect(0, 0, width, height);
    addPixmap(QPixmap::fromImage(image));
}


