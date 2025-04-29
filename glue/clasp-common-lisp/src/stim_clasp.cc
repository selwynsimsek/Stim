// Clasp bindings for Stim.

#include <fmt/format.h>
#include <clasp/clasp.h>
#include "stim.h"
#include "stim_clbind.h"

namespace clasp_stim {

  extern "C" void startup_clasp_extension() {
    using namespace clbind;
    fmt::print("Entered {}:{}:{}\n", __FILE__, __LINE__, __FUNCTION__);
    package_ s("STIM", {}, {"COMMON-LISP"});
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

      fmt::print("Exited {}:{}:{}\n", __FILE__, __LINE__, __FUNCTION__);
  }
}; // namespace clasp_stim
