#ifndef INCLUDE_CREATEAUDITORYCOMMAND_HPP_
#define INCLUDE_CREATEAUDITORYCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class CreateAuditoryCommand {
 public:
  CreateAuditoryCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_CREATEAUDITORYCOMMAND_HPP_
