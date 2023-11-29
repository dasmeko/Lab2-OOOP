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

