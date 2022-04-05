#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "agingcell.h"
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
    short getChosenNumberOfCellsInRow();
    short getChosenNumberOfCellsInColumn();
    void drawEmptyBoard();
    GameOfLifeGraphicsScene *getBoard();

public slots:
    void initializeNextStep();

private slots:

    void saveButton_clicked();

    void loadButton_clicked();

    void startStopButton_clicked();

    void randomButton_clicked();

    void sizeComboBox_currentIndexChanged(int index);

    void saveCurrentButton_clicked();

    void algorithmComboBox_currentIndexChanged(int index);

private:
    Ui::GameWindow *ui;
    GameOfLifeGraphicsScene *board;
    QPixmap image;

    bool saveStartingState();
    bool saveCurrentState();
    bool loadStartingState();
    void connectSignalsAndSlots();
};
#endif // GAMEWINDOW_H
