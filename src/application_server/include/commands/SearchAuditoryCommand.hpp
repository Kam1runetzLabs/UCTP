#ifndef INCLUDE_SEARCHAUDITORYCOMMAND_HPP_
#define INCLUDE_SEARCHAUDITORYCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class SearchAuditoryCommand {
 public:
  SearchAuditoryCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_SEARCHAUDITORYCOMMAND_HPP_
