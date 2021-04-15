#ifndef INCLUDE_DELETEGROUPCOMMAND_HPP_
#define INCLUDE_DELETEGROUPCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class DeleteGroupCommand {
 public:
  DeleteGroupCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_DELETEGROUPCOMMAND_HPP_
