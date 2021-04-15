#ifndef INCLUDE_DELETETEACHERCOMMAND_HPP_
#define INCLUDE_DELETETEACHERCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class DeleteTeacherCommand {
 public:
  DeleteTeacherCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_DELETETEACHERCOMMAND_HPP_
