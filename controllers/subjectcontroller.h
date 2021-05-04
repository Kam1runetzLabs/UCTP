#ifndef SUBJECTCONTROLLER_H
#define SUBJECTCONTROLLER_H

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT SubjectController : public ApplicationController
{
    Q_OBJECT
public:
    SubjectController() : ApplicationController() {}

public slots:
    void index();
    void show(const QString &id);
    void create();
    void save(const QString &id);
    void remove(const QString &id);
};

#endif // SUBJECTCONTROLLER_H
