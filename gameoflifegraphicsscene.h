#ifndef GAMEOFLIFEGRAPHICSSCENE_H
#define GAMEOFLIFEGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QMainWindow>

class GameOfLifeGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameOfLifeGraphicsScene(QObject *parent = nullptr);
};

#endif // GAMEOFLIFEGRAPHICSSCENE_H
