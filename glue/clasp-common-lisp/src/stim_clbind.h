#include <fmt/format.h>
#include <clasp/clasp.h>
#include "stim.h"

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

namespace clasp_stim {

  int stim_main(const std::vector<std::string> args);
    }
