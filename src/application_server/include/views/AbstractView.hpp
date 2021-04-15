// Copyright 2021 Kam1runetzLabs notsoserious2017@gmail.com

#ifndef INCLUDE_ABSTRACTVIEW_HPP_
#define INCLUDE_ABSTRACTVIEW_HPP_

#include <memory>

#include "controllers/IControllerCommandRouter.hpp"
#include "datatypes/ControllerContext.hpp"
#include "tools/ICGIProcessor.hpp"

class AbstractView {
 public:
  AbstractView(std::shared_ptr<ICGIProcessor> cgiProc,
               std::shared_ptr<IControllerCommandRouter> router,
               std::shared_ptr<Controller> controller);

  virtual ~AbstractView() = default;

  virtual void Run();

  virtual void SelfUpdate(const ControllerContext &controllerResponse) = 0;

 protected:
  std::shared_ptr<ICGIProcessor> m_CGIProcessor;
  std::shared_ptr<IControllerCommandRouter> m_ControllerCommandRouter;
  std::shared_ptr<Controller> m_Controller;
};

#endif  // INCLUDE_ABSTRACTVIEW_HPP_
