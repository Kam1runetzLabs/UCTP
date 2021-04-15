#ifndef INCLUDE_CREATEGROUPCOMMAND_HPP_
#define INCLUDE_CREATEGROUPCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class CreateGroupCommand {
 public:
  CreateGroupCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_CREATEGROUPCOMMAND_HPP_
