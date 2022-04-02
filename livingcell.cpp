#include "livingcell.h"

LivingCell::LivingCell()
    : Cell()
{
    cellAge = CellAge();
}

short LivingCell::getAge() {
    return cellAge.getAge();
}

void LivingCell::setAge(short age) {
    cellAge.setAge(age);
}

void LivingCell::beBorn() {
    if(this->cellAge.getAge() == -1) {
        return;
    }
    this->alive = true;
    setAge(1);
}

void LivingCell::getOlder() {
    return;
}

void LivingCell::stayAlive(short currentAge) {
    this->alive = true;
    setAge(currentAge);
}
