#include "timer.h"

Timer::Timer(QTime time, QLabel description)
{
    this->time = time;
    this->description = description.text();
}

Timer::Timer(QTime time, QString description)
{
    this->time = time;
    this->description = description;
}

QTime Timer::getTime()
{
    return time;
}

QString Timer::getDesc()
{
    return description;
}

void Timer::setDesc(QString newDesc)
{
    description = newDesc;
}
