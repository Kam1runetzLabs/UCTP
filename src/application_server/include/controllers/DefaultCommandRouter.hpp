//Copyright 2021 Kam1runetzLabs notsoserious2017@gmail.com

#ifndef INCLUDE_DEFAULTCOMMAND_ROUTER_HPP_
#define INCLUDE_DEFAULTCOMMAND_ROUTER_HPP_

#include <string>
#include <map>
#include <memory>

#include "datatypes/HttpContext.hpp"
#include "IControllerCommand.hpp"
#include "IControllerCommandRouter.hpp"

class AbstractModel;

class DefaultCommandRouter : public IControllerCommandRouter {
 public:
  DefaultCommandRouter(std::map<std::string, std::shared_ptr<AbstractModel>> &modelsMapRef);
  std::shared_ptr<IControllerCommand> Route(const HttpContext &httpRequest) override;
 private:
  std::map<std::string, std::shared_ptr<AbstractModel>> &m_ModelsMapRef;
};

#endif  // INCLUDE_DEFAULTCOMMAND_ROUTER_HPP_
