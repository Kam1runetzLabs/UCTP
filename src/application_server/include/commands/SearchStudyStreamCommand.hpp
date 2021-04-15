#ifndef INCLUDE_SEARCHSTUDYSTREAMCOMMAND_HPP_
#define INCLUDE_SEARCHSTUDYSTREAMCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class SearchStudyStreamCommand {
 public:
  SearchStudyStreamCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_SEARCHSTUDYSTREAMCOMMAND_HPP_
