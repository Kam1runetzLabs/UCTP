#ifndef INCLUDE_UPDATESUBJECTCOMMAND_HPP_
#define INCLUDE_UPDATESUBJECTCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class UpdateSubjectCommand {
 public:
  UpdateSubjectCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_UPDATESUBJECTCOMMAND_HPP_
