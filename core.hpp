#ifndef __CORE_H__
#define __CORE_H__
#pragma once

#include "includes/includes.hpp"
#include "lib/lib_logger/logger.hpp"

class core {
 private:
  /* data */
 protected:
  core() = default;
  core(core const&) = delete;
  core& operator=(core const&) = delete;

 public:
  ~core() = default;
  inline static logger& diag = logger::instance();

  static core& instance() {
    static core instance;
    return instance;
  };
};

#endif  // __CORE_H__