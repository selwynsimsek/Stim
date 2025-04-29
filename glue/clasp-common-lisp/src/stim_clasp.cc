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

    // 'Module-level' methods
    s.def("target-rec",&target_rec);
    s.def("target-inverse-target",&target_inv_target);
    s.def("target-inverse-integer",&target_inv_uint32_t);
    s.def("target-combiner",&stim::GateTarget::combiner);
    s.def("target-x-target",&target_x_target);
    s.def("target-x-integer",&target_x_uint32_t);
    s.def("target-y-target",&target_y_target);
    s.def("target-y-integer",&target_y_uint32_t);
    s.def("target-z-target",&target_z_target);
    s.def("target-z-integer",&target_z_uint32_t);
    s.def("target-pauli-string",&target_pauli_string);
    s.def("target-pauli-integer",&target_pauli_uint8_t);
    s.def("target-combined-paulis-string",&target_combined_paulis_string);
    s.def("target-combined-paulis-gate-targets",&target_combined_paulis_gate_targets);
    s.def("target-sweep-bit",&target_sweep_bit);
    s.def("main",&stim_main);

      fmt::print("Exited {}:{}:{}\n", __FILE__, __LINE__, __FUNCTION__);
  }
}; // namespace clasp_stim
