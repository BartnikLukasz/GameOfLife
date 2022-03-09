#include "gamelogic.h"
#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QThread>
#include <QTimer>
#include <QFileDialog>
#include <QIODevice>
#include <QMessageBox>
#include <QVector>

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
    short imageHeight = 600; //TODO zmiana wielkości na ustawialną
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
    unpause();
    nextStep();
}

void GameWindow::nextStep() {

    if (!gameActive) {
        return;
    }

    gameLogic->nextStep();
    board->drawCells(gameLogic->gameState, gameLogic->cellsInRow);

    QTimer::singleShot(100, this, SLOT(nextStep()));

    ui->graphicsView->update();
}

void GameWindow::on_startStopButton_clicked()
{
    if(!gameActive) {
        gameLogic->gameStartingState = gameLogic->gameState;
        ui->startStopButton->setText("Stop");
        startGame();
    }
    else {
        pause();
        ui->startStopButton->setText("Start");
    }
}


void GameWindow::on_saveButton_clicked()
{
    if(gameLogic->gameStartingState.empty()) {
        gameLogic->gameStartingState = gameLogic->gameState;
    }
    saveStartingState();
}


void GameWindow::on_loadButton_clicked()
{
    pause();
    if(loadStartingState()) {
        gameLogic->gameState = gameLogic->gameStartingState;
        board->drawCells(gameLogic->gameState, gameLogic->cellsInRow);
    }
}

void GameWindow::on_randomButton_clicked()
{
    gameLogic->randomizeGameState();
    board->drawCells(gameLogic->gameState, gameLogic->cellsInRow);
    updateUI();
}

bool GameWindow::saveStartingState() {

    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save starting state"), "",
            tr("Game starting state (*.gss);;All Files (*)"));

    if (fileName.isEmpty())
            return false;
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return false;
            }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_2);
    QVector<QVector<bool>> savedStartingState = std2DVectorTo2DQVector(gameLogic->gameStartingState);
    out << savedStartingState;

    return true;
    }
}

bool GameWindow::loadStartingState() {

    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Save starting state"), "",
            tr("Game starting state (*.gss);;All Files (*)"));

    if (fileName.isEmpty())
            return false;
        else {

            QFile file(fileName);

            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return false;
            }

            QDataStream in(&file);
            in.setVersion(QDataStream::Qt_6_2);
            QVector<QVector<bool>> loadedStartingStater;
            in >> loadedStartingStater;

            gameLogic->gameStartingState = qVectorToStd2DVector(loadedStartingStater);
            return true;
    }
}

QVector<QVector<bool>> GameWindow::std2DVectorTo2DQVector(vector<vector<bool>> vector) {

    QVector<QVector<bool>> returnedQVector;

    for(int i = 0; i < vector.size(); i++) {

        QVector<bool> tempQVector = QVector<bool>(vector[i].begin(), vector[i].end());

        returnedQVector.push_back(tempQVector);
    }

    return returnedQVector;
}

vector<vector<bool>> GameWindow::qVectorToStd2DVector(QVector<QVector<bool>> qVector) {

    vector<vector<bool>> returnedVector;

    for(int i = 0; i < qVector.size(); i++) {

        vector<bool> tempVector = vector<bool>(qVector[i].begin(), qVector[i].end());

        returnedVector.push_back(tempVector);
    }

    return returnedVector;
}

void GameWindow::pause() {
    gameActive = false;
}

void GameWindow::unpause() {
    gameActive = true;
}

