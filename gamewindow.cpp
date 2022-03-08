#include "gamelogic.h"
#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QThread>
#include <QTimer>

using namespace std;

extern GameLogic * gameLogic;

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    gameActive = false;
    ui->setupUi(this);
    board = new GameOfLifeGraphicsScene(this);
    ui->graphicsView->setScene(board);

    ui->graphicsView->update();

    gameLogic->createBoard(60); // zmienic na edytowalne
    board->drawCells(gameLogic->gameState, gameLogic->cellsInRow);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::toggleCell(int x, int y, GameOfLifeGraphicsScene *board)
{
    short imageHeight = 800; //TODO zmiana wielkości na ustawialną
    short imageWidth = 1200;

    short cellSize = imageWidth / gameLogic->cellsInRow;

    short row = x / cellSize;
    short column = y / cellSize;
    gameLogic->gameState[row][column] = !gameLogic->gameState[row][column];
    board->drawCells(gameLogic->gameState, gameLogic->cellsInRow);

    this->update();
}

void GameWindow::updateUI()
{
    ui->graphicsView->update();
}

void GameWindow::startGame() {
    gameActive = true;
    nextStep();
}

void GameWindow::nextStep() {

    gameLogic->nextStep();
    board->drawCells(gameLogic->gameState, gameLogic->cellsInRow);

    QTimer::singleShot(500, this, SLOT(nextStep()));

    ui->graphicsView->update();
}

void GameWindow::on_startButton_clicked()
{
    startGame();
}

