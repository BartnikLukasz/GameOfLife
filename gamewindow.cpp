#include "gamelogic.h"
#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "iostream"
#include "converters.h"

#include <QThread>
#include <QTimer>
#include <QFileDialog>
#include <QIODevice>
#include <QMessageBox>
#include <QVector>

using namespace std;

extern GameLogic * gameLogic;

QStringList sizes = {"60x30", "30x15", "80x40"};
QStringList algorithms = {"Normal", "Die easier", "Die harder"};

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    gameActive = false;
    ui->setupUi(this);
    ui->sizeComboBox->addItems(sizes);
    ui->algorithmComboBox->addItems(algorithms);

    board = new GameOfLifeGraphicsScene(this);
    ui->graphicsView->setScene(board);

    connectSignalsAndSlots();

    ui->graphicsView->update();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::drawEmptyBoard() {
    gameLogic->reload(this);
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

    gameLogic->nextStep(this, ui->agingRadio->isChecked());
    board->drawCells(gameLogic->gameState, gameLogic->cellsInRow);

    QTimer::singleShot(500, this, SLOT(nextStep()));

    ui->graphicsView->update();
}

void GameWindow::startStopButton_clicked()
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


void GameWindow::saveButton_clicked()
{
    if(gameLogic->gameStartingState.empty()) {
        gameLogic->gameStartingState = gameLogic->gameState;
    }
    saveStartingState();
}


void GameWindow::loadButton_clicked()
{
    pause();
    if(loadStartingState()) {
        gameLogic->gameState = gameLogic->gameStartingState;
        board->drawCells(gameLogic->gameState, gameLogic->cellsInRow);
    }
}

void GameWindow::randomButton_clicked()
{
    gameLogic->randomizeGameState();
    board->drawCells(gameLogic->gameState, gameLogic->cellsInRow);
    updateUI();
}

void GameWindow::saveCurrentButton_clicked()
{
    if(gameLogic->gameState.empty()) {
        return;
    }
    saveCurrentState();
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
    QVector<QVector<bool>> savedStartingState = cvt::std2DVectorTo2DQVector(cvt::convertAgingCellToBool(gameLogic->gameStartingState));
    out << savedStartingState;

    return true;
    }
}

bool GameWindow::saveCurrentState() {

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
    QVector<QVector<bool>> savedState = cvt::std2DVectorTo2DQVector(cvt::convertAgingCellToBool(gameLogic->gameState));
    out << savedState;

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
            QVector<QVector<bool>> loadedStartingState;
            in >> loadedStartingState;

            gameLogic->gameStartingState = cvt::convertBoolToAgingCell(cvt::qVectorToStd2DVector(loadedStartingState));
            return true;
    }
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
            return 80;
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
            return 40;
        default:
            return 30;
    }
}

void GameWindow::sizeComboBox_currentIndexChanged(int index)
{
    if(gameLogic) {
        gameLogic->reload(this);
        drawEmptyBoard();
    }
}

void GameWindow::algorithmComboBox_currentIndexChanged(int index)
{
    gameLogic->algorithmType = index;
}

void GameWindow::connectSignalsAndSlots() {
    QObject::connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveButton_clicked()));
    QObject::connect(ui->saveCurrentButton, SIGNAL(clicked()), this, SLOT(saveCurrentButton_clicked()));
    QObject::connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadButton_clicked()));
    QObject::connect(ui->startStopButton, SIGNAL(clicked()), this, SLOT(startStopButton_clicked()));
    QObject::connect(ui->randomButton, SIGNAL(clicked()), this, SLOT(randomButton_clicked()));
    QObject::connect(ui->sizeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(sizeComboBox_currentIndexChanged(int)));
}


