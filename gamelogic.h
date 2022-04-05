#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "agingCell.h"
#include "gamewindow.h"

#include <string>
#include <vector>

using namespace std;

class GameWindow;

/*!
 * \brief Klasa GameLogic
 *
 * Jest odpowiedzialna za logikę rozgrywki. Znajduje się w nim między innymi reperzentacja planszy, metody pozwalające na zarządzanie nią
 * oraz logika odpowiedzialna za przebieg rozgrywki.
 */
class GameLogic
{
public:
    /*!
     * \brief Konstruktor klasy GameLogic
     *
     * Tworzy wyłączoną grę, ze zwykłym algorytmem życia komórek.
     */
    GameLogic();
    /*!
     * \brief Metoda calculateNextStep
     *
     * Jest odpowiedzialna za obliczanie następnego stanu planszy, na podstawie aktualnego oraz informacji czy komórki mają się starzeć.
     * \param currentState aktualny stan planszy
     * \param aging parametr zawierający informację, czy komórki mają się starzeć
     * \return vector obiektów klasy AgingCell będący oblczonym następnym stanem planszy
     */
    vector<vector<AgingCell>> calculateNextStep(vector<vector<AgingCell>>& currentState, bool aging);
    /*!
     * \brief Metoda nextLogicStep
     *
     * Jest odpowiedzialna za wywoływanie metody calculateNextStep oraz przypisywanie jej wyniku do aktualnego stanu planszy.
     * Wywołuje również update ekranu gry.
     * \param gameWindow obiekt klasy gameWindow.
     * \param aging parametr zawierający informację, czy komórki mają się starzeć
     */
    void nextLogicStep(GameWindow *gameWindow, bool aging);
    /*!
     * \brief Metoda createBoard
     *
     * Inicjalizuje planszę
     * \param cellsInRow ilość komórek jaka ma być w rzędzie
     */
    void createBoard(short cellsInRow);

    /*!
     * \brief Pole gameState
     *
     * Zawiera aktualny stan planszy.
     */
    vector<vector<AgingCell>> gameState;

    /*!
     * \brief Pole gameStartingState
     *
     * Zawiera początkowy stan planszy. Służy do zapisania stanu początkowego nawet na koniec rozgrywki.
     */
    vector<vector<AgingCell>> gameStartingState;

    /*!
     * \brief Pole cellsInRow
     *
     * Pole przechowujące informacje i ilości komórek w rzędzie.
     */
    short cellsInRow;

    /*!
     * \brief Pole algorithmType
     *
     * Pole przechowujące informację o wybranym algorytmie życia komórek.
     */
    short algorithmType;

    /*!
     * \brief Metoda randomizeGameState
     *
     * Ustawia w sposób pseudo-losowy stan planszy.
     */
    void randomizeGameState();

    /*!
     * \brief Metoda reload
     *
     * Metoda tworząca planszę od nowa, wykorzystywana w przypadku zmiany jej wielkości.
     * \param gameWindow obiekt klasy GameWindow.
     */
    void reload(GameWindow *gameWindow);
    /*!
     * \brief Metoda pause
     *
     * Metoda zatrzymująca grę, ustawia pole gameActive na false.
     */
    void pause();
    /*!
     * \brief Metoda unpause
     *
     * Metoda utuchamiająca grę, ustawia pole gameActive na true.
     */
    void unpause();
    /*!
     * \brief Metoda isGameActive
     *
     * Zwraca informację o tym, czy gra jest aktywna.
     * \return true jeżeli gra jest aktywna, false jeżeli gra jest zatrzymana.
     */
    bool isGameActive();
    /*!
     * \brief Metoda nextStep
     *
     * Metoda wywołująca metodę nextLogicStep zależnie od tego, czy gra jest aktywna.
     * Wywołuje również narysowanie odpowiedniego stanu planszy na ekranie gry.
     * Jest też odpowiedzialna za ciągłość działąnia gry.
     * \param gameWindow obiekt klasy GameWindow.
     * \param aging parametr zawierający informację, czy komórki mają się starzeć
     */
    void nextStep(GameWindow *gameWindow, bool aging);

private:
    /*!
     * \brief Pole gameActive
     *
     * Pole zawierające informacje czy gra jest uruchomiona.
     */
    bool gameActive;
    /*!
     * \brief Pole columns
     *
     * Pole zawierające informację o ilości kolumn na planszy.
     */
    short columns;
    /*!
     * \brief Pole rows
     *
     * Pole zawierające informację o ilości wierszy na planszy.
     */
    short rows;
};

#endif // GAMELOGIC_H
