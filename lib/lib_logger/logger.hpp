#ifndef __LOGGER_H__
#define __LOGGER_H__
#pragma once

#include "../../includes/includes.hpp"

class logger {
 protected:
  logger() = default;
  logger(logger const&) = delete;
  logger& operator=(logger const&) = delete;

 public:
  ~logger() = default;

  static logger& instance() {
    static logger instance;
    return instance;
  };

  template <typename... args>
  static const void print(const char* format, const args&... arguments) {
    std::cout << "\033[34;1m" << (boost::format(format) % ... % arguments)
              << "\033[0m\n";
  };
};

#endif  // __LOGGER_H__