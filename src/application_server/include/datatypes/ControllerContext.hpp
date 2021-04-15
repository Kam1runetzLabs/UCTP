// Copyright 2021 Kam1runetzLabs notsoserious2017@gmail.com

#ifndef INCLUDE_CONTROLLERCONTEXT_HPP_
#define INCLUDE_CONTROLLERCONTEXT_HPP_

#include <string>
#include <nlohmann/json.hpp>

union ControllerContext {
 public:
  enum StatusCodes {
    Ok,
    ControllerError,
    ModelError,
    DataError
  };

  enum HttpMethod { Get, Post };

  struct ControllerRequest {
    HttpMethod Method;
    nlohmann::json RequestBody;
  };

  struct ControllerResponse {
    StatusCodes Status;
    nlohmann::json ResponseBody;
  };

  ControllerRequest Request;
  ControllerResponse Response;
};

#endif  // INCLUDE_CONTROLLERCONTEXT_HPP_
