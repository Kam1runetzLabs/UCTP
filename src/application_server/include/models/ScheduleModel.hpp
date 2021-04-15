#ifndef INCLUDE_SCHEDULEMODEL_HPP_
#define INCLUDE_SCHEDULEMODEL_HPP_

#include "datatypes/ModelContext.hpp"

class ScheduleModel : public AbstractModel {
 public:
  ScheduleModel();
  void UpdateSelf(const ModelContext &modelResponse);
};

#endif  // INCLUDE_SCHEDULEMODEL_HPP_
