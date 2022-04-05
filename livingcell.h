#ifndef LIVINGCELL_H
#define LIVINGCELL_H

#include "cell.h"

/*!
 * \brief Klasa LivingCell
 *
 * Klasa LivingCell dziedziczy po klasie Cell i rozszerza ją o posiadanie wieku. Jest niemal identyczna do klasy AgingCell, co umożliwia łatwą konwersję między nimi.
 * Nadpisuje metodę getOlder, w której nie postarza komórki, dzięki czemu wyłącza funkcjonalność starzenia się. Przy wyborze opcji nie starzenia się, obiekt klasy AgingCell
 * konwertowany jest na obiekt klasy LivingCell i na nim wywoływana jest odpowiednia metoda. Następnie odwraca się konwersję i program działa dalej.
 */
class LivingCell : public Cell
{
public:
    /*!
     * \brief Konstruktor klasy LivingCell
     *
     * Poza tworzeniem obiektu klasy LivingCell przypisuje on również polu cellAge nowy obiekt klasy CellAge.
     */
    LivingCell();
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
     * Implementuje funkcjonalność starazenia się komórki. Nadpisuje metodę wirtualną z klasy Cell, w przeciwieństwie do klasy AgingCell nie postarza komórki.
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

#endif // LIVINGCELL_H
