#ifndef TIMETABLECONTROLLER_H
#define TIMETABLECONTROLLER_H

#include "applicationcontroller.h"

class T_CONTROLLER_EXPORT TimetableController : public ApplicationController {
  Q_OBJECT
 public:
  TimetableController() : ApplicationController() {}

 public slots:
  void index();
  void show(const QString &id);
  void create();
  void removeAll();
};

#endif  // TIMETABLECONTROLLER_H
