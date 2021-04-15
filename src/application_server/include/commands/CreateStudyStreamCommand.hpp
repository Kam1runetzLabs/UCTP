#ifndef INCLUDE_CREATESTUDYSTREAMCOMMAND_HPP_
#define INCLUDE_CREATESTUDYSTREAMCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class CreateStudyStreamCommand {
 public:
  CreateStudyStreamCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_CREATESTUDYSTREAMCOMMAND_HPP_
