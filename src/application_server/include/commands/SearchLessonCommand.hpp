#ifndef INCLUDE_SEARCHLESSONCOMMAND_HPP_
#define INCLUDE_SEARCHLESSONCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class SearchLessonCommand {
 public:
  SearchLessonCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_SEARCHLESSONCOMMAND_HPP_
