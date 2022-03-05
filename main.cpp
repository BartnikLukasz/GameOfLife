#include "gamelogic.h"
#include "gamewindow.h"

#include <QApplication>
#include <QGraphicsRectItem>

GameWindow * gameWindow;

GameLogic * gameLogic;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gameLogic = new GameLogic();
    gameWindow = new GameWindow();
    gameWindow->show();
    return a.exec();
}
