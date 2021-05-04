#ifndef CLASSROOMCONTROLLER_H
#define CLASSROOMCONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT ClassroomController : public ApplicationController
{
    Q_OBJECT
public:
    ClassroomController() : ApplicationController() {}

public slots:
    void index();
    void show(const QString &id);
    void create();
    void save(const QString &id);
    void remove(const QString &id);
};

#endif // CLASSROOMCONTROLLER_H
