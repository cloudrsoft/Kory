#ifndef CALENDAR_H
#define CALENDAR_H

#include <QDateTime>

#include <settings.h>

class Calendar
{
public:
    Calendar();

    void addCalendar(int num, QDateTime time, int type, QString event);
    void removeCalendar(int num);

    int getNumber(QString event, QDateTime time = QDateTime());
};

#endif // CALENDAR_H
