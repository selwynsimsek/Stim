// Clasp bindings for Stim.

#include <fmt/format.h>
#include <clasp/clasp.h>
#include "stim.h"
#include "stim_clbind.h"

PACKAGE_USE("COMMON-LISP");

NAMESPACE_PACKAGE_ASSOCIATION(clasp_stim, ClaspStimPkg, "STIM");

//CLBIND_TRANSLATE_SYMBOL_TO_ENUM(stim::SampleFormat, clasp_stim::_sym_STARsampleFormatTranslatorSTAR );

namespace clasp_stim {

  extern "C" void startup_clasp_extension() {
    using namespace clbind;
    fmt::print("Entered {}:{}:{}\n", __FILE__, __LINE__, __FUNCTION__);
    package_ s(ClaspStimPkg);
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
    // TODO pybind_read_write

    //s.def("read-shot-data-file",&read_shot_data_file);
    //s.def("write-shot-data-file",&write_shot_data_file);

    //core::Symbol_sp y = core::lisp_intern("*SAMPLE-FORMAT-TRANSLATOR*","STIM");
    //y->exportYourself();

    // expose classes

    // dem_sampler
    class_<DemSampler<MAX_BITWORD_WIDTH>>(s,"dem-sampler");
    // TODO compiled detector sampler (needs its own class)
    //class_<CompiledDetectorSampler>(s,"compiled-detector-sampler");
    // TODO compiled measurement sampler (needs its own class)
    //class_<CompiledMeasurementSampler>(s,"compiled-detector-sampler");
    // TODO _compiled_m2d_converter
    // pauli_string
    class_<FlexPauliString>(s,"flex-pauli-string")
      .def_constructor("make-flex-pauli-string",constructor<uint32_t>()) // TODO fix size_t
      .def("flex-pauli-string-str",&FlexPauliString::str)
      .def("flex-pauli-string-phase",&FlexPauliString::get_phase)
      .def("flex-pauli-string+",&FlexPauliString::operator+)
      .def("flex-pauli-string+=",&FlexPauliString::operator+=)
      //.def("flex-pauli-string*-complex",(FlexPauliString(*)(std::complex<float>)) &FlexPauliString::operator*)
      //.def("flex-pauli-string*-flex-pauli-string",(FlexPauliString(*)(FlexPauliString&))&FlexPauliString::operator)
      .def("flex-pauli-string/",&FlexPauliString::operator/)
      //.def("flex-pauli-string*=-complex",(FlexPauliString(*)(std::complex<float>))&FlexPauliString::operator*=)
      //.def("flex-pauli-string*=-flex-pauli-string",(FlexPauliString(*)(FlexPauliString&))&FlexPauliString::operator*=)
      .def("flex-pauli-string/=",&FlexPauliString::operator/=)
      .def("flex-pauli-string-equal-p",&FlexPauliString::operator==)
      .def("flex-pauli-string-not-equal-p",&FlexPauliString::operator!=);
    s.def("pauli-string-from-text",&flex_pauli_from_text);

    // circuit_gate_target
    using namespace stim;
    class_<GateTarget>(s,"gate-target")
      .def("rec-offset",&GateTarget::rec_offset)
      .def("has-qubit-value-p",&GateTarget::has_qubit_value)
      .def("combiner-p",&GateTarget::is_combiner)
      .def("x-target-p",&GateTarget::is_x_target)
      .def("y-target-p",&GateTarget::is_y_target)
      .def("z-target-p",&GateTarget::is_z_target)
      .def("inverted-result-target-p",&GateTarget::is_inverted_result_target)
      .def("measurement-record-target-p",&GateTarget::is_measurement_record_target)
      .def("qubit-target-p",&GateTarget::is_qubit_target)
      .def("sweep-bit-target-p",&GateTarget::is_sweep_bit_target)
      .def("classical-bit-target-p",&GateTarget::is_classical_bit_target)
      .def("pauli-target-p",&GateTarget::is_pauli_target)
      .def("gate-target-qubit-value",&GateTarget::qubit_value)
      .def("gate-target-value",&GateTarget::value)
      .def("gate-target-equal-p",&GateTarget::operator==)
      .def("gate-target-not-equal-p",&GateTarget::operator!=)
      .def("gate-target-<",&GateTarget::operator<)
      .def("gate-target-str",&GateTarget::str)
      .def("gate-target-repr",&GateTarget::repr)
      .def("gate-target-pauli-type",&GateTarget::pauli_type)
      .def("target-str",&GateTarget::target_str);
    s.def("gate-target-from-string",&gate_target_from_target_str);
      fmt::print("Exited {}:{}:{}\n", __FILE__, __LINE__, __FUNCTION__);
  }
}; // namespace clasp_stim
