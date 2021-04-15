// Copyright 2021 Kam1runetzLabs notsoserious2017@gmail.com

#ifndef INCLUDE_UCTPVIEW_HPP_
#define INCLUDE_UCTPVIEW_HPP_

#include <memory>

#include "AbstractView.hpp"
#include "controllers/IControllerCommandRouter.hpp"
#include "datatypes/ControllerContext.hpp"
#include "tools/ICGIProcessor.hpp"

class UCTPView : public AbstractView {
 public:
  UCTPView(std::shared_ptr<ICGIProcessor> cgiProc,
           std::shared_ptr<IControllerCommandRouter> router,
           std::shared_ptr<Controller> controller);

  void Run() override;

  void SelfUpdate(const ControllerContext &controllerResponse) override;

 protected:
  std::shared_ptr<ICGIProcessor> m_CGIProcessor;
  std::shared_ptr<IControllerCommandRouter> m_ControllerCommandRouter;
  std::shared_ptr<Controller> m_Controller;
};

#endif  // INCLUDE_UCTPVIEW_HPP_
