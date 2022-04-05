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

protected:
    /*!
     * \brief Pole alive
     *
     * Pole zawierające informacje czy dana komórka jest żywa czy martwa.
     */
    bool alive;

};

#endif // CELL_H
