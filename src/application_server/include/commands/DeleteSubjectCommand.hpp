#ifndef INCLUDE_DELETESUBJECTCOMMAND_HPP_
#define INCLUDE_DELETESUBJECTCOMMAND_HPP_

#include "datatypes/HttpContext.hpp"
#include "models/ScheduleModel.hpp"

class DeleteSubjectCommand {
 public:
  DeleteSubjectCommand(ScheduleModel model, HttpContext httpRequest);
  void Execute();
};

#endif  // INCLUDE_DELETESUBJECTCOMMAND_HPP_
