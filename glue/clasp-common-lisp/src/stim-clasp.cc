// Clasp bindings for Stim.

#include <fmt/format.h>
#include <clasp/clasp.h>
#include "stim.h"

namespace clasp_stim {

  void hello_world(double x, double y) { fmt::print("Hello World! Did you know that {} + {} = {}?\n", x, y, x + y); }

  int stim_main(const std::vector<std::string> args){ // adapted from stim.pybind.cc
    std::vector<const char *> argv;
    argv.push_back("stim.main");
    for (const auto &arg : args) {
      argv.push_back(arg.c_str());
    }
    return stim::main(argv.size(), argv.data());
  }

  extern "C" void startup_clasp_extension() {
    using namespace clbind;
    using namespace stim;
    fmt::print("Entered {}:{}:{}\n", __FILE__, __LINE__, __FUNCTION__);
    package_ s("STIM", {}, {"COMMON-LISP"});
    s.def("hello-world", &hello_world, "(x y)"_ll, "Hello world that adds numbers."_docstring);
    // #include "stim/circuit/circuit.h"
    //s.def("add-saturate", &add_saturate, "(x y)"_ll, ""_docstring);
    //s.def("mul-saturate", &mul_saturate, "(x y)"_ll, ""_docstring);
    // class_<Circuit>(s,"circuit")
    //   .def_constructor("make-circuit",constructor<>(),"")
    //   .def_constructor("make-circuit-from-description",constructor<std::string>(),"")
    //   .def("circuit-string",&Circuit::str)
    //   .def("compute-stats",&Circuit::compute_stats)
    //   .def("append-from-file",&Circuit::append_from_file)
    //   .def("append-from-text",&Circuit::append_from_text)
    //   .def("clear",&Circuit::clear)
    //   ;

    // src/stim/py/stim.pybind.cc contains the pybind bindings.
    // The clbind bindings should follow this as closely as possible, as they form a documented API.
    // There are 28 classes exposed.
    // The problem is that a lot of them return pybind11::objects, whereas we would prefer to use c++/lisp
    // type translators.
    // Writing our own will be time consuming. Can the existing ones be adapted somehow?
    // Try importing only a few functions to begin with, like main().
    // Also, do a smallish class by hand.
    // Ambitious: use clasp to scrape the definitions?
    //class_<DemSampler<MAX_BITWORD_WIDTH>>(s,"dem-sampler");
    //class_<CompiledDetectorSampler>(s,"compiled-dem-sampler");
    //class_<CompiledMeasurementSampler>(s,"compiled-measurement-sampler");

    s.def("main",&stim_main);
      fmt::print("Exited {}:{}:{}\nMAX_BITWORD_WIDTH {}", __FILE__, __LINE__, __FUNCTION__,MAX_BITWORD_WIDTH);
  }
}; // namespace clasp_stim
