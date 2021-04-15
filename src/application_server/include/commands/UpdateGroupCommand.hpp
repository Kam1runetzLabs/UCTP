#ifndef INCLUDE_UPDATEGROUPCOMMAND_HPP_
#define INCLUDE_UPDATEGROUPCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class UpdateGroupCommand {
 public:
  UpdateGroupCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_UPDATEGROUPCOMMAND_HPP_
