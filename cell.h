#ifndef CELL_H
#define CELL_H

#include "cellage.h"



class Cell
{
public:
    Cell();
    bool isAlive();
    short getAge();
    void beBorn();
    void die();
    virtual void getOlder();

    void stayAlive(short currentAge);
private:
    bool alive;
    CellAge cellAge;
    void setAge(short age);
};

#endif // CELL_H
