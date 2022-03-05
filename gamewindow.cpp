#include "gamelogic.h"
#include "gamewindow.h"
#include "ui_gamewindow.h"

using namespace std;

extern GameLogic * gameLogic;

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::toggleCell(int x, int y, GameOfLifeGraphicsScene *board)
{
    short imageHeight = 400; //TODO zmiana wielkości na ustawialną
    short imageWidth = 400;

    short cellSize = imageWidth / gameLogic->cellsInRow;

    short row = x / cellSize;
    short column = y / cellSize;
    gameLogic->gameState[row][column] = true;
    board->drawCells(gameLogic->gameState, gameLogic->cellsInRow);
    this->update();
}

void GameWindow::updateUI()
{
}
