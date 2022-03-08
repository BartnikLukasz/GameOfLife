#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "gameoflifegraphicsscene.h"
#include "ui_mainwindow.h"


#include <QMainWindow>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    void toggleCell(int x, int y, GameOfLifeGraphicsScene *board);

    void updateUI();

    void startGame();
private slots:
    void on_startButton_clicked();
    void nextStep();

private:
    Ui::GameWindow *ui;
    GameOfLifeGraphicsScene *board;
    QPixmap image;

    bool gameActive;
};
#endif // GAMEWINDOW_H
