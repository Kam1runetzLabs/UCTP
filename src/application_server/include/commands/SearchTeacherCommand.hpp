#ifndef INCLUDE_SEARCHTEACHERCOMMAND_HPP_
#define INCLUDE_SEARCHTEACHERCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class SearchTeacherCommand {
 public:
  SearchTeacherCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_SEARCHTEACHERCOMMAND_HPP_
