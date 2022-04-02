#ifndef AGINGCELL_H
#define AGINGCELL_H

#include "cell.h"


class AgingCell : public Cell
{
public:
    AgingCell();
    short getAge();
    void getOlder();
    void stayAlive(short currentAge);
    void beBorn();

private:
    CellAge cellAge;
    void setAge(short age);
};

#endif // AGINGCELL_H
