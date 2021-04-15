#ifndef INCLUDE_SEARCHSUBJECTCOMMAND_HPP_
#define INCLUDE_SEARCHSUBJECTCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class SearchSubjectCommand {
 public:
  SearchSubjectCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_SEARCHSUBJECTCOMMAND_HPP_
