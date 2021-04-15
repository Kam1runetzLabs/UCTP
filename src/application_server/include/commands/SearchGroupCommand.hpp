#ifndef INCLUDE_SEARCHGROUPCOMMAND_HPP_
#define INCLUDE_SEARCHGROUPCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class SearchGroupCommand {
 public:
  SearchGroupCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_SEARCHGROUPCOMMAND_HPP_
