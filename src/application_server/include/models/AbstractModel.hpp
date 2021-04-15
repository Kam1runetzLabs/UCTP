// Copyright 2021 Kam1runetzLabs notsoserious2017@gmail.com

#ifndef INCLUDE_ABSTRACTMODEL_HPP_
#define INCLUDE_ABSTRACTMODEL_HPP_

#include "controllers/Controller.hpp"
#include "datatypes/ModelContext.hpp"

class AbstractModel {
 public:
  AbstractModel();

  virtual ~AbstractModel() = default;

  virtual void UpdateSelf(const ModelContext &modelResponse) = 0;

  void SetController(const std::shared_ptr<Controller> &controller);

 private:
  std::shared_ptr<Controller> m_Controller;
};

#endif  // INCLUDE_ABSTRACTMODEL_HPP_