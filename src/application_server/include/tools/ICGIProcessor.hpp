//Copyright 2021 Kam1runetzLabs notsoserious2017@gmail.com

#ifndef INCLUDE_ICGIPROCESSOR_HPP_
#define INCLUDE_ICGIPROCESSOR_HPP_

#include "HttpContext.hpp"

class ICGIProcessor {
 public:
  virtual ~ICGIProcessor() = default;
  virtual HttpContext ReadHttp() = 0;
  virtual void WriteHttp(const HttpContext &httpResponse) = 0;
};

#endif  // INCLUDE_ICGIPROCESSOR_HPP_
