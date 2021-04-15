// Copyright 2021 Kam1runetzLabs notsoserious2017@gmail.com

#ifndef INCLUDE_HTTPCONTEXT_HPP_
#define INCLUDE_HTTPCONTEXT_HPP_

#include <string>

union HttpContext {
 public:
  enum HttpMethod { Get, Post };

  struct HttpRequest {
    HttpMethod Method;
    std::string Url;
    std::string Body;
    std::string Headers;
  };

  struct HttpResponse {
    std::string Status;
    std::string Date;
    std::string Server;
    std::string ContentType;
    size_t ContentLength;
    std::string Body;
  };

  HttpRequest Request;
  HttpResponse Response;
};

#endif  // INCLUDE_HTTPCONTEXT_HPP_
