#ifndef CELLAGE_H
#define CELLAGE_H

/*!
 * \brief Klasa CellAge
 *
 * Zawiera informacje o wieku komórki oraz metody pozwalające na manipulowanie nim.
 */
class CellAge
{
public:
    /*!
     * \brief Konstruktor klasy CellAge
     *
     * Ustawia wiek na 0
     */
    CellAge();
    /*!
     * \brief Metoda addAge
     *
     * Zwiększa wiek komórki o 1.
     */
    void addAge();
    /*!
     * \brief Metoda getAge
     *
     * Zwraca aktualny wiek komórki.
     * \return wiek komórki
     */
    short getAge();
    /*!
     * \brief Metoda setAge
     *
     * Metoda pozwalająca ustawić wiek komórki według parametru
     * \param age żądany wiek komórki
     */
    void setAge(short age);
private:
    /*!
     * \brief Pole age
     *
     * Przechowuje informacje o wieku komórki.
     */
    short age;
};

#endif // CELLAGE_H
