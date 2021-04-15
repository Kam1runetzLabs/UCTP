#ifndef INCLUDE_DELETEAUDITORYCOMMAND_HPP_
#define INCLUDE_DELETEAUDITORYCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class DeleteAuditoryCommand {
 public:
  DeleteAuditoryCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_DELETEAUDITORYCOMMAND_HPP_
