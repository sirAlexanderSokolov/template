#include "../core.hpp"

void load_options(int argc, char* argv[]) {
  // load options
  try {
    boost::program_options::options_description opt_description{"Options"};
    // clang-format off
    opt_description.add_options()
    (ocf_help, "Keys:")
    (ocf_version, "Programm info")
    (ocf_cfile, boost::program_options::value<const char*>()->default_value("settings.cfg"),CMSG001_);
    // clang-format on

    boost::program_options::store(
        parse_command_line(argc, argv, opt_description), opt_map);

    if (opt_map.count(oc_help))
      std::cout << opt_description << '\n';
    if (opt_map.count(oc_version))
      print_header();
    if (opt_map.count(oc_cfile))
      std::cout << "config file: " << o_file_path_cfg << '\n';
  } catch (const std::exception& e) {
    print_error("%s\n%s", CERR000_, e.what());
  }
}