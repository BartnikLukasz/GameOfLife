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
private slots:

    void nextStep();

    void on_saveButton_clicked();

    void on_loadButton_clicked();

    void on_startStopButton_clicked();

    void on_randomButton_clicked();

    void on_sizeComboBox_currentIndexChanged(int index);

private:
    Ui::GameWindow *ui;
    GameOfLifeGraphicsScene *board;
    QPixmap image;

    bool gameActive;
    bool saveStartingState();
    QVector<QVector<bool> > std2DVectorTo2DQVector(vector<vector<bool> > vector);
    bool loadStartingState();
    vector<vector<bool> > qVectorToStd2DVector(QVector<QVector<bool> > qVector);
    void pause();
    void unpause();
    vector<vector<bool> > convertAgingCellToBool(vector<vector<AgingCell> > agingCellGameState);
    vector<vector<AgingCell> > convertBoolToAgingCell(vector<vector<bool> > boolGameState);
};
#endif // GAMEWINDOW_H
