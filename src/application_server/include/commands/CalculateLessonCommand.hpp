#ifndef INCLUDE_CALCULATELESSONCOMMAND_HPP_
#define INCLUDE_CALCULATELESSONCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class CalculateLessonCommand {
 public:
  CalculateLessonCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_CALCULATELESSONCOMMAND_HPP_
