//Copyright 2021 Kam1runetzLabs notsoserious2017@gmail.com

#ifndef INCLUDE_ICONTROLLERCOMMANDROUTER_HPP_
#define INCLUDE_ICONTROLLERCOMMANDROUTER_HPP_

#include <memory>

#include "datatypes/HttpContext.hpp"
#include "IControllerCommand.hpp"

class IControllerCommandRouter {
 public:
  virtual ~IControllerCommandRouter() = default;
  virtual std::shared_ptr<IControllerCommand> Route(const HttpContext &httpRequest) = 0;
};

#endif  // INCLUDE_ICONTROLLERCOMMANDROUTER_HPP_
