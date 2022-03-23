#include "cellage.h"

CellAge::CellAge()
{
    age = 0;
}

void CellAge::addAge() {
    if(age < 5 && age >= 0) {
        age++;
    }
    else {
        age = 0;
    }
}

short CellAge::getAge() {
    return age;
}

void CellAge::setAge(short age) {
    if(age < 5 && age >= 0) {
        this->age = age;
    }
    else {
        age = 0;
    }
}
