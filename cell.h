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

private:
    bool alive;
    CellAge* cellAge;
};

#endif // CELL_H
