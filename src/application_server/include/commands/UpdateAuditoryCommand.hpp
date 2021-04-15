#ifndef INCLUDE_UPDATEAUDITORYCOMMAND_HPP_
#define INCLUDE_UPDATEAUDITORYCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class UpdateAuditoryCommand {
 public:
  UpdateAuditoryCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_UPDATEAUDITORYCOMMAND_HPP_
