#ifndef AGINGCELL_H
#define AGINGCELL_H

#include "cell.h"

/*!
 * \brief Klasa AgingCell
 *
 * Klasa AgingCell dziedziczy po klasie Cell i rozszerza ją o posiadanie wieku oraz funkcjonalność starzenia się.
 * Jako pole posiada obiekt klasy CellAge oraz posiada funkcje pozwalające na manipulację tym obiektem.
 */
class AgingCell : public Cell
{
public:
    /*!
     * \brief Konstruktor klasy AgingCell
     *
     * Poza tworzeniem obiektu klasy AgingCell przypisuje on również polu cellAge nowy obiekt klasy CellAge.
     */
    AgingCell();
    /*!
     * \brief Metoda getAge
     *
     * Zwraca wiek komórki pobrany z obiektu cellAge.
     * \return wiek komórki
     */
    short getAge();
    /*!
     * \brief Metoda getOlder
     *
     * Implementuje funkcjonalność starazenia się komórki. Nadpisuje metodę wirtualną z klasy Cell, dodając zwiększanie się wieku komórki.
     */
    void getOlder();
    /*!
     * \brief Metoda stayAlive
     *
     * Metoda pozwalająca na utrzymanie komórki przy życiu wraz z utrzymaniem jej wieku, poprzez ustawienie pola isAlive na true oraz ustawienie jej wieku.
     * \param[in] currentAge aktualny wiek komórki.
     */
    void stayAlive(short currentAge);
    /*!
     * \brief Metoda beBorn
     *
     * Metoda 'rodząca' komórkę. Ustawia wiek komórki na 1. Nadpisuje metodę z klasy Cell.
     */
    void beBorn();

private:
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

#endif // AGINGCELL_H
