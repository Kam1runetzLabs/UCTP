#ifndef TIMESLOTCONTROLLER_H
#define TIMESLOTCONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT TimeSlotController : public ApplicationController
{
    Q_OBJECT
public:
    TimeSlotController() : ApplicationController() {}

public slots:
    void index();
    void show(const QString &id);
    void create();
    void save(const QString &id);
    void remove(const QString &id);
};

#endif // TIMESLOTCONTROLLER_H
