#include "gamelogic.h"
#include "gamewindow.h"

#include <QApplication>
#include <QGraphicsRectItem>

GameWindow * gameWindow;

GameLogic * gameLogic;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gameWindow = new GameWindow();
    gameLogic = new GameLogic();

    gameWindow->drawEmptyBoard();
    //gameWindow->resize(1280, 720);
    gameWindow->show();
    return a.exec();
}
