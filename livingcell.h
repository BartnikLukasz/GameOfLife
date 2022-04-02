#ifndef LIVINGCELL_H
#define LIVINGCELL_H

#include "cell.h"

class LivingCell : public Cell
{
public:
    LivingCell();
    short getAge();
    void getOlder();
    void stayAlive(short currentAge);
    void beBorn();

private:
    CellAge cellAge;
    void setAge(short age);
};

#endif // LIVINGCELL_H
