#include "../../core.hpp"

//---------------------------------------------------------------------------
logger& logger::instance() {
  static logger instance;
  return instance;
}
//---------------------------------------------------------------------------
const void logger::print_head() {
#ifndef PR_NAME
#define PR_NAME "template"
#endif
#ifndef PR_DESCRIPT
#define PR_DESCRIPT "project template"
#endif
#ifndef PR_VERSION
#define PR_VERSION "1.0.0"
#endif
#ifndef PR_VERSION_DATE
#define PR_VERSION_DATE __DATE__
#endif
#ifndef PROJECT_DEVELOPER
#define PROJECT_DEVELOPER "Dev"
#endif
#ifndef DEV_CONTACT
#define DEV_CONTACT "example@gmail.com"
#endif

  print_message("=========================");
  print_message("programm name: %s", PR_NAME);
  print_message("description: %s", PR_DESCRIPT);
  print_message("version: %s", PR_VERSION);
  print_message("build date: %s", PR_VERSION_DATE);
  print_message("developer: %s (%s)", PROJECT_DEVELOPER, DEV_CONTACT);
  print_message("=========================");
}
//---------------------------------------------------------------------------