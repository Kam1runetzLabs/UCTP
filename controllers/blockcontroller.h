#ifndef BLOCKCONTROLLER_H
#define BLOCKCONTROLLER_H

#include "applicationcontroller.h"

class T_CONTROLLER_EXPORT BlockController : public ApplicationController {
  Q_OBJECT
 public:
  BlockController() : ApplicationController() {}

 public slots:
  void index();
  void show(const QString &id);
  void create();
  void save(const QString &id);
  void remove(const QString &id);
};

#endif  // BLOCKCONTROLLER_H
