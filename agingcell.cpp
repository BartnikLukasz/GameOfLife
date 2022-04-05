#include "agingcell.h"

AgingCell::AgingCell()
    : Cell()
{
    cellAge = CellAge();
}

short AgingCell::getAge() {
    return cellAge.getAge();
}

void AgingCell::setAge(short age) {
    cellAge.setAge(age);
}

void AgingCell::beBorn() {
    if(this->cellAge.getAge() == -1) { //Jeżeli wiek -1, to znaczy że komórka umarła ze starości i ma się w tej chwili nie rodzić.
        return;
    }
    this->alive = true;
    setAge(1);
}

void AgingCell::getOlder() {
    cellAge.addAge();
    if(getAge() == 0) {
        die();
    }
}

void AgingCell::stayAlive(short currentAge) {
    this->alive = true;
    setAge(currentAge);
}

