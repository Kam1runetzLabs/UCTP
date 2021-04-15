#ifndef INCLUDE_DELETESTUDYSTREAMCOMMAND_HPP_
#define INCLUDE_DELETESTUDYSTREAMCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class DeleteStudyStreamCommand {
 public:
  DeleteStudyStreamCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_DELETESTUDYSTREAMCOMMAND_HPP_
