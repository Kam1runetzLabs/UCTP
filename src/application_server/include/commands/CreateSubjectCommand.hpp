#ifndef INCLUDE_CREATESUBJECTCOMMAND_HPP_
#define INCLUDE_CREATESUBJECTCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class CreateSubjectCommand {
 public:
  CreateSubjectCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_CREATESUBJECTCOMMAND_HPP_
