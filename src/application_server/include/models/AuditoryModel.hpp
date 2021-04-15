#ifndef INCLUDE_AUDITORYMODEL_HPP_
#define INCLUDE_AUDITORYMODEL_HPP_

#include "datatypes/ModelContext.hpp"

class AuditoryModel : public AbstractModel {
 public:
  AuditoryModel();
  void UpdateSelf(const ModelContext &modelResponse);
};

#endif  // INCLUDE_AUDITORYMODEL_HPP_
