#include <fmt/format.h>
#include <clasp/clasp.h>
#include "stim.h"

namespace clasp_stim {

  int stim_main(const std::vector<std::string> args){ // adapted from stim.pybind.cc
    std::vector<const char *> argv;
    argv.push_back("stim.main");
    for (const auto &arg : args) {
      argv.push_back(arg.c_str());
    }
    return stim::main(argv.size(), argv.data());
  }
}
