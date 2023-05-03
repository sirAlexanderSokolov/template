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

  static logger& instance();
  static const void print_head();

  template <typename... args>
  static const void print_msg(const char* format, const args&... arguments) {
    std::cout << "\033[34;1m" << (boost::format(format) % ... % arguments)
              << "\033[0m\n";
  }

  template <typename... args>
  const void print_err(const char* format, const args&... arguments) {
    std::cerr << "\033[31;1m" << (boost::format(format) % ... % arguments)
              << "\033[0m\n";
  };
};
#endif  // __LOGGER_H__