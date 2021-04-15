#ifndef INCLUDE_CREATETEACHERCOMMAND_HPP_
#define INCLUDE_CREATETEACHERCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class CreateTeacherCommand {
 public:
  CreateTeacherCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_CREATETEACHERCOMMAND_HPP_
