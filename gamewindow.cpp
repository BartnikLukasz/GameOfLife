#include "gamelogic.h"
#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "iostream"

#include <QThread>
#include <QTimer>
#include <QFileDialog>
#include <QIODevice>
#include <QMessageBox>
#include <QVector>

using namespace std;

extern GameLogic * gameLogic;

QStringList sizes = {"60x30", "30x15", "60x120"};

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    gameActive = false;
    ui->setupUi(this);

    ui->sizeComboBox->addItems(sizes);

    board = new GameOfLifeGraphicsScene(this);
    ui->graphicsView->setScene(board);

    ui->graphicsView->update();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::drawEmptyBoard() {
    gameLogic->createBoard(getChosenNumberOfCellsInRow());
    board->drawCells(gameLogic->gameState, gameLogic->cellsInRow);
}

void GameWindow::toggleCell(int x, int y, GameOfLifeGraphicsScene *board)
{
    short cellSize = board->width / gameLogic->cellsInRow;

    short row = x / cellSize;
    short column = y / cellSize;
    if(gameLogic->gameState[row][column].isAlive()) {
        gameLogic->gameState[row][column].die();
    }
    else {
        gameLogic->gameState[row][column].beBorn();
    }
    cout<< "Row: "<<row<<endl;
    cout<< "Column: "<<column<<endl;
    cout<<gameLogic->gameState[row][column].isAlive();
    board->drawCells(gameLogic->gameState, gameLogic->cellsInRow);

    for(int i = 0; i< gameLogic->gameState.size(); i++) {
        for(int j = 0; j<gameLogic->gameState[i].size(); j++) {
            //cout << gameLogic->gameState[i][j].isAlive();
        }
        //cout<<endl;
    }
    cout<<endl;

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

    QTimer::singleShot(500, this, SLOT(nextStep()));

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
    QVector<QVector<bool>> savedStartingState = std2DVectorTo2DQVector(convertAgingCellToBool(gameLogic->gameStartingState));
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

            gameLogic->gameStartingState = convertBoolToAgingCell(qVectorToStd2DVector(loadedStartingStater));
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

short GameWindow::getChosenNumberOfCellsInRow() {
    switch(ui->sizeComboBox->currentIndex()) {
        case 0:
            return 60;
        case 1:
            return 30;
        case 2:
            return 120;
        default:
            return 60;
    }
}

short GameWindow::getChosenNumberOfCellsInColumn() {
    switch(ui->sizeComboBox->currentIndex()) {
        case 0:
            return 30;
        case 1:
            return 15;
        case 2:
            return 60;
        default:
            return 30;
    }
}

void GameWindow::on_sizeComboBox_currentIndexChanged(int index)
{
    if(gameLogic) {
        gameLogic->reload();
        drawEmptyBoard();
    }
}

vector<vector<bool>> GameWindow::convertAgingCellToBool(vector<vector<AgingCell>> agingCellGameState) {

    vector<vector<bool>> returnedVector = vector<vector<bool>>(agingCellGameState.size(), vector<bool>(agingCellGameState[0].size(), false));

    for(int i = 0; i < agingCellGameState.size(); i++) {

        for(int j = 0; j<agingCellGameState[i].size(); j++) {

            returnedVector[i][j] = true; //agingCellGameState[i][j].isAlive();

        }
    }

    return returnedVector;
}

vector<vector<AgingCell>> GameWindow::convertBoolToAgingCell(vector<vector<bool>> boolGameState) {

    vector<vector<AgingCell>> returnedVector = vector<vector<AgingCell>>(boolGameState.size(), vector<AgingCell>(boolGameState[0].size(), AgingCell()));

    for(int i = 0; i < boolGameState.size(); i++) {

        for(int j = 0; j<boolGameState[i].size(); j++) {

            if(boolGameState[i][j]) {
                returnedVector[i][j].beBorn();
            }
            else {
                returnedVector[i][j].die();
            }
        }
    }

    return returnedVector;
}
