//Copyright 2021 Kam1runetzLabs notsoserious2017@gmail.com

#ifndef INCLUDE_FASTCGIPROCESSOR_HPP_
#define INCLUDE_FASTCGIPROCESSOR_HPP_

#include "datatypes/HttpContext.hpp"
#include "ICGIProcessor.hpp"

class FastCGIProcessor : public ICGIProcessor {
 public:
  FastCGIProcessor();
  HttpContext ReadHttp() override;
  void WriteHttp(const HttpContext &httpRequest) override;
};

#endif  // INCLUDE_FASTCGIPROCESSOR_HPP_
