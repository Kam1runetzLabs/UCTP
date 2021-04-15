#ifndef INCLUDE_SUBJECTMODEL_HPP_
#define INCLUDE_SUBJECTMODEL_HPP_

#include "datatypes/ModelContext.hpp"

class SubjectModel : public AbstractModel {
 public:
  SubjectModel();
  void UpdateSelf(const ModelContext &modelResponse);
};

#endif  // INCLUDE_SUBJECTMODEL_HPP_
