#include "cellage.h"
#include "iostream"

CellAge::CellAge()
{
    age = 0;
}

void CellAge::addAge() {
    if(age < 5 && age >= 0) { //W wieku od 0 do 5 komórka ma się starzeć
        age++;
    }
    else if(age == 5) { //Jeżeli komórka ma wiek równy 5, nie rób nic
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
    if(age < 5 && age >= 0) { //Dla wieku od 0 do 5 ustaw wiek
        this->age = age;
    }
    else if(age == 5) { //Dla wieku 5 ustaw wiek na -1, bo komórka umarła ze starości
        this->age = -1;
    }
    else {
       this-> age = 0;
    }
}
