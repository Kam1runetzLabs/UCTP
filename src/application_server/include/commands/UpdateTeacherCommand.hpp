#ifndef INCLUDE_UPDATETEACHERCOMMAND_HPP_
#define INCLUDE_UPDATETEACHERCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class UpdateTeacherCommand {
 public:
  UpdateTeacherCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_UPDATETEACHERCOMMAND_HPP_
