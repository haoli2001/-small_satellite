#include "gdata.h"

Gdata::Gdata()
{
    sem1 = new QSemaphore();
    sem2 = new QSemaphore();
    gNum = 0;
}

Gdata::~Gdata()
{
    delete sem1;
    delete sem2;
}
