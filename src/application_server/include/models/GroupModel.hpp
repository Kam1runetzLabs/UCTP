#ifndef INCLUDE_GROUPMODEL_HPP_
#define INCLUDE_GROUPMODEL_HPP_

#include "datatypes/ModelContext.hpp"

class GroupModel : public AbstractModel {
 public:
  GroupModel();
  void UpdateSelf(const ModelContext &modelResponse);
};

#endif  // INCLUDE_GROUPMODEL_HPP_
