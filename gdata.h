#ifndef GDATA_H
#define GDATA_H

#include <mutex>
#include <iostream>
#include <QSemaphore>

class Gdata
{
public:
    Gdata();
    ~Gdata();
    //qsemphore 信号量，控制同时访问特定资源的线程数量
    QSemaphore * sem1;
    QSemaphore * sem2;
    int gNum;
};

#endif // GDATA_H
