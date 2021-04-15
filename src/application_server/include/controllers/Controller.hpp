//Copyright 2021 Kam1runetzLabs notsoserious2017@gmail.com

#ifndef INCLUDE_DEFAULTCOMMAND_ROUTER_HPP_
#define INCLUDE_DEFAULTCOMMAND_ROUTER_HPP_

#include <memory>

#include "commands/IControllerCommand.hpp"
#include "datatypes/ModelContext.hpp"

class AbstractView;

class Controller {
 public:
  Controller();
  void Execute(const std::shared_ptr<IControllerCommand> &command);
  void SetView(const std::shared_ptr<AbstractView> &view);
  void UpdateView(const ModelResponse &modelResponse);

 private:
  std::shared_ptr<AbstractView> m_View;
};

#endif  // INCLUDE_DEFAULTCOMMAND_ROUTER_HPP_
