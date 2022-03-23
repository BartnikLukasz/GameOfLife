#include "cell.h"

Cell::Cell()
{
    alive = false;
    cellAge = CellAge();
}

bool Cell::isAlive() {
    return this->alive;
}

short Cell::getAge() {
    return cellAge.getAge();
}

void Cell::beBorn() {
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

void Cell::setAge(short age) {
    cellAge.setAge(age);
}
