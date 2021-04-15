#ifndef INCLUDE_STUDYSTREAMMODEL_HPP_
#define INCLUDE_STUDYSTREAMMODEL_HPP_

#include "datatypes/ModelContext.hpp"

class StudyStreamModel : public AbstractModel {
 public:
  StudyStreamModel();
  void UpdateSelf(const ModelContext &modelResponse);
};

#endif  // INCLUDE_STUDYSTREAMMODEL_HPP_
