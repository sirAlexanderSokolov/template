#include "core.hpp"
#include "includes/includes.hpp"

int main(int argc, char* argv[]) {
  // init
  auto& mediator = core::instance();
  // print header
  core::diag.print(CMSG001_);
  core::diag.print("=========================");
#ifdef PR_NAME
  core::diag.print("programm name: %s", PR_NAME);
#endif
#ifdef PR_DESCRIPT
  core::diag.print("description: %s", PR_DESCRIPT);
#endif
#ifdef PR_VERSION
  core::diag.print("version: %s", PR_VERSION);
#endif
#ifdef PR_VERSION_DATE
  core::diag.print("build date: %s", PR_VERSION_DATE);
#endif
#ifdef PR_DEVELOPER
  core::diag.print("developer: %s", PR_DEVELOPER);
#endif
#ifdef PR_COMMIT
  core::diag.print("commit: %s", PR_COMMIT);
#endif
  core::diag.print("=========================");
  // load options
  try {
    boost::program_options::options_description opt_description{"Options"};
    boost::program_options::variables_map opt_map{};

    opt_description.add_options()("help,h", "This screen")(
        "file,f",
        boost::program_options::value<std::string>()->default_value("file.bin"),
        "file to modify");

    boost::program_options::store(
        parse_command_line(argc, argv, opt_description), opt_map);

    if (opt_map.count("help"))
      std::cout << opt_description << '\n';
    if (opt_map.count("file"))
      std::cout << "filename: " << opt_map["file"].as<std::string>() << '\n';
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
  // logic
  return 0;
}