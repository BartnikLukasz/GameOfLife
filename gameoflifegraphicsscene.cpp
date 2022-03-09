#include "gameoflifegraphicsscene.h"
#include "gamewindow.h"

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

}

GameOfLifeGraphicsScene::GameOfLifeGraphicsScene(QGraphicsScene *parent)
{

}

void GameOfLifeGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    gameWindow->toggleCell(event->scenePos().x(), event->scenePos().y(), this);
}

void GameOfLifeGraphicsScene::drawCells(vector<vector<bool>> gameState, short cellsInRow)
{
    short imageHeight = 600; //TODO zmiana wielkości na ustawialną
    short imageWidth = 1200;

    short cellSize = imageWidth / cellsInRow;
    short cellsInColumn = imageHeight / cellSize;

    QImage image(imageWidth, imageHeight, QImage::Format_RGB32);

    QRgb deadColor = qRgb(200, 200, 200);
    QRgb aliveColor = qRgb(50, 50, 50);

    QPainter painter(&image);

    painter.fillRect(0, 0, imageWidth, imageHeight, qRgb(255, 255, 255));

    /*painter.fillRect(0, 0, cellSize-2, cellSize-2, deadColor);
    painter.fillRect(0, cellSize, cellSize-2, (2*cellSize)-2, deadColor);
    painter.fillRect(0, 2*cellSize, cellSize-2, (3*cellSize)-2, deadColor);
    painter.fillRect(cellSize, 0, (2*cellSize)-2, cellSize-2, deadColor);
    painter.fillRect(cellSize, cellSize, (2*cellSize)-2, (2*cellSize)-2, deadColor);*/

    for(int i = 0; i < cellsInRow; i++) {

        for(int j = 0; j < cellsInColumn; j++) {

            QRect *cell = new QRect(QPoint(i*cellSize, j*cellSize), QPoint(((i+1)*cellSize)-2, ((j+1)*cellSize)-2));

            if(gameState[i][j]) {
                painter.fillRect(*cell, aliveColor);
            }
            else {
                painter.fillRect(*cell, deadColor);
            }
        }
    }

    setSceneRect(0, 0, imageWidth, imageHeight);
    addPixmap(QPixmap::fromImage(image));
}


