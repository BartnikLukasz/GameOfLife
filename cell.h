#ifndef CELL_H
#define CELL_H

#include "cellage.h"

/*!
 * \brief Klasa Cell
 *
 * Jest klasą bazową, po której dziedziczą klasy AgingCell i LivingCell. Zawiera podstawowe pole oraz metody dotyczące życia komórki.
 */
class Cell
{
public:
    /*!
     * \brief Konstruktor klasy Cell
     *
     * Ustawia pole alive na wartość false
     */
    Cell();
    /*!
     * \brief Destruktor klasy Cell
     *
     * Podstawowy destruktor
     */
    virtual ~Cell();
    /*!
     * \brief Metoda isAlive
     *
     * Zwraca pole alive
     * \return true jeżeli komórka jest żywa, false jeżeli komórka jest martwa
     */
    bool isAlive();
    /*!
     * \brief Metoda getAge
     *
     * Zwraca wiek komórki pobrany z obiektu cellAge.
     * \return wiek komórki
     */
    short getAge();
    /*!
     * \brief Metoda beBorn
     *
     * Metoda 'rodząca' komórkę. Ustawia pole alive na true
     */
    void beBorn();
    /*!
     * \brief Metoda die
     *
     * Metoda 'uśmiercająca' komórkę. Ustawia pole alive na false
     */
    void die();
    /*!
     * \brief Metoda wirtualna getOlder
     *
     * Metoda wirtualna odpowiadająca za różne implementacje starzenia się komórki.
     */
    virtual void getOlder();
    /*!
     * \brief Metoda stayAlive
     *
     * Metoda pozwalająca na utrzymanie komórki przy życiu wraz z utrzymaniem jej wieku, poprzez ustawienie pola isAlive na true oraz ustawienie jej wieku.
     * \param[in] currentAge aktualny wiek komórki.
     */
    void stayAlive(short currentAge);

protected:
    /*!
     * \brief Pole alive
     *
     * Pole zawierające informacje czy dana komórka jest żywa czy martwa.
     */
    bool alive;
    /*!
     * \brief Pole cellAge
     *
     * Obiekt klasy CellAge, zawiera w sobie informację o wieku komórki oraz metody pozwalające nim mianipulować.
     */
    CellAge cellAge;
    /*!
     * \brief Metoda setAge
     *
     * Metoda pozwalająca na ustawienie wieku komórki zgodnie z podanym w parametrze.
     * \param[in] age wiek komórki do ustawienia.
     */
    void setAge(short age);
};

#endif // CELL_H
