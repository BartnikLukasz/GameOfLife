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
QStringList algorithms = {"Normal", "Die harder", "Die easier"};

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    ui->sizeComboBox->addItems(sizes);
    ui->algorithmComboBox->addItems(algorithms);
    ui->timeEdit->setValidator(new QIntValidator(20, 5000, this));

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

GameOfLifeGraphicsScene *GameWindow::getBoard()
{
    return this->board;
}

int GameWindow::getTimeBetweenStepsValue()
{
    return ui->timeEdit->text().toInt();
}

void GameWindow::initializeNextStep()
{
    gameLogic->nextStep(this, ui->agingRadio->isChecked()); //Wywoływanie metody nextStep jest tutaj, aby mogło byc slotem
}

void GameWindow::toggleCell(int x, int y, GameOfLifeGraphicsScene *board)
{
    short cellSize = board->width / gameLogic->cellsInRow;

    short row = x / cellSize;
    short column = y / cellSize;
    if(gameLogic->gameState[row][column].isAlive()) { //Jeżeli kliknięta komórka jest żywa, to ma umrzeć i odwrotnie
        gameLogic->gameState[row][column].die();
    }
    else {
        gameLogic->gameState[row][column].beBorn();
    }
    board->drawCells(gameLogic->gameState, gameLogic->cellsInRow);

    this->update();
}

void GameWindow::updateUI()
{
    ui->graphicsView->update();
}

void GameWindow::startGame() {
    gameLogic->unpause();
    initializeNextStep();   //Wywołanie początku gry
}

void GameWindow::startStopButton_clicked()
{
    if(!gameLogic->isGameActive()) {
        gameLogic->gameStartingState = gameLogic->gameState;
        ui->startStopButton->setText("Stop");
        startGame();
    }
    else {
        gameLogic->pause();
        ui->startStopButton->setText("Start");
    }
}


void GameWindow::saveButton_clicked()
{
    if(gameLogic->gameStartingState.empty()) {  //Jeżeli początkowy stan gry jest pusty, niech będzie wypełniony aktualnym stanem gry
        gameLogic->gameStartingState = gameLogic->gameState;
    }
    saveStartingState();
}


void GameWindow::loadButton_clicked()
{
    gameLogic->pause();
    if(loadStartingState()) {
        if(gameLogic->gameStartingState.size() != gameLogic->cellsInRow) {  //Jeżeli wielkośc planszy załadowanej gry jest inna niż wybrana wielkość planszy, zmień wielkość planszy
            switch(gameLogic->gameStartingState.size()) {
                case 60:
                    ui->sizeComboBox->setCurrentIndex(0);
                    gameLogic->reload(this);
                break;
                case 30:
                    ui->sizeComboBox->setCurrentIndex(1);
                    gameLogic->reload(this);
                break;
                case 80:
                    ui->sizeComboBox->setCurrentIndex(2);
                    gameLogic->reload(this);
                break;
                default:
                    ui->sizeComboBox->setCurrentIndex(0);
                    gameLogic->reload(this);
                break;
            }
        }
        gameLogic->gameState = gameLogic->gameStartingState;
        board->drawCells(gameLogic->gameState, gameLogic->cellsInRow);  //Narysowanie planszy od nowa po wczytaniu stanu gry
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

//Kod zaczerpnięty ze strony dokumentacji QT
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
    //Zapisać w ten sposób mogę tylko QVector<QVector<bool>>, więc konwertuję stan gry na ten typ
    QVector<QVector<bool>> savedStartingState = cvt::std2DVectorTo2DQVector(cvt::convertAgingCellToBool(gameLogic->gameStartingState));
    out << savedStartingState;

    return true;
    }
}

//Kod zaczerpnięty ze strony dokumentacji QT
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

//Kod zaczerpnięty ze strony dokumentacji QT
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

            //Przypisanie wczytanego stanu gry do gameStartingState
            gameLogic->gameStartingState = cvt::convertBoolToAgingCell(cvt::qVectorToStd2DVector(loadedStartingState));
            return true;
    }
}

short GameWindow::getChosenNumberOfCellsInRow() {   //Zależnie od wybranej opcji zwraca odpowiednią ilość komórek w rzędzie
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

short GameWindow::getChosenNumberOfCellsInColumn() {    //Zależnie od wybranej opcji zwraca odpowiednią ilość komórek w kolumnie
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

//Przypisanie sygnałów do slotów w osobnej funkcji
void GameWindow::connectSignalsAndSlots() {
    QObject::connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveButton_clicked()));
    QObject::connect(ui->saveCurrentButton, SIGNAL(clicked()), this, SLOT(saveCurrentButton_clicked()));
    QObject::connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadButton_clicked()));
    QObject::connect(ui->startStopButton, SIGNAL(clicked()), this, SLOT(startStopButton_clicked()));
    QObject::connect(ui->randomButton, SIGNAL(clicked()), this, SLOT(randomButton_clicked()));
    QObject::connect(ui->sizeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(sizeComboBox_currentIndexChanged(int)));
    QObject::connect(ui->algorithmComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(algorithmComboBox_currentIndexChanged(int)));
}


