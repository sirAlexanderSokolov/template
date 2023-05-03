#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

// const

// types

// functions
#define now_time                                                    \
  std::chrono::duration_cast<std::chrono::nanoseconds>(             \
      std::chrono::high_resolution_clock::now().time_since_epoch()) \
      .count()

#define diag logger::instance()
#define print_error(...) logger::instance().print_err(__VA_ARGS__)
#define print_message(...) logger::instance().print_msg(__VA_ARGS__)
#define print_header() logger::instance().print_head()

#endif  // __CONSTANTS_H__