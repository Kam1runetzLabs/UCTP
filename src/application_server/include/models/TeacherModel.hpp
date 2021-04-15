#ifndef INCLUDE_TEACHERMODEL_HPP_
#define INCLUDE_TEACHERMODEL_HPP_

#include "datatypes/ModelContext.hpp"

class TeacherModel : public AbstractModel {
 public:
  TeacherModel();
  void UpdateSelf(const ModelContext &modelResponse);
};

#endif  // INCLUDE_TEACHERMODEL_HPP_
