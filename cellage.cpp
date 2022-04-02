#include "cellage.h"
#include "iostream"

CellAge::CellAge()
{
    age = 0;
}

void CellAge::addAge() {
    if(age < 5 && age >= 0) {
        age++;
    }
    else if(age == 5) {
        return;
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
    else if(age == 5) {
        this->age = -1;
    }
    else {
       this-> age = 0;
    }
}
