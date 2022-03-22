#include "agingcell.h"

AgingCell::AgingCell()
    : Cell()
{

}

void Cell::getOlder() {
    cellAge->addAge();
    if(getAge() == 0) {
        die();
    }
}

