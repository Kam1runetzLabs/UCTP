#ifndef TEACHERCONTROLLER_H
#define TEACHERCONTROLLER_H

#include "applicationcontroller.h"

class T_CONTROLLER_EXPORT TeacherController : public ApplicationController {
  Q_OBJECT
 public:
  TeacherController() : ApplicationController() {}

 public slots:
  void index();
  void show(const QString &id);
  void create();
  void save(const QString &id);
  void remove(const QString &id);
};

#endif  // TEACHERCONTROLLER_H
