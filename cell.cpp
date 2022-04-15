#include "cell.h"

Cell::Cell()
{
    alive = false;
    cellAge = CellAge();
}

Cell::~Cell() {

}

void Cell::getOlder() {

}

bool Cell::isAlive() {
    return this->alive;
}

void Cell::beBorn() {
    if(this->cellAge.getAge() == -1) { //Jeżeli wiek -1, to znaczy że komórka umarła ze starości i ma się w tej chwili nie rodzić.
        return;
    }
    this->alive = true;
    setAge(1);
}

void Cell::stayAlive(short currentAge) {
    this->alive = true;
    setAge(currentAge);
}

void Cell::die() {
    this->alive = false;
}

short Cell::getAge() {
    return cellAge.getAge();
}

void Cell::setAge(short age) {
    cellAge.setAge(age);
}
