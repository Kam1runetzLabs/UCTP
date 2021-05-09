#ifndef GROUPCONTROLLER_H
#define GROUPCONTROLLER_H

#include "applicationcontroller.h"

class T_CONTROLLER_EXPORT GroupController : public ApplicationController {
  Q_OBJECT
 public:
  GroupController() : ApplicationController() {}

 public slots:
  void index();
  void show(const QString &id);
  void create();
  void save(const QString &id);
  void remove(const QString &id);
};

#endif  // GROUPCONTROLLER_H
