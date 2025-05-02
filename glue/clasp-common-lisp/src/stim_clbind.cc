// Clasp bindings for Stim.
// These bindings are inspired by, and closely follow, the Python Stim v.1.13 API (or the Python API for short).

#include <fmt/format.h>
#include <clasp/clasp.h>
#include "stim.h"
#include "stim_clasp.h"

PACKAGE_USE("COMMON-LISP");

NAMESPACE_PACKAGE_ASSOCIATION(clasp_stim, ClaspStimPkg, "STIM");

namespace clasp_stim {
  template<typename K, typename V>
  map<V, K> reverse_map(const map<K, V>& m) {
    map<V, K> r;
    for (const auto& kv : m)
      r[kv.second] = kv.first;
    return r;
  }
  using namespace clbind;
  using namespace stim;
  void expose_main_methods(){
    // Here we expose in order the top level functions in the Python API.
    fmt::print("Exposing main methods...\n");
    package_ s(ClaspStimPkg);
    s.def("gate-data",&stim__gate_data);
    s.def("main",&stim__main);
    // not doing read_shot_data_file; unnecessary
    s.def("target-combined-paulis-string",&stim__target_combined_paulis_string);
    s.def("target-combined-paulis-gate-targets",&stim__target_combined_paulis_gate_targets);
    s.def("target-combiner",&stim::GateTarget::combiner);
    s.def("target-inverse-target",&stim__target_inv_target);
    s.def("target-inverse-integer",&stim__target_inv_uint32_t);
    s.def("target-logical-observable-id",&stim__target_logical_observable_id);
    s.def("target-pauli-string",&stim__target_pauli_string);
    s.def("target-pauli-integer",&stim__target_pauli_uint8_t);
    s.def("target-rec",&stim__target_rec);
    s.def("target-relative-detector-id",&stim__target_relative_detector_id);
    s.def("target-separator",&stim__target_separator);
    s.def("target-sweep-bit",&stim__target_sweep_bit);
    s.def("target-x-target",&stim__target_x_target);
    s.def("target-x-integer",&stim__target_x_uint32_t);
    s.def("target-y-target",&stim__target_y_target);
    s.def("target-y-integer",&stim__target_y_uint32_t);
    s.def("target-z-target",&stim__target_z_target);
    s.def("target-z-integer",&stim__target_z_uint32_t);
    // not doing write_shot_data_file; unnecessary
  }
  void expose_classes(){
    // Here we expose all the necessary classes in the order they appear in the Python Stim v.1.13 API..
    // This is a bit more complicated than top level functions, as not all the Python API classes correspond to one or more C++ classes.
    // Some of them are in the stim_pybind namespace, meaning that we cannot and should not expose them.
    // Instead alternatives are defined in stim_clbind.h.
    // Methods are also defined for the classes where it makes sense.
    fmt::print("Exposing classes...\n");
    package_ s(ClaspStimPkg);
    class_<clbind_Circuit>(s,"circuit");
    class_<clbind_CircuitErrorLocation>(s,"circuit-error-location");
    class_<clbind_CircuitErrorLocationStackFrame>(s,"circuit-error-location-stack-frame");
    class_<clbind_CircuitInstruction>(s,"circuit-instruction");
    class_<clbind_CircuitRepeatBlock>(s,"circuit-repeat-block");
    class_<clbind_CircuitTargetsInsideInstruction>(s,"circuit-targets-inside-instruction");
    class_<clbind_CompiledDemSampler>(s,"compiled-dem-sampler");
    class_<clbind_CompiledDetectorSampler>(s,"compiled-detector-sampler");
    class_<clbind_CompiledMeasurementSampler>(s,"compiled-measurement-sampler");
    class_<clbind_CompiledMeasurementsToDetectionEventsConverter>
      (s,"compiled-measurements-to-detection-events-converter");
    class_<clbind_DemInstruction>(s,"dem-instruction");
    class_<clbind_DemRepeatBlock>(s,"dem-repeat-block");
    class_<clbind_DemTarget>(s,"dem-target");
    class_<clbind_DemTargetWithCoords>(s,"dem-target-with-coords");
    class_<clbind_DetectorErrorModel>(s,"detector-error-model");
    class_<clbind_ExplainedError>(s,"explained-error");
    class_<clbind_FlipSimulator>(s,"flip-simulator");
    class_<clbind_FlippedMeasurement>(s,"flipped-measurement");
    class_<clbind_Flow>(s,"flow");
    class_<clbind_GateData>(s,"gate-data");
    class_<clbind_GateTarget>(s,"gate-target");
    class_<clbind_GateTargetWithCoords>(s,"gate-target-with-coords");
    class_<clbind_PauliString>(s,"pauli-string");
    class_<clbind_PauliStringIterator>(s,"pauli-string-iterator");
    class_<clbind_Tableau>(s,"tableau");
    class_<clbind_TableauIterator>(s,"tableau-iterator");
    class_<clbind_TableauSimulator>(s,"tableau-simulator");
    class_<clbind_DiagramHelper>(s,"diagram-helper");
  }
  void expose_api_functions(){
    fmt::print("Exposing API functions...\n");
    package_ s(ClaspStimPkg);
  }
  extern "C" void startup_clasp_extension() {
    fmt::print("Entered {}:{}:{}\n", __FILE__, __LINE__, __FUNCTION__);
    package_ s(ClaspStimPkg);

    expose_main_methods();
    expose_classes();
    expose_api_functions();

    fmt::print("Exited {}:{}:{}\n", __FILE__, __LINE__, __FUNCTION__);
  }
}; // namespace clasp_stim

CLBIND_EXPOSE_MACRO(stim::GateType,({{"NOT-A-GATE", GateType::NOT_A_GATE},
                                     {"DETECTOR",GateType::DETECTOR},
                                     {"OBSERVABLE-INCLUDE",GateType::OBSERVABLE_INCLUDE},
                                     {"TICK",GateType::TICK},
                                     {"QUBIT-COORDINATES",GateType::QUBIT_COORDS},
                                     {"SHIFT-COORDINATES",GateType::SHIFT_COORDS},
                                     {"REPEAT",GateType::REPEAT}}));

CLBIND_EXPOSE_MACRO(stim::GateFlags,({{"GATE-UNITARY-P",GateFlags::GATE_IS_UNITARY}}));

CLBIND_EXPOSE_MACRO(stim::SampleFormat,({{"01",SampleFormat::SAMPLE_FORMAT_01},
                                         {"B8",SampleFormat::SAMPLE_FORMAT_B8},
                                         {"PTB64",SampleFormat::SAMPLE_FORMAT_PTB64},
                                         {"HITS",SampleFormat::SAMPLE_FORMAT_HITS},
                                         {"R8",SampleFormat::SAMPLE_FORMAT_R8},
                                         {"DETS",SampleFormat::SAMPLE_FORMAT_DETS}}));
