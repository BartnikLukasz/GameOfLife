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

/*!
 * \brief Klasa GameWindow
 *
 * Klasa GameWindow łączy interfejs graficzny aplikacji z logiką rozgrywki. Obsługuje interakcje z elementami interfejsu graficznego wywołując odpowiednie reakcje w aplikacji.
 */
class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Konstruktor klasy GameWindow
     *
     * Przygotowuje interfejs graficzny, tworzy obiekt klasy GameOFLifeGraphicsScene, łączy sygnały ze slotami.
     * \param parent
     */
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    /*!
     * \brief Metoda toggleCell
     *
     * Jest odpowiedzialna za reakcję na kliknięcie na planszę. Wywołuje rysowanie planszy zgodnie z jej nowym stanem.
     * \param x parametr x punktu na ekranie.
     * \param y parametr y punktu na ekranie.
     * \param board obiekt klasy GameOFLifeGraphicsScene.
     */
    void toggleCell(int x, int y, GameOfLifeGraphicsScene *board);

    /*!
     * \brief Metoda updateUI
     *
     * Metoda wywołująca odświeżenie stanu interfejsu graficznego aplikacji.
     */
    void updateUI();

    /*!
     * \brief startGame
     *
     * Metoda rozpoczynająca rozgrywkę.
     */
    void startGame();
    /*!
     * \brief Metoda getChosenNumberOfCellsInRow
     *
     * Metoda zwracająca wybraną w interfejsie graficznym liczbę komórek w rzędzie.
     * \return wybrana liczba komórek w rzędzie.
     */
    short getChosenNumberOfCellsInRow();
    /*!
     * \brief Metoda getChosenNumberOfCellsInColumn
     *
     * Metoda zwracająca wybraną w interfejsie graficznym liczbę komórek w kolumnie.
     * \return wybrana liczba komórek w kolumnie.
     */
    short getChosenNumberOfCellsInColumn();
    /*!
     * \brief Metoda drawEmptyBoard
     *
     * Tworzy i wyświetla pustą planszę, w celu rozpoczęcia rozgrywki.
     */
    void drawEmptyBoard();
    /*!
     * \brief Metoda getBoard
     *
     * Zwraca pole board, aby dostęp do niego miała klasa GameLogic.
     * \return pole board
     */
    GameOfLifeGraphicsScene *getBoard();

    /*!
     * \brief Metoda getTimeBetweenStepsValue
     *
     * Zwraca wartość wpisaną przez użytkownika do pola czasu.
     * \return wartość czasu w ms pomiędzy krokami.
     */
    int getTimeBetweenStepsValue();

public slots:
    /*!
     * \brief Metoda SLOT initializeNextStep
     *
     * Jest to SLOT odpowiedzialny za ciągłość rozgrywki, jest wywoływany co określoną ilość czasu.
     */
    void initializeNextStep();

private slots:

    /*!
     * \brief Metoda SLOT saveButton_clicked
     *
     * Obsługuje kliknięcie przycisku 'Save'. Wywołuje metodę saveStartingState.
     */
    void saveButton_clicked();

    /*!
     * \brief Metoda SLOT loadButton_clicked
     *
     * Obsługuje kliknięcie przycisku 'Load'. Wywołuje metodę loadStartingState.
     */
    void loadButton_clicked();

    /*!
     * \brief Metoda SLOT startStopButton_clicked
     *
     * Obsługuje kliknięcie przycisku 'Start'. Może grę uruchomić, lub zatrzymać. Wywołuje metodę startGame.
     */
    void startStopButton_clicked();

    /*!
     * \brief Metoda SLOT randomButton_clicked
     *
     * Obsługuje kliknięcie przycisku 'Random'. Wywołuje metodę randomizeGameState.
     */
    void randomButton_clicked();

    /*!
     * \brief Metoda SLOT sizeComboBox_currentIndexChanged
     *
     * Obsługuje zmianę wyboru wielkości planszy. Wywołuje metodę reload.
     * \param index
     */
    void sizeComboBox_currentIndexChanged(int index);

    /*!
     * \brief Metoda SLOT saveCurrentButton_clicked
     *
     * Obsługuje kliknięcie przycisku 'Save current'. Wywołuje metodę saveCurrentState.
     */
    void saveCurrentButton_clicked();

    /*!
     * \brief Metoda SLOT algorithmComboBox_currentIndexChanged
     *
     * Obsługuje zmianę wyboru algorytmu życia komórek. Ustawia wartość pola algorithmType.
     * \param index
     */
    void algorithmComboBox_currentIndexChanged(int index);

private:
    /*!
     * \brief Pole ui
     *
     * Obiektowa reprezentacja interfejsu graficznego aplikacji,
     */
    Ui::GameWindow *ui;

    /*!
     * \brief Pole board
     *
     * Obiekt klasy GameOfLifeGraphicsScene służący do rysowania planszy.
     */
    GameOfLifeGraphicsScene *board;
    /*!
     * \brief Pole image
     *
     * Obiekt klasy QPixmap będący obrazową reprezentacją planszy.
     */
    QPixmap image;

    /*!
     * \brief Metoda saveStartingState
     *
     * Zapisuje początkowy stan planszy do pliku.
     * \return true jeżeli zapis się uda, false jeżeli zapis się nie powiedzie.
     */
    bool saveStartingState();
    /*!
     * \brief Metoda saveCurrentState
     *
     * Zapisuje aktualny stan planszy do pliku
     * \return true jeżeli zapis się uda, false jeżeli zapis się nie powiedzie.
     */
    bool saveCurrentState();
    /*!
     * \brief Metoda loadStartingState
     *
     * Wczytuje stan planszy z pliku.
     * \return true jeżeli odczyt się uda, false jeżeli odczyt się nie powiedzie.
     */
    bool loadStartingState();
    /*!
     * \brief Metoda connectSignalsAndSlots
     *
     * Metoda łącząca sygnały i sloty.
     */
    void connectSignalsAndSlots();
};
#endif // GAMEWINDOW_H
