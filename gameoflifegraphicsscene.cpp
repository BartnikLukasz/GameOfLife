#include "gameoflifegraphicsscene.h"
#include "gamewindow.h"

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
    //TODO zmiana stanu danej komórki
}

void GameOfLifeGraphicsScene::drawCells(vector<vector<bool>> gameState, short cellsInRow)
{
    short imageHeight = 400;
    short imageWidth = 400;

    short cellSize = imageWidth / cellsInRow;
    short cellsInColumn = imageHeight / cellSize;

    QImage image(imageWidth, imageHeight, QImage::Format_RGB32);

    QRgb aliveColor = qRgb(200, 200, 200);
    QRgb deadColor = qRgb(50, 50, 50);

    QPainter painter(&image);

    /*painter.fillRect(0, 0, cellSize-2, cellSize-2, deadColor);
    painter.fillRect(0, cellSize, cellSize-2, (2*cellSize)-2, deadColor);
    painter.fillRect(0, 2*cellSize, cellSize-2, (3*cellSize)-2, deadColor);
    painter.fillRect(cellSize, 0, (2*cellSize)-2, cellSize-2, deadColor);
    painter.fillRect(cellSize, cellSize, (2*cellSize)-2, (2*cellSize)-2, deadColor);*/

    for(int i = 0; i < cellsInRow; i++) {

        for(int j = 0; j < cellsInRow; j++) {

            if(gameState[i][j]) {
                painter.fillRect(i*cellSize, j*cellSize, ((i+1)*cellSize)-2, ((j+1)*cellSize)-2, aliveColor);
            }
            else {
                painter.fillRect(i*cellSize, j*cellSize, ((i+1)*cellSize)-2, ((j+1)*cellSize)-2, deadColor);
            }
        }
    }
    setSceneRect(0, 0, imageWidth, imageHeight);
    addPixmap(QPixmap::fromImage(image));
}


