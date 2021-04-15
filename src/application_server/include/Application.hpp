// Copyright 2021 Kam1runetzLabs notsoserious2017@gmail.com

#ifndef INCLUDE_APPLICATION_HPP_
#define INCLUDE_APPLICATION_HPP_

#include <map>
#include <memory>

#include "controllers/Controller.hpp"
#include "views/AbstractView.hpp"

class AbstractModel;

class Application {
 public:
  Application(int argc, char *argv[]);

  void SetView(AbstractView *view);

  void PostModel(const std::string &id, AbstractModel *model);

  void Run();

 private:
  std::shared_ptr<Controller> m_Controller;
  std::shared_ptr<AbstractView> m_View;
  std::map<std::string,std::shared_ptr<AbstractModel>> m_Models;
};

#endif  // INCLUDE_APPLICATION_HPP_
