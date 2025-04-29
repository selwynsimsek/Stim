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
    using namespace stim;
    fmt::print("Entered {}:{}:{}\n", __FILE__, __LINE__, __FUNCTION__);
    package_ s(ClaspStimPkg);
    // We imitate the API laid out in src/stim/py/ystim.pybind.cc.
    // Not everything will be possible or useful to port, but most of it will.
    // We proceed by porting the module exposing code in order, on line 573 starting
    // PYBIND11_MODULE(STIM_PYBIND11_MODULE_NAME, m) {.
    // Parts of comments within square brackets are intended to illustrate the equivalent part of pybind that is being ported.

    // With pybind, classes are registered before functions/methods. This is not necessary with clbind.

    // We start by doing the top level function definitions:

    // 'Module-level' methods [start top_level(m)]
    // TODO Add comments. more complicated lambda list with optional parameter for 'invert'?
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
    // [end top_level]

    // [start pybind_read_write] TODO Implement these
    //s.def("read-shot-data-file",&read_shot_data_file);
    //s.def("write-shot-data-file",&write_shot_data_file);
    // [end pybind_read_write]

    // We start by exposing all the classes that are not in the pybind namespace (it would be problematic to build with pybind and we ultimately don't need it.)
    // It is intended (TODO) that those classes which are in the pybind namespace will be themselves ported to clbind and exposed here. There are nine of them.
    // [start class definitions]
    // TODO Add methods
    class_<DemSampler<MAX_BITWORD_WIDTH>>(s,"compiled-dem-sampler");
    // TODO compiled detector sampler (python)
    //class_<CompiledDetectorSampler>(s,"compiled-detector-sampler");
    // TODO compiled measurement sampler (python)
    //class_<CompiledMeasurementSampler>(s,"compiled-detector-sampler");
    // TODO _compiled_m2d_converter (python)
    // pauli_string
    class_<FlexPauliString>(s,"pauli-string")
      .def_constructor("make-pauli-string",constructor<uint32_t>()) // TODO fix size_t
      .def("pauli-string-str",&FlexPauliString::str)
      .def("pauli-string-phase",&FlexPauliString::get_phase)
      .def("pauli-string+",&FlexPauliString::operator+)
      .def("pauli-string+=",&FlexPauliString::operator+=) // TODO Fix exposing of overloaded methods
      //.def("flex-pauli-string*-complex",(FlexPauliString(*)(std::complex<float>)) &FlexPauliString::operator*)
      //.def("flex-pauli-string*-flex-pauli-string",(FlexPauliString(*)(FlexPauliString&))&FlexPauliString::operator)
      .def("pauli-string/",&FlexPauliString::operator/)
      //.def("flex-pauli-string*=-complex",(FlexPauliString(*)(std::complex<float>))&FlexPauliString::operator*=)
      //.def("flex-pauli-string*=-flex-pauli-string",(FlexPauliString(*)(FlexPauliString&))&FlexPauliString::operator*=)
      .def("pauli-string/=",&FlexPauliString::operator/=)
      .def("pauli-string-equal-p",&FlexPauliString::operator==)
      .def("pauli-string-not-equal-p",&FlexPauliString::operator!=);
    s.def("pauli-string-from-text",&flex_pauli_from_text);

    // PauliStringIterator
     class_<PauliStringIterator<MAX_BITWORD_WIDTH>>(s,"pauli-string-iterator")
        .def_constructor("make-pauli-string-iterator",constructor<uint32_t,uint32_t,uint32_t,bool, bool, bool>())
      .def("pauli-string-iterator-next",&PauliStringIterator<MAX_BITWORD_WIDTH>::iter_next);
     s.def("pauli-string-iterator-current",&pauli_iterator_get_current);

     // Tableau
     class_<Tableau<MAX_BITWORD_WIDTH>>(s,"tableau")
       ;
     // TableauIterator
     class_<TableauIterator<MAX_BITWORD_WIDTH>>(s,"tableau-iterator")
       ;
    // circuit_gate_target
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
      // GateData
      class_<Gate>(s,"gate")
        ;
      // CircuitInstruction (python)
      // CircuitRepeatBlock (python)
      // Circuit
       class_<Circuit>(s,"circuit")
         .def_constructor("make-circuit",constructor<>(),"")
         .def_constructor("make-circuit-from-description",constructor<std::string>(),"")
         .def("circuit-string",&Circuit::str)
         .def("compute-stats",&Circuit::compute_stats)
         .def("append-from-file",&Circuit::append_from_file)
         .def("append-from-text",&Circuit::append_from_text)
         .def("clear",&Circuit::clear)
         ;
       // ExposedDemInstruction (python)
       // ExposedDemTarget (python)
       // ExposedDemRepeatBlock (python)
       // DetectorErrorModel
       class_<DetectorErrorModel>(s,"detector-error-model")
         ;
       // TableauSimulator
       class_<TableauSimulator<MAX_BITWORD_WIDTH>>(s,"tableau-simulator")
         ;
       // FrameSimulator
       class_<FrameSimulator<MAX_BITWORD_WIDTH>>(s,"frame-simulator")
         ;

       // CircuitErrorLocationStackFrame
       class_<CircuitErrorLocationStackFrame>(s,"circuit-error-location-stack-frame")
         ;
       // GateTargetWithCoords
       class_<GateTargetWithCoords>(s,"gate-target-with-coords")
         ;
       // dem_target_with_coords
       class_<DemTargetWithCoords>(s,"dem-target-with-coords")
         ;
       // flipped_measurement
       class_<FlippedMeasurement>(s,"flipped-measurement")
         ;
       // circuit_targets_inside_instruction
       class_<CircuitTargetsInsideInstruction>(s,"circuit-targets-inside-instruction")
         ;
       // circuit_error_location
       class_<CircuitErrorLocation>(s,"circuit-error-location")
         ;
       // circuit_error_location_methods
       class_<ExplainedError>(s,"explained-error")
         ;
       // flow
       class_<Flow<MAX_BITWORD_WIDTH>>(s,"flow")
         ;
       // diagram_helper (python)
       //end [class definitions]
  }
}; // namespace clasp_stim
