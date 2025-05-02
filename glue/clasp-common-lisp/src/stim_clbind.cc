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
    s.def("circuit-add",&circuit__add);
    s.def("circuit-eq",&circuit__eq);
//s.def("circuit-getitem-uint32-t",&circuit__getitem_uint32_t);
//s.def("circuit-getitem-slice",&circuit__getitem_slice);
s.def("circuit-iadd",&circuit__iadd);
s.def("circuit-imul",&circuit__imul);
s.def("circuit-init",&circuit__init);
s.def("circuit-len",&circuit__len);
s.def("circuit-mul",&circuit__mul);
s.def("circuit-ne",&circuit__ne);
s.def("circuit-repr",&circuit__repr);
s.def("circuit-rmul",&circuit__rmul);
s.def("circuit-str",&circuit__str);
//s.def("circuit-append-int-array",&circuit__append_int_array);
//s.def("circuit-append-gate-target-array",&circuit__append_gate_target_array);
//s.def("circuit-append-circuit-instruction",&circuit__append_circuit_instruction);
//s.def("circuit-append-circuit-repeat-block",&circuit__append_circuit_repeat_block);
s.def("circuit-append-from-stim-program-text",&circuit__append_from_stim_program_text);
//s.def("circuit-approx-equals",&circuit__approx_equals);
s.def("circuit-clear",&circuit__clear);
//s.def("circuit-compile-detector-sampler",&circuit__compile_detector_sampler);
//s.def("circuit-compile-detector-sampler-seed",&circuit__compile_detector_sampler_seed);
//s.def("circuit__compile_m2d_converter",&circuit__compile_m2d_converter);
//s.def("circuit-compile-sampler",&circuit__compile_sampler);
//s.def("circuit-compile-sampler-seed",&circuit__compile_sampler_seed);
//s.def("circuit-compile-sampler-reference-sample",&circuit__compile_sampler_reference_sample);
//s.def("circuit-compile-sampler-reference-sample-seed",&circuit__compile_sampler_reference_sample_seed);
s.def("circuit-copy",&circuit__copy);
//s.def("circuit-count-determined-measurements",&circuit__count_determined_measurements);
//s.def("circuit-decomposed",&circuit__decomposed);
//s.def("circuit-detecting-regions",&circuit__detecting_regions);
//s.def("circuit-detecting-regions-targets-strings",&circuit__detecting_regions_targets_strings);
//s.def("circuit-detecting-regions-targets-floats",&circuit__detecting_regions_targets_floats);
//s.def("circuit-detecting-regions-targets-strings-ticks",&circuit__detecting_regions_targets_strings_ticks);
//s.def("circuit-detecting-regions-targets-floats-ticks",&circuit__detecting_regions_targets_floats_ticks);
//s.def("circuit-detecting-regions-ticks",&circuit__detecting_regions_ticks);
//s.def("circuit-detector-error-model",&circuit__detector_error_model);
//s.def("circuit-diagram-range-float",&circuit__diagram_range_float);
//s.def("circuit-diagram-range-dem-target",&circuit__diagram_range_dem_target);
//s.def("circuit-diagram-tick-float",&circuit__diagram_tick_float);
//s.def("circuit-diagram-tick-dem-target",&circuit__diagram_tick_dem_target);
//s.def("circuit-diagram-float",&circuit__diagram_float);
//s.def("circuit-diagram-dem-target",&circuit__diagram_dem_target);
//s.def("circuit-diagram",&circuit__diagram);
//s.def("circuit-explain-detector-error-model-errors",&circuit__explain_detector_error_model_errors);
//s.def("circuit-flattened",&circuit__flattened);
//s.def("circuit-from-file",&circuit__from_file);
s.def("circuit-generated",&circuit__generated);
//s.def("circuit-get-detector-coordinates",&circuit__get_detector_coordinates);
//s.def("circuit-get-detector-coordinates-only",&circuit__get_detector_coordinates_only);
s.def("circuit-get-final-qubit-coordinates",&circuit__get_final_qubit_coordinates);
//s.def("circuit-has-all-flows",&circuit__has_all_flows);
//s.def("circuit-has-flow",&circuit__has_flow);
//s.def("circuit-inverse",&circuit__inverse);
//s.def("circuit-likeliest-error-sat-problem-wdimacs",&circuit__likeliest_error_sat_problem_wdimacs);
//s.def("circuit-num-detectors",&circuit__num_detectors);
//s.def("circuit-num-measurements",&circuit__num_measurements);
//s.def("circuit-num-observables",&circuit__num_observables);
//s.def("circuit-num-qubits",&circuit__num_qubits);
//s.def("circuit-num-sweep-bits",&circuit__num_sweep_bits);
//s.def("circuit-num-ticks",&circuit__num_ticks);
//s.def("circuit-reference-sample",&circuit__reference_sample);
//s.def("circuit-search-for-undetectable-logical-errors",&circuit__search_for_undetectable_logical_errors);
//s.def("circuit-shortest-error-sat-problem-dimacs",&circuit__shortest_error_sat_problem_dimacs);
//s.def("circuit-shortest-graphlike-error",&circuit__shortest_graphlike_error);
//s.def("circuit-to-file",&circuit__to_file);
//s.def("circuit-to-qasm",&circuit__to_qasm);
//s.def("circuit-to-tableau",&circuit__to_tableau);
//s.def("circuit-with-inlined-feedback",&circuit__with_inlined_feedback);
//s.def("circuit-without-noise",&circuit__without_noise);
//s.def("circuit-error-location-flipped-measurement-p",&circuit_error_location__flipped_measurement_p);
//s.def("circuit-error-location-flipped-measurement",&circuit_error_location__flipped_measurement);
//s.def("circuit-error-location-flipped-pauli-product",&circuit_error_location__flipped_pauli_product);
//s.def("circuit-error-location-instruction-targets",&circuit_error_location__instruction_targets);
//s.def("circuit-error-location-stack-frames",&circuit_error_location__stack_frames);
//s.def("circuit-error-location-tick-offset",&circuit_error_location__tick_offset);
//s.def("circuit-error-location-stack-frame-init",&circuit_error_location_stack_frame__init);
//s.def("circuit-error-location-stack-frame-offset",&circuit_error_location_stack_frame__offset);
//s.def("circuit-error-location-stack-frame-repetitions-arg",&circuit_error_location_stack_frame__repetitions_arg);
//s.def("circuit-error-location-stack-frame-iteration-index",&circuit_error_location_stack_frame__iteration_index);
//s.def("circuit-instruction-eq",&circuit_instruction__eq);
//s.def("circuit-instruction-init-ints",&circuit_instruction__init_ints);
//s.def("circuit-instruction-init-gate-targets",&circuit_instruction__init_gate_targets);
//s.def("circuit-instruction-ne",&circuit_instruction__ne);
//s.def("circuit-instruction-repr",&circuit_instruction__repr);
//s.def("circuit-instruction-str",&circuit_instruction__str);
//s.def("circuit-instruction-gate-args-copy",&circuit_instruction__gate_args_copy);
//s.def("circuit-instruction-name",&circuit_instruction__name);
//s.def("circuit-instruction-targets-copy",&circuit_instruction__targets_copy);
//s.def("circuit-repeat-block-eq",&circuit_repeat_block__eq);
//s.def("circuit-repeat-block-init",&circuit_repeat_block__init);
//s.def("circuit-repeat-block-ne",&circuit_repeat_block__ne);
//s.def("circuit-repeat-block-repr",&circuit_repeat_block__repr);
//s.def("circuit-repeat-block-body-copy",&circuit_repeat_block__body_copy);
//s.def("circuit-repeat-block-name",&circuit_repeat_block__name);
//s.def("circuit-repeat-block-repeat-count",&circuit_repeat_block__repeat_count);
//s.def("circuit-targets-inside-instruction-init",&circuit_targets_inside_instruction__init);
//s.def("circuit-targets-inside-instruction-args",&circuit_targets_inside_instruction__args);
//s.def("circuit-targets-inside-instruction-gate-p",&circuit_targets_inside_instruction__gate_p);
//s.def("circuit-targets-inside-instruction-gate",&circuit_targets_inside_instruction__gate);
//s.def("circuit-targets-inside-instruction-target-range-end",&circuit_targets_inside_instruction__target_range_end);
//s.def("circuit-targets-inside-instruction-target-range-start",&circuit_targets_inside_instruction__target_range_start);
//s.def("circuit-targets-inside-instruction-targets-in-range",&circuit_targets_inside_instruction__targets_in_range);
//s.def("compiled-dem-sampler-sample",&compiled_dem_sampler__sample);
//s.def("compiled-dem-sampler-sample-recorded-errors-to-replay",&compiled_dem_sampler__sample_recorded_errors_to_replay);
//s.def("compiled-dem-sampler-sample-write",&compiled_dem_sampler__sample_write);
//s.def("compiled-detector-sampler-init",&compiled_detector_sampler__init);
//s.def("compiled-detector-sampler-init-seed",&compiled_detector_sampler__init_seed);
//s.def("compiled-detector-sampler-repr",&compiled_detector_sampler__repr);
//s.def("compiled-detector-sampler-sample",&compiled_detector_sampler__sample);
//s.def("compiled-detector-sampler-sample-write",&compiled_detector_sampler__sample_write);
//s.def("compiled-measurement-sampler-init",&compiled_measurement_sampler__init);
//s.def("compiled-measurement-sampler-repr",&compiled_measurement_sampler__repr);
//s.def("compiled-measurement-sampler-sample",&compiled_measurement_sampler__sample);
//s.def("compiled-measurement-sampler-sample-write",&compiled_measurement_sampler__sample_write);
//s.def("Compiled-Measurements-To-Detection-Events-Converter-init",&CompiledMeasurementsToDetectionEventsConverter__init);
//s.def("Compiled-Measurements-To-Detection-Events-Converter-repr",&CompiledMeasurementsToDetectionEventsConverter__repr);
//s.def("Compiled-Measurements-To-Detection-Events-Converter-convert",&CompiledMeasurementsToDetectionEventsConverter__convert);
//s.def("Compiled-Measurements-To-Detection-Events-Converter-convert-file",&CompiledMeasurementsToDetectionEventsConverter__convert_file);
//s.def("Dem-Instruction-eq",&DemInstruction__eq);
//s.def("Dem-Instruction-init",&DemInstruction__init);
//s.def("Dem-Instruction-ne",&DemInstruction__ne);
//s.def("Dem-Instruction-repr",&DemInstruction__repr);
//s.def("Dem-Instruction-str",&DemInstruction__str);
//s.def("Dem-Instruction-args-copy",&DemInstruction__args_copy);
//s.def("Dem-Instruction-targets-copy",&DemInstruction__targets_copy);
//s.def("Dem-Instruction-type",&DemInstruction__type);
//s.def("Dem-Repeat-Block-eq",&DemRepeatBlock__eq);
//s.def("Dem-Repeat-Block-init",&DemRepeatBlock__init);
//s.def("Dem-Repeat-Block-ne",&DemRepeatBlock__ne);
//s.def("Dem-Repeat-Block-repr",&DemRepeatBlock__repr);
//s.def("Dem-Repeat-Block-body-copy",&DemRepeatBlock__body_copy);
//s.def("Dem-Repeat-Block-repeat-count",&DemRepeatBlock__repeat_count);
//s.def("Dem-Repeat-Block-type",&DemRepeatBlock__type);
//s.def("Dem-Target-eq",&DemTarget__eq);
//s.def("Dem-Target-ne",&DemTarget__ne);
//s.def("Dem-Target-repr",&DemTarget__repr);
//s.def("Dem-Target-str",&DemTarget__str);
//s.def("Dem-Target-is-logical-observable-id",&DemTarget__is_logical_observable_id);
//s.def("Dem-Target-is-relative-detector-id",&DemTarget__is_relative_detector_id);
//s.def("Dem-Target-is-separator",&DemTarget__is_separator);
//s.def("Dem-Target-logical-observable-id",&DemTarget__logical_observable_id);
//s.def("Dem-Target-relative-detector-id",&DemTarget__relative_detector_id);
//s.def("Dem-Target-separator",&DemTarget__separator);
//s.def("Dem-Target-val",&DemTarget__val);
//s.def("Dem-Target-With-Coords-init",&DemTargetWithCoords__init);
//s.def("Dem-Target-With-Coords-coords",&DemTargetWithCoords__coords);
//s.def("Dem-Target-With-Coords-dem-target",&DemTargetWithCoords__dem_target);
//s.def("Detector-Error-Model-add",&DetectorErrorModel__add);
//s.def("Detector-Error-Model-eq",&DetectorErrorModel__eq);
//s.def("Detector-Error-Model-getitem",&DetectorErrorModel__getitem);
//s.def("Detector-Error-Model-iadd",&DetectorErrorModel__iadd);
//s.def("Detector-Error-Model-imul",&DetectorErrorModel__imul);
//s.def("Detector-Error-Model-init",&DetectorErrorModel__init);
//s.def("Detector-Error-Model-len",&DetectorErrorModel__len);
//s.def("Detector-Error-Model-mul",&DetectorErrorModel__mul);
//s.def("Detector-Error-Model-ne",&DetectorErrorModel__ne);
//s.def("Detector-Error-Model-repr",&DetectorErrorModel__repr);
//s.def("Detector-Error-Model-rmul",&DetectorErrorModel__rmul);
//s.def("Detector-Error-Model-str",&DetectorErrorModel__str);
//s.def("Detector-Error-Model-append",&DetectorErrorModel__append);
//s.def("Detector-Error-Model-approx-equals",&DetectorErrorModel__approx_equals);
//s.def("Detector-Error-Model-clear",&DetectorErrorModel__clear);
//s.def("Detector-Error-Model-compile-sampler",&DetectorErrorModel__compile_sampler);
//s.def("Detector-Error-Model-copy",&DetectorErrorModel__copy);
//s.def("Detector-Error-Model-diagram",&DetectorErrorModel__diagram);
//s.def("Detector-Error-Model-flattened",&DetectorErrorModel__flattened);
//s.def("Detector-Error-Model-from-file",&DetectorErrorModel__from_file);
//s.def("Detector-Error-Model-get-detector-coordinates",&DetectorErrorModel__get_detector_coordinates);
//s.def("Detector-Error-Model-num-detectors",&DetectorErrorModel__num_detectors);
//s.def("Detector-Error-Model-num-errors",&DetectorErrorModel__num_errors);
//s.def("Detector-Error-Model-num-observables",&DetectorErrorModel__num_observables);
//s.def("Detector-Error-Model-rounded",&DetectorErrorModel__rounded);
//s.def("Detector-Error-Model-shortest-graphlike-error",&DetectorErrorModel__shortest_graphlike_error);
//s.def("Detector-Error-Model-to-file",&DetectorErrorModel__to_file);
//s.def("Explained-Error",&ExplainedError);
//s.def("Explained-Error-init",&ExplainedError__init);
//s.def("Explained-Error-circuit-error-locations",&ExplainedError__circuit_error_locations);
//s.def("Explained-Error-dem-error-terms",&ExplainedError__dem_error_terms);
//s.def("Flip-Simulator",&FlipSimulator);
//s.def("Flip-Simulator-init",&FlipSimulator__init);
//s.def("Flip-Simulator-batch-size",&FlipSimulator__batch_size);
//s.def("Flip-Simulator-broadcast-pauli-errors",&FlipSimulator__broadcast_pauli_errors);
//s.def("Flip-Simulator-do",&FlipSimulator__do);
//s.def("Flip-Simulator-get-detector-flips",&FlipSimulator__get_detector_flips);
//s.def("Flip-Simulator-get-measurement-flips",&FlipSimulator__get_measurement_flips);
//s.def("Flip-Simulator-get-observable-flips",&FlipSimulator__get_observable_flips);
//s.def("Flip-Simulator-num-detectors",&FlipSimulator__num_detectors);
//s.def("Flip-Simulator-num-measurements",&FlipSimulator__num_measurements);
//s.def("Flip-Simulator-num-observables",&FlipSimulator__num_observables);
//s.def("Flip-Simulator-num-qubits",&FlipSimulator__num_qubits);
//s.def("Flip-Simulator-peek-pauli-flips",&FlipSimulator__peek_pauli_flips);
//s.def("Flip-Simulator-set-pauli-flip",&FlipSimulator__set_pauli_flip);
//s.def("Flipped-Measurement-init",&FlippedMeasurement__init);
//s.def("Flipped-Measurement-observable",&FlippedMeasurement__observable);
//s.def("Flipped-Measurement-record-index",&FlippedMeasurement__record_index);
//s.def("Flow-eq",&Flow__eq);
//s.def("Flow-init",&Flow__init);
//s.def("Flow-ne",&Flow__ne);
//s.def("Flow-repr",&Flow__repr);
//s.def("Flow-str",&Flow__str);
//s.def("Flow-input-copy",&Flow__input_copy);
//s.def("Flow-measurements-copy",&Flow__measurements_copy);
//s.def("Flow-output-copy",&Flow__output_copy);
//s.def("Gate-Data-eq",&GateData__eq);
//s.def("Gate-Data-init",&GateData__init);
//s.def("Gate-Data-ne",&GateData__ne);
//s.def("Gate-Data-repr",&GateData__repr);
//s.def("Gate-Data-str",&GateData__str);
//s.def("Gate-Data-aliases",&GateData__aliases);
//s.def("Gate-Data-flows",&GateData__flows);
//s.def("Gate-Data-generalized-inverse",&GateData__generalized_inverse);
//s.def("Gate-Data-inverse",&GateData__inverse);
//s.def("Gate-Data-is-noisy-gate",&GateData__is_noisy_gate);
//s.def("Gate-Data-is-reset",&GateData__is_reset);
//s.def("Gate-Data-is-single-qubit-gate",&GateData__is_single_qubit_gate);
//s.def("Gate-Data-is-two-qubit-gate",&GateData__is_two_qubit_gate);
//s.def("Gate-Data-is-unitary",&GateData__is_unitary);
//s.def("Gate-Data-name",&GateData__name);
//s.def("Gate-Data-num-parens-arguments-range",&GateData__num_parens_arguments_range);
//s.def("Gate-Data-produces-measurements",&GateData__produces_measurements);
//s.def("Gate-Data-tableau",&GateData__tableau);
//s.def("Gate-Data-takes-measurement-record-targets",&GateData__takes_measurement_record_targets);
//s.def("Gate-Data-takes-pauli-targets",&GateData__takes_pauli_targets);
//s.def("Gate-Data-unitary-matrix",&GateData__unitary_matrix);
//s.def("Gate-Target-eq",&GateTarget__eq);
//s.def("Gate-Target-init",&GateTarget__init);
//s.def("Gate-Target-ne",&GateTarget__ne);
//s.def("Gate-Target-repr",&GateTarget__repr);
//s.def("Gate-Target-is-combiner",&GateTarget__is_combiner);
//s.def("Gate-Target-is-inverted-result-target",&GateTarget__is_inverted_result_target);
//s.def("Gate-Target-is-measurement-record-target",&GateTarget__is_measurement_record_target);
//s.def("Gate-Target-is-qubit-target",&GateTarget__is_qubit_target);
//s.def("Gate-Target-is-sweep-bit-target",&GateTarget__is_sweep_bit_target);
//s.def("Gate-Target-is-x-target",&GateTarget__is_x_target);
//s.def("Gate-Target-is-y-target",&GateTarget__is_y_target);
//s.def("Gate-Target-is-z-target",&GateTarget__is_z_target);
//s.def("Gate-Target-pauli-type",&GateTarget__pauli_type);
//s.def("Gate-Target-qubit-value",&GateTarget__qubit_value);
//s.def("Gate-Target-value",&GateTarget__value);
//s.def("Gate-Target-With-Coords-init",&GateTargetWithCoords__init);
//s.def("Gate-Target-With-Coords-coords",&GateTargetWithCoords__coords);
//s.def("Gate-Target-With-Coords-gate-target",&GateTargetWithCoords__gate_target);
//s.def("Pauli-String-add",&PauliString__add);
//s.def("Pauli-String-eq",&PauliString__eq);
//s.def("Pauli-String-getitem",&PauliString__getitem);
//s.def("Pauli-String-iadd",&PauliString__iadd);
//s.def("Pauli-String-imul",&PauliString__imul);
//s.def("Pauli-String-init",&PauliString__init);
//s.def("Pauli-String-itruediv",&PauliString__itruediv);
//s.def("Pauli-String-len",&PauliString__len);
//s.def("Pauli-String-mul",&PauliString__mul);
//s.def("Pauli-String-ne",&PauliString__ne);
//s.def("Pauli-String-neg",&PauliString__neg);
//s.def("Pauli-String-pos",&PauliString__pos);
//s.def("Pauli-String-repr",&PauliString__repr);
//s.def("Pauli-String-rmul",&PauliString__rmul);
//s.def("Pauli-String-setitem",&PauliString__setitem);
//s.def("Pauli-String-str",&PauliString__str);
//s.def("Pauli-String-truediv",&PauliString__truediv);
//s.def("Pauli-String-after",&PauliString__after);
//s.def("Pauli-String-before",&PauliString__before);
//s.def("Pauli-String-commutes",&PauliString__commutes);
//s.def("Pauli-String-copy",&PauliString__copy);
//s.def("Pauli-String-from-numpy",&PauliString__from_numpy);
//s.def("Pauli-String-from-unitary-matrix",&PauliString__from_unitary_matrix);
//s.def("Pauli-String-iter-all",&PauliString__iter_all);
//s.def("Pauli-String-pauli-indices",&PauliString__pauli_indices);
//s.def("Pauli-String-random",&PauliString__random);
//s.def("Pauli-String-sign",&PauliString__sign);
//s.def("Pauli-String-to-numpy",&PauliString__to_numpy);
//s.def("Pauli-String-to-tableau",&PauliString__to_tableau);
//s.def("Pauli-String-to-unitary-matrix",&PauliString__to_unitary_matrix);
//s.def("Pauli-String-weight",&PauliString__weight);
//s.def("Pauli-String-Iterator-iter",&PauliStringIterator__iter);
//s.def("Pauli-String-Iterator-next",&PauliStringIterator__next);
//s.def("Tableau-add",&Tableau__add);
//s.def("Tableau-call",&Tableau__call);
//s.def("Tableau-eq",&Tableau__eq);
//s.def("Tableau-iadd",&Tableau__iadd);
//s.def("Tableau-init",&Tableau__init);
//s.def("Tableau-len",&Tableau__len);
//s.def("Tableau-mul",&Tableau__mul);
//s.def("Tableau-ne",&Tableau__ne);
//s.def("Tableau-pow",&Tableau__pow);
//s.def("Tableau-repr",&Tableau__repr);
//s.def("Tableau-str",&Tableau__str);
//s.def("Tableau-append",&Tableau__append);
//s.def("Tableau-copy",&Tableau__copy);
//s.def("Tableau-from-circuit",&Tableau__from_circuit);
//s.def("Tableau-from-conjugated-generators",&Tableau__from_conjugated_generators);
//s.def("Tableau-from-named-gate",&Tableau__from_named_gate);
//s.def("Tableau-from-numpy",&Tableau__from_numpy);
//s.def("Tableau-from-stabilizers",&Tableau__from_stabilizers);
//s.def("Tableau-from-state-vector",&Tableau__from_state_vector);
//s.def("Tableau-from-unitary-matrix",&Tableau__from_unitary_matrix);
//s.def("Tableau-inverse",&Tableau__inverse);
//s.def("Tableau-inverse-x-output",&Tableau__inverse_x_output);
//s.def("Tableau-inverse-x-output-pauli",&Tableau__inverse_x_output_pauli);
//s.def("Tableau-inverse-y-output",&Tableau__inverse_y_output);
//s.def("Tableau-inverse-y-output-pauli",&Tableau__inverse_y_output_pauli);
//s.def("Tableau-inverse-z-output",&Tableau__inverse_z_output);
//s.def("Tableau-inverse-z-output-pauli",&Tableau__inverse_z_output_pauli);
//s.def("Tableau-iter-all",&Tableau__iter_all);
//s.def("Tableau-prepend",&Tableau__prepend);
//s.def("Tableau-random",&Tableau__random);
//s.def("Tableau-then",&Tableau__then);
//s.def("Tableau-to-circuit",&Tableau__to_circuit);
//s.def("Tableau-to-numpy",&Tableau__to_numpy);
//s.def("Tableau-to-pauli-string",&Tableau__to_pauli_string);
//s.def("Tableau-to-stabilizers",&Tableau__to_stabilizers);
//s.def("Tableau-to-state-vector",&Tableau__to_state_vector);
//s.def("Tableau-to-unitary-matrix",&Tableau__to_unitary_matrix);
//s.def("Tableau-x-output",&Tableau__x_output);
//s.def("Tableau-x-output-pauli",&Tableau__x_output_pauli);
//s.def("Tableau-x-sign",&Tableau__x_sign);
//s.def("Tableau-y-output",&Tableau__y_output);
//s.def("Tableau-y-output-pauli",&Tableau__y_output_pauli);
//s.def("Tableau-y-sign",&Tableau__y_sign);
//s.def("Tableau-z-output",&Tableau__z_output);
//s.def("Tableau-z-output-pauli",&Tableau__z_output_pauli);
//s.def("Tableau-z-sign",&Tableau__z_sign);
//s.def("Tableau-Iterator-iter",&TableauIterator__iter);
//s.def("Tableau-Iterator-next",&TableauIterator__next);
//s.def("Tableau-Simulator-init",&TableauSimulator__init);
//s.def("Tableau-Simulator-c-xyz",&TableauSimulator__c_xyz);
//s.def("Tableau-Simulator-c-zyx",&TableauSimulator__c_zyx);
//s.def("Tableau-Simulator-canonical-stabilizers",&TableauSimulator__canonical_stabilizers);
//s.def("Tableau-Simulator-cnot",&TableauSimulator__cnot);
//s.def("Tableau-Simulator-copy",&TableauSimulator__copy);
//s.def("Tableau-Simulator-current-inverse-tableau",&TableauSimulator__current_inverse_tableau);
//s.def("Tableau-Simulator-current-measurement-record",&TableauSimulator__current_measurement_record);
//s.def("Tableau-Simulator-cx",&TableauSimulator__cx);
//s.def("Tableau-Simulator-cy",&TableauSimulator__cy);
//s.def("Tableau-Simulator-cz",&TableauSimulator__cz);
//s.def("TableauSimulator__depolarize1",&TableauSimulator__depolarize1);
//s.def("TableauSimulator__depolarize2",&TableauSimulator__depolarize2);
//s.def("Tableau-Simulator-do",&TableauSimulator__do);
//s.def("Tableau-Simulator-do-circuit",&TableauSimulator__do_circuit);
//s.def("Tableau-Simulator-do-pauli-string",&TableauSimulator__do_pauli_string);
//s.def("Tableau-Simulator-do-tableau",&TableauSimulator__do_tableau);
//s.def("Tableau-Simulator-h",&TableauSimulator__h);
//s.def("Tableau-Simulator-h-xy",&TableauSimulator__h_xy);
//s.def("Tableau-Simulator-h-xz",&TableauSimulator__h_xz);
//s.def("Tableau-Simulator-h-yz",&TableauSimulator__h_yz);
//s.def("Tableau-Simulator-iswap",&TableauSimulator__iswap);
//s.def("Tableau-Simulator-iswap-dag",&TableauSimulator__iswap_dag);
//s.def("Tableau-Simulator-measure",&TableauSimulator__measure);
//s.def("Tableau-Simulator-measure-kickback",&TableauSimulator__measure_kickback);
//s.def("Tableau-Simulator-measure-many",&TableauSimulator__measure_many);
//s.def("Tableau-Simulator-measure-observable",&TableauSimulator__measure_observable);
//s.def("Tableau-Simulator-num-qubits",&TableauSimulator__num_qubits);
//s.def("Tableau-Simulator-peek-bloch",&TableauSimulator__peek_bloch);
//s.def("Tableau-Simulator-peek-observable-expectation",&TableauSimulator__peek_observable_expectation);
//s.def("Tableau-Simulator-peek-x",&TableauSimulator__peek_x);
//s.def("Tableau-Simulator-peek-y",&TableauSimulator__peek_y);
//s.def("Tableau-Simulator-peek-z",&TableauSimulator__peek_z);
//s.def("Tableau-Simulator-postselect-observable",&TableauSimulator__postselect_observable);
//s.def("Tableau-Simulator-postselect-x",&TableauSimulator__postselect_x);
//s.def("Tableau-Simulator-postselect-y",&TableauSimulator__postselect_y);
//s.def("Tableau-Simulator-postselect-z",&TableauSimulator__postselect_z);
//s.def("Tableau-Simulator-reset",&TableauSimulator__reset);
//s.def("Tableau-Simulator-reset-x",&TableauSimulator__reset_x);
//s.def("Tableau-Simulator-reset-y",&TableauSimulator__reset_y);
//s.def("Tableau-Simulator-reset-z",&TableauSimulator__reset_z);
//s.def("Tableau-Simulator-s",&TableauSimulator__s);
//s.def("Tableau-Simulator-s-dag",&TableauSimulator__s_dag);
//s.def("Tableau-Simulator-set-inverse-tableau",&TableauSimulator__set_inverse_tableau);
//s.def("Tableau-Simulator-set-num-qubits",&TableauSimulator__set_num_qubits);
//s.def("Tableau-Simulator-set-state-from-stabilizers",&TableauSimulator__set_state_from_stabilizers);
//s.def("Tableau-Simulator-set-state-from-state-vector",&TableauSimulator__set_state_from_state_vector);
//s.def("Tableau-Simulator-sqrt-x",&TableauSimulator__sqrt_x);
//s.def("Tableau-Simulator-sqrt-x-dag",&TableauSimulator__sqrt_x_dag);
//s.def("Tableau-Simulator-sqrt-y",&TableauSimulator__sqrt_y);
//s.def("Tableau-Simulator-sqrt-y-dag",&TableauSimulator__sqrt_y_dag);
//s.def("Tableau-Simulator-state-vector",&TableauSimulator__state_vector);
//s.def("Tableau-Simulator-swap",&TableauSimulator__swap);
//s.def("Tableau-Simulator-x",&TableauSimulator__x);
//s.def("Tableau-Simulator-x-error",&TableauSimulator__x_error);
//s.def("Tableau-Simulator-xcx",&TableauSimulator__xcx);
//s.def("Tableau-Simulator-xcy",&TableauSimulator__xcy);
//s.def("Tableau-Simulator-xcz",&TableauSimulator__xcz);
//s.def("Tableau-Simulator-y",&TableauSimulator__y);
//s.def("Tableau-Simulator-y-error",&TableauSimulator__y_error);
//s.def("Tableau-Simulator-ycx",&TableauSimulator__ycx);
//s.def("Tableau-Simulator-ycy",&TableauSimulator__ycy);
//s.def("Tableau-Simulator-ycz",&TableauSimulator__ycz);
//s.def("Tableau-Simulator-z",&TableauSimulator__z);
//s.def("Tableau-Simulator-z-error",&TableauSimulator__z_error);
//s.def("Tableau-Simulator-zcx",&TableauSimulator__zcx);
//s.def("Tableau-Simulator-zcy",&TableauSimulator__zcy);
//s.def("Tableau-Simulator-zcz",&TableauSimulator__zcz);

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

// enums

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

// translators (why don't they work when put in a different file?)

namespace translate
{
  template <>
  struct to_object<std::map<uint32_t, std::vector<double>>>
  {
    static core::T_sp convert(std::map<uint32_t, std::vector<double>> arg)
    {
      core::Cons_sp return_list = nil<core::Cons_O>();
      // TODO Actually do the translation
      for (auto const& [key, val] : arg)
        {
          core::ComplexVector_T_sp vo = core::ComplexVector_T_O::make(val.size(), nil<core::T_O>());
          int i(0);
          for (auto ai : val) {
            vo->rowMajorAset(i++, core::DoubleFloat_O::create(ai));
          }
          core::Cons_sp cons = core::Cons_O::create(core::Integer_O::create(key),vo);
          return_list = core::Cons_O::create(cons, return_list);
        }
      return return_list;
    }
  };
};

namespace translate
{
  template <>
  struct from_object<std::map<uint32_t, std::vector<double>>>
  {
    typedef std::map<uint32_t, std::vector<double>> DeclareType;                             // (1)
    DeclareType _v;
    from_object(core::T_sp obj)
    {
      std::map<uint32_t, std::vector<double>> m;
      this->_v=m;// (3)
    }
  };
};
