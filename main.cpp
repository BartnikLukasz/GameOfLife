#include "gamewindow.h"

#include <QApplication>
#include <QGraphicsRectItem>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    w.show();
    return a.exec();
}
