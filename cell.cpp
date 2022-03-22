#include "cell.h"

Cell::Cell()
{
    alive = false;
    cellAge = new CellAge();
}

bool Cell::isAlive() {
    return this->alive;
}

short Cell::getAge() {
    return cellAge->getAge();
}

void Cell::beBorn() {
    this->alive = true;
    cellAge->addAge();
}

void Cell::die() {
    alive = false;
}
