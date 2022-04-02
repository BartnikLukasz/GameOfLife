#include "cell.h"

Cell::Cell()
{
    alive = false;
}

Cell::~Cell() {

}

void Cell::getOlder() {

}

bool Cell::isAlive() {
    return this->alive;
}

void Cell::beBorn() {
    this->alive = true;
}

void Cell::die() {
    this->alive = false;
}
