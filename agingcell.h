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
     * \brief Destruktor klasy AgingCell
     *
     * Podstawowy destruktor
     */
    virtual ~AgingCell();
    /*!
     * \brief Metoda getOlder
     *
     * Implementuje funkcjonalność starazenia się komórki. Nadpisuje metodę wirtualną z klasy Cell, dodając zwiększanie się wieku komórki.
     */
    virtual void getOlder();
};

#endif // AGINGCELL_H
