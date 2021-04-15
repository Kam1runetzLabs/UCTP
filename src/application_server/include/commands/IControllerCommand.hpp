//Copyright 2021 Kam1runetzLabs notsoserious2017@gmail.com

#ifndef INCLUDE_ICONTROLLERCOMMAND_HPP_
#define INCLUDE_ICONTROLLERCOMMAND_HPP_

class IControllerCommand {
 public:
  virtual ~IControllerCommand() = default;
  virtual void Execute() = 0;
};

#endif  // INCLUDE_ICONTROLLERCOMMAND_HPP_
