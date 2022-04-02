#ifndef CELL_H
#define CELL_H

#include "cellage.h"


class Cell
{
public:
    Cell();
    virtual ~Cell();
    bool isAlive();
    void beBorn();
    void die();
    virtual void getOlder();

protected:
    bool alive;

};

#endif // CELL_H
