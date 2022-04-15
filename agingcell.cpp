#include "agingcell.h"

AgingCell::AgingCell()
    : Cell()
{

}

AgingCell::~AgingCell() {

}


void AgingCell::getOlder() {
    cellAge.addAge();
    if(getAge() == 0) {
        die();
    }
}


