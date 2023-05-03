#ifndef __UTILITY_H__
#define __UTILITY_H__
#pragma once

#include "includes.hpp"
//---------------------------------------------------------------------------
// LOAD OPTIONS
//---------------------------------------------------------------------------
static boost::program_options::variables_map opt_map{};

#define oc_cfile "config"
#define ocf_cfile "config,c"
#define oc_help "help"
#define ocf_help "help,h"
#define oc_version "version"
#define ocf_version "version,f"

#define o_file_path_cfg opt_map[oc_cfile].as<const char*>()

void load_options(int argc, char* argv[]);
//---------------------------------------------------------------------------
#endif  // __UTILITY_H__