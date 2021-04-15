#ifndef INCLUDE_UPDATESTUDYSTREAMCOMMAND_HPP_
#define INCLUDE_UPDATESTUDYSTREAMCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class UpdateStudyStreamCommand {
 public:
  UpdateStudyStreamCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_UPDATESTUDYSTREAMCOMMAND_HPP_
