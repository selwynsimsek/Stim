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
//s.def("circuit__getitem_uint32_t",&circuit__getitem_uint32_t);
//s.def("circuit__getitem_slice",&circuit__getitem_slice);
s.def("circuit-iadd",&circuit__iadd);
s.def("circuit-imul",&circuit__imul);
s.def("circuit-init",&circuit__init);
s.def("circuit-len",&circuit__len);
s.def("circuit-mul",&circuit__mul);
s.def("circuit-ne",&circuit__ne);
s.def("circuit-repr",&circuit__repr);
s.def("circuit-rmul",&circuit__rmul);
s.def("circuit-str",&circuit__str);
//s.def("circuit__append_int_array",&circuit__append_int_array);
//s.def("circuit__append_gate_target_array",&circuit__append_gate_target_array);
//s.def("circuit__append_circuit_instruction",&circuit__append_circuit_instruction);
//s.def("circuit__append_circuit_repeat_block",&circuit__append_circuit_repeat_block);
s.def("circuit__append_from_stim_program_text",&circuit__append_from_stim_program_text);
//s.def("circuit__approx_equals",&circuit__approx_equals);
s.def("circuit-clear",&circuit__clear);
//s.def("circuit__compile_detector_sampler",&circuit__compile_detector_sampler);
//s.def("circuit__compile_detector_sampler_seed",&circuit__compile_detector_sampler_seed);
//s.def("circuit__compile_m2d_converter",&circuit__compile_m2d_converter);
//s.def("circuit__compile_sampler",&circuit__compile_sampler);
//s.def("circuit__compile_sampler_seed",&circuit__compile_sampler_seed);
//s.def("circuit__compile_sampler_reference_sample",&circuit__compile_sampler_reference_sample);
//s.def("circuit__compile_sampler_reference_sample_seed",&circuit__compile_sampler_reference_sample_seed);
s.def("circuit-copy",&circuit__copy);
//s.def("circuit__count_determined_measurements",&circuit__count_determined_measurements);
//s.def("circuit__decomposed",&circuit__decomposed);
//s.def("circuit__detecting_regions",&circuit__detecting_regions);
//s.def("circuit__detecting_regions_targets_strings",&circuit__detecting_regions_targets_strings);
//s.def("circuit__detecting_regions_targets_floats",&circuit__detecting_regions_targets_floats);
//s.def("circuit__detecting_regions_targets_strings_ticks",&circuit__detecting_regions_targets_strings_ticks);
//s.def("circuit__detecting_regions_targets_floats_ticks",&circuit__detecting_regions_targets_floats_ticks);
//s.def("circuit__detecting_regions_ticks",&circuit__detecting_regions_ticks);
//s.def("circuit__detector_error_model",&circuit__detector_error_model);
//s.def("circuit__diagram_range_float",&circuit__diagram_range_float);
//s.def("circuit__diagram_range_dem_target",&circuit__diagram_range_dem_target);
//s.def("circuit__diagram_tick_float",&circuit__diagram_tick_float);
//s.def("circuit__diagram_tick_dem_target",&circuit__diagram_tick_dem_target);
//s.def("circuit__diagram_float",&circuit__diagram_float);
//s.def("circuit__diagram_dem_target",&circuit__diagram_dem_target);
//s.def("circuit__diagram",&circuit__diagram);
//s.def("circuit__explain_detector_error_model_errors",&circuit__explain_detector_error_model_errors);
//s.def("circuit__flattened",&circuit__flattened);
//s.def("circuit__from_file",&circuit__from_file);
s.def("circuit-generated",&circuit__generated);
//s.def("circuit__get_detector_coordinates",&circuit__get_detector_coordinates);
//s.def("circuit__get_detector_coordinates_only",&circuit__get_detector_coordinates_only);
s.def("circuit-get-final-qubit-coordinates",&circuit__get_final_qubit_coordinates);
//s.def("circuit__has_all_flows",&circuit__has_all_flows);
//s.def("circuit__has_flow",&circuit__has_flow);
//s.def("circuit__inverse",&circuit__inverse);
//s.def("circuit__likeliest_error_sat_problem_wdimacs",&circuit__likeliest_error_sat_problem_wdimacs);
//s.def("circuit__num_detectors",&circuit__num_detectors);
//s.def("circuit__num_measurements",&circuit__num_measurements);
//s.def("circuit__num_observables",&circuit__num_observables);
//s.def("circuit__num_qubits",&circuit__num_qubits);
//s.def("circuit__num_sweep_bits",&circuit__num_sweep_bits);
//s.def("circuit__num_ticks",&circuit__num_ticks);
//s.def("circuit__reference_sample",&circuit__reference_sample);
//s.def("circuit__search_for_undetectable_logical_errors",&circuit__search_for_undetectable_logical_errors);
//s.def("circuit__shortest_error_sat_problem_dimacs",&circuit__shortest_error_sat_problem_dimacs);
//s.def("circuit__shortest_graphlike_error",&circuit__shortest_graphlike_error);
//s.def("circuit__to_file",&circuit__to_file);
//s.def("circuit__to_qasm",&circuit__to_qasm);
//s.def("circuit__to_tableau",&circuit__to_tableau);
//s.def("circuit__with_inlined_feedback",&circuit__with_inlined_feedback);
//s.def("circuit__without_noise",&circuit__without_noise);
//s.def("circuit_error_location__flipped_measurement_p",&circuit_error_location__flipped_measurement_p);
//s.def("circuit_error_location__flipped_measurement",&circuit_error_location__flipped_measurement);
//s.def("circuit_error_location__flipped_pauli_product",&circuit_error_location__flipped_pauli_product);
//s.def("circuit_error_location__instruction_targets",&circuit_error_location__instruction_targets);
//s.def("circuit_error_location__stack_frames",&circuit_error_location__stack_frames);
//s.def("circuit_error_location__tick_offset",&circuit_error_location__tick_offset);
//s.def("circuit_error_location_stack_frame__init",&circuit_error_location_stack_frame__init);
//s.def("circuit_error_location_stack_frame__offset",&circuit_error_location_stack_frame__offset);
//s.def("circuit_error_location_stack_frame__repetitions_arg",&circuit_error_location_stack_frame__repetitions_arg);
//s.def("circuit_error_location_stack_frame__iteration_index",&circuit_error_location_stack_frame__iteration_index);
//s.def("circuit_instruction__eq",&circuit_instruction__eq);
//s.def("circuit_instruction__init_ints",&circuit_instruction__init_ints);
//s.def("circuit_instruction__init_gate_targets",&circuit_instruction__init_gate_targets);
//s.def("circuit_instruction__ne",&circuit_instruction__ne);
//s.def("circuit_instruction__repr",&circuit_instruction__repr);
//s.def("circuit_instruction__str",&circuit_instruction__str);
//s.def("circuit_instruction__gate_args_copy",&circuit_instruction__gate_args_copy);
//s.def("circuit_instruction__name",&circuit_instruction__name);
//s.def("circuit_instruction__targets_copy",&circuit_instruction__targets_copy);
//s.def("circuit_repeat_block__eq",&circuit_repeat_block__eq);
//s.def("circuit_repeat_block__init",&circuit_repeat_block__init);
//s.def("circuit_repeat_block__ne",&circuit_repeat_block__ne);
//s.def("circuit_repeat_block__repr",&circuit_repeat_block__repr);
//s.def("circuit_repeat_block__body_copy",&circuit_repeat_block__body_copy);
//s.def("circuit_repeat_block__name",&circuit_repeat_block__name);
//s.def("circuit_repeat_block__repeat_count",&circuit_repeat_block__repeat_count);
//s.def("circuit_targets_inside_instruction__init",&circuit_targets_inside_instruction__init);
//s.def("circuit_targets_inside_instruction__args",&circuit_targets_inside_instruction__args);
//s.def("circuit_targets_inside_instruction__gate_p",&circuit_targets_inside_instruction__gate_p);
//s.def("circuit_targets_inside_instruction__gate",&circuit_targets_inside_instruction__gate);
//s.def("circuit_targets_inside_instruction__target_range_end",&circuit_targets_inside_instruction__target_range_end);
//s.def("circuit_targets_inside_instruction__target_range_start",&circuit_targets_inside_instruction__target_range_start);
//s.def("circuit_targets_inside_instruction__targets_in_range",&circuit_targets_inside_instruction__targets_in_range);
//s.def("compiled_dem_sampler__sample",&compiled_dem_sampler__sample);
//s.def("compiled_dem_sampler__sample_recorded_errors_to_replay",&compiled_dem_sampler__sample_recorded_errors_to_replay);
//s.def("compiled_dem_sampler__sample_write",&compiled_dem_sampler__sample_write);
//s.def("compiled_detector_sampler__init",&compiled_detector_sampler__init);
//s.def("compiled_detector_sampler__init_seed",&compiled_detector_sampler__init_seed);
//s.def("compiled_detector_sampler__repr",&compiled_detector_sampler__repr);
//s.def("compiled_detector_sampler__sample",&compiled_detector_sampler__sample);
//s.def("compiled_detector_sampler__sample_write",&compiled_detector_sampler__sample_write);
//s.def("compiled_measurement_sampler__init",&compiled_measurement_sampler__init);
//s.def("compiled_measurement_sampler__repr",&compiled_measurement_sampler__repr);
//s.def("compiled_measurement_sampler__sample",&compiled_measurement_sampler__sample);
//s.def("compiled_measurement_sampler__sample_write",&compiled_measurement_sampler__sample_write);
//s.def("CompiledMeasurementsToDetectionEventsConverter__init",&CompiledMeasurementsToDetectionEventsConverter__init);
//s.def("CompiledMeasurementsToDetectionEventsConverter__repr",&CompiledMeasurementsToDetectionEventsConverter__repr);
//s.def("CompiledMeasurementsToDetectionEventsConverter__convert",&CompiledMeasurementsToDetectionEventsConverter__convert);
//s.def("CompiledMeasurementsToDetectionEventsConverter__convert_file",&CompiledMeasurementsToDetectionEventsConverter__convert_file);
//s.def("DemInstruction__eq",&DemInstruction__eq);
//s.def("DemInstruction__init",&DemInstruction__init);
//s.def("DemInstruction__ne",&DemInstruction__ne);
//s.def("DemInstruction__repr",&DemInstruction__repr);
//s.def("DemInstruction__str",&DemInstruction__str);
//s.def("DemInstruction__args_copy",&DemInstruction__args_copy);
//s.def("DemInstruction__targets_copy",&DemInstruction__targets_copy);
//s.def("DemInstruction__type",&DemInstruction__type);
//s.def("DemRepeatBlock__eq",&DemRepeatBlock__eq);
//s.def("DemRepeatBlock__init",&DemRepeatBlock__init);
//s.def("DemRepeatBlock__ne",&DemRepeatBlock__ne);
//s.def("DemRepeatBlock__repr",&DemRepeatBlock__repr);
//s.def("DemRepeatBlock__body_copy",&DemRepeatBlock__body_copy);
//s.def("DemRepeatBlock__repeat_count",&DemRepeatBlock__repeat_count);
//s.def("DemRepeatBlock__type",&DemRepeatBlock__type);
//s.def("DemTarget__eq",&DemTarget__eq);
//s.def("DemTarget__ne",&DemTarget__ne);
//s.def("DemTarget__repr",&DemTarget__repr);
//s.def("DemTarget__str",&DemTarget__str);
//s.def("DemTarget__is_logical_observable_id",&DemTarget__is_logical_observable_id);
//s.def("DemTarget__is_relative_detector_id",&DemTarget__is_relative_detector_id);
//s.def("DemTarget__is_separator",&DemTarget__is_separator);
//s.def("DemTarget__logical_observable_id",&DemTarget__logical_observable_id);
//s.def("DemTarget__relative_detector_id",&DemTarget__relative_detector_id);
//s.def("DemTarget__separator",&DemTarget__separator);
//s.def("DemTarget__val",&DemTarget__val);
//s.def("DemTargetWithCoords__init",&DemTargetWithCoords__init);
//s.def("DemTargetWithCoords__coords",&DemTargetWithCoords__coords);
//s.def("DemTargetWithCoords__dem_target",&DemTargetWithCoords__dem_target);
//s.def("DetectorErrorModel__add",&DetectorErrorModel__add);
//s.def("DetectorErrorModel__eq",&DetectorErrorModel__eq);
//s.def("DetectorErrorModel__getitem",&DetectorErrorModel__getitem);
//s.def("DetectorErrorModel__iadd",&DetectorErrorModel__iadd);
//s.def("DetectorErrorModel__imul",&DetectorErrorModel__imul);
//s.def("DetectorErrorModel__init",&DetectorErrorModel__init);
//s.def("DetectorErrorModel__len",&DetectorErrorModel__len);
//s.def("DetectorErrorModel__mul",&DetectorErrorModel__mul);
//s.def("DetectorErrorModel__ne",&DetectorErrorModel__ne);
//s.def("DetectorErrorModel__repr",&DetectorErrorModel__repr);
//s.def("DetectorErrorModel__rmul",&DetectorErrorModel__rmul);
//s.def("DetectorErrorModel__str",&DetectorErrorModel__str);
//s.def("DetectorErrorModel__append",&DetectorErrorModel__append);
//s.def("DetectorErrorModel__approx_equals",&DetectorErrorModel__approx_equals);
//s.def("DetectorErrorModel__clear",&DetectorErrorModel__clear);
//s.def("DetectorErrorModel__compile_sampler",&DetectorErrorModel__compile_sampler);
//s.def("DetectorErrorModel__copy",&DetectorErrorModel__copy);
//s.def("DetectorErrorModel__diagram",&DetectorErrorModel__diagram);
//s.def("DetectorErrorModel__flattened",&DetectorErrorModel__flattened);
//s.def("DetectorErrorModel__from_file",&DetectorErrorModel__from_file);
//s.def("DetectorErrorModel__get_detector_coordinates",&DetectorErrorModel__get_detector_coordinates);
//s.def("DetectorErrorModel__num_detectors",&DetectorErrorModel__num_detectors);
//s.def("DetectorErrorModel__num_errors",&DetectorErrorModel__num_errors);
//s.def("DetectorErrorModel__num_observables",&DetectorErrorModel__num_observables);
//s.def("DetectorErrorModel__rounded",&DetectorErrorModel__rounded);
//s.def("DetectorErrorModel__shortest_graphlike_error",&DetectorErrorModel__shortest_graphlike_error);
//s.def("DetectorErrorModel__to_file",&DetectorErrorModel__to_file);
//s.def("ExplainedError",&ExplainedError);
//s.def("ExplainedError__init",&ExplainedError__init);
//s.def("ExplainedError__circuit_error_locations",&ExplainedError__circuit_error_locations);
//s.def("ExplainedError__dem_error_terms",&ExplainedError__dem_error_terms);
//s.def("FlipSimulator",&FlipSimulator);
//s.def("FlipSimulator__init",&FlipSimulator__init);
//s.def("FlipSimulator__batch_size",&FlipSimulator__batch_size);
//s.def("FlipSimulator__broadcast_pauli_errors",&FlipSimulator__broadcast_pauli_errors);
//s.def("FlipSimulator__do",&FlipSimulator__do);
//s.def("FlipSimulator__get_detector_flips",&FlipSimulator__get_detector_flips);
//s.def("FlipSimulator__get_measurement_flips",&FlipSimulator__get_measurement_flips);
//s.def("FlipSimulator__get_observable_flips",&FlipSimulator__get_observable_flips);
//s.def("FlipSimulator__num_detectors",&FlipSimulator__num_detectors);
//s.def("FlipSimulator__num_measurements",&FlipSimulator__num_measurements);
//s.def("FlipSimulator__num_observables",&FlipSimulator__num_observables);
//s.def("FlipSimulator__num_qubits",&FlipSimulator__num_qubits);
//s.def("FlipSimulator__peek_pauli_flips",&FlipSimulator__peek_pauli_flips);
//s.def("FlipSimulator__set_pauli_flip",&FlipSimulator__set_pauli_flip);
//s.def("FlippedMeasurement__init",&FlippedMeasurement__init);
//s.def("FlippedMeasurement__observable",&FlippedMeasurement__observable);
//s.def("FlippedMeasurement__record_index",&FlippedMeasurement__record_index);
//s.def("Flow__eq",&Flow__eq);
//s.def("Flow__init",&Flow__init);
//s.def("Flow__ne",&Flow__ne);
//s.def("Flow__repr",&Flow__repr);
//s.def("Flow__str",&Flow__str);
//s.def("Flow__input_copy",&Flow__input_copy);
//s.def("Flow__measurements_copy",&Flow__measurements_copy);
//s.def("Flow__output_copy",&Flow__output_copy);
//s.def("GateData__eq",&GateData__eq);
//s.def("GateData__init",&GateData__init);
//s.def("GateData__ne",&GateData__ne);
//s.def("GateData__repr",&GateData__repr);
//s.def("GateData__str",&GateData__str);
//s.def("GateData__aliases",&GateData__aliases);
//s.def("GateData__flows",&GateData__flows);
//s.def("GateData__generalized_inverse",&GateData__generalized_inverse);
//s.def("GateData__inverse",&GateData__inverse);
//s.def("GateData__is_noisy_gate",&GateData__is_noisy_gate);
//s.def("GateData__is_reset",&GateData__is_reset);
//s.def("GateData__is_single_qubit_gate",&GateData__is_single_qubit_gate);
//s.def("GateData__is_two_qubit_gate",&GateData__is_two_qubit_gate);
//s.def("GateData__is_unitary",&GateData__is_unitary);
//s.def("GateData__name",&GateData__name);
//s.def("GateData__num_parens_arguments_range",&GateData__num_parens_arguments_range);
//s.def("GateData__produces_measurements",&GateData__produces_measurements);
//s.def("GateData__tableau",&GateData__tableau);
//s.def("GateData__takes_measurement_record_targets",&GateData__takes_measurement_record_targets);
//s.def("GateData__takes_pauli_targets",&GateData__takes_pauli_targets);
//s.def("GateData__unitary_matrix",&GateData__unitary_matrix);
//s.def("GateTarget__eq",&GateTarget__eq);
//s.def("GateTarget__init",&GateTarget__init);
//s.def("GateTarget__ne",&GateTarget__ne);
//s.def("GateTarget__repr",&GateTarget__repr);
//s.def("GateTarget__is_combiner",&GateTarget__is_combiner);
//s.def("GateTarget__is_inverted_result_target",&GateTarget__is_inverted_result_target);
//s.def("GateTarget__is_measurement_record_target",&GateTarget__is_measurement_record_target);
//s.def("GateTarget__is_qubit_target",&GateTarget__is_qubit_target);
//s.def("GateTarget__is_sweep_bit_target",&GateTarget__is_sweep_bit_target);
//s.def("GateTarget__is_x_target",&GateTarget__is_x_target);
//s.def("GateTarget__is_y_target",&GateTarget__is_y_target);
//s.def("GateTarget__is_z_target",&GateTarget__is_z_target);
//s.def("GateTarget__pauli_type",&GateTarget__pauli_type);
//s.def("GateTarget__qubit_value",&GateTarget__qubit_value);
//s.def("GateTarget__value",&GateTarget__value);
//s.def("GateTargetWithCoords__init",&GateTargetWithCoords__init);
//s.def("GateTargetWithCoords__coords",&GateTargetWithCoords__coords);
//s.def("GateTargetWithCoords__gate_target",&GateTargetWithCoords__gate_target);
//s.def("PauliString__add",&PauliString__add);
//s.def("PauliString__eq",&PauliString__eq);
//s.def("PauliString__getitem",&PauliString__getitem);
//s.def("PauliString__iadd",&PauliString__iadd);
//s.def("PauliString__imul",&PauliString__imul);
//s.def("PauliString__init",&PauliString__init);
//s.def("PauliString__itruediv",&PauliString__itruediv);
//s.def("PauliString__len",&PauliString__len);
//s.def("PauliString__mul",&PauliString__mul);
//s.def("PauliString__ne",&PauliString__ne);
//s.def("PauliString__neg",&PauliString__neg);
//s.def("PauliString__pos",&PauliString__pos);
//s.def("PauliString__repr",&PauliString__repr);
//s.def("PauliString__rmul",&PauliString__rmul);
//s.def("PauliString__setitem",&PauliString__setitem);
//s.def("PauliString__str",&PauliString__str);
//s.def("PauliString__truediv",&PauliString__truediv);
//s.def("PauliString__after",&PauliString__after);
//s.def("PauliString__before",&PauliString__before);
//s.def("PauliString__commutes",&PauliString__commutes);
//s.def("PauliString__copy",&PauliString__copy);
//s.def("PauliString__from_numpy",&PauliString__from_numpy);
//s.def("PauliString__from_unitary_matrix",&PauliString__from_unitary_matrix);
//s.def("PauliString__iter_all",&PauliString__iter_all);
//s.def("PauliString__pauli_indices",&PauliString__pauli_indices);
//s.def("PauliString__random",&PauliString__random);
//s.def("PauliString__sign",&PauliString__sign);
//s.def("PauliString__to_numpy",&PauliString__to_numpy);
//s.def("PauliString__to_tableau",&PauliString__to_tableau);
//s.def("PauliString__to_unitary_matrix",&PauliString__to_unitary_matrix);
//s.def("PauliString__weight",&PauliString__weight);
//s.def("PauliStringIterator__iter",&PauliStringIterator__iter);
//s.def("PauliStringIterator__next",&PauliStringIterator__next);
//s.def("Tableau__add",&Tableau__add);
//s.def("Tableau__call",&Tableau__call);
//s.def("Tableau__eq",&Tableau__eq);
//s.def("Tableau__iadd",&Tableau__iadd);
//s.def("Tableau__init",&Tableau__init);
//s.def("Tableau__len",&Tableau__len);
//s.def("Tableau__mul",&Tableau__mul);
//s.def("Tableau__ne",&Tableau__ne);
//s.def("Tableau__pow",&Tableau__pow);
//s.def("Tableau__repr",&Tableau__repr);
//s.def("Tableau__str",&Tableau__str);
//s.def("Tableau__append",&Tableau__append);
//s.def("Tableau__copy",&Tableau__copy);
//s.def("Tableau__from_circuit",&Tableau__from_circuit);
//s.def("Tableau__from_conjugated_generators",&Tableau__from_conjugated_generators);
//s.def("Tableau__from_named_gate",&Tableau__from_named_gate);
//s.def("Tableau__from_numpy",&Tableau__from_numpy);
//s.def("Tableau__from_stabilizers",&Tableau__from_stabilizers);
//s.def("Tableau__from_state_vector",&Tableau__from_state_vector);
//s.def("Tableau__from_unitary_matrix",&Tableau__from_unitary_matrix);
//s.def("Tableau__inverse",&Tableau__inverse);
//s.def("Tableau__inverse_x_output",&Tableau__inverse_x_output);
//s.def("Tableau__inverse_x_output_pauli",&Tableau__inverse_x_output_pauli);
//s.def("Tableau__inverse_y_output",&Tableau__inverse_y_output);
//s.def("Tableau__inverse_y_output_pauli",&Tableau__inverse_y_output_pauli);
//s.def("Tableau__inverse_z_output",&Tableau__inverse_z_output);
//s.def("Tableau__inverse_z_output_pauli",&Tableau__inverse_z_output_pauli);
//s.def("Tableau__iter_all",&Tableau__iter_all);
//s.def("Tableau__prepend",&Tableau__prepend);
//s.def("Tableau__random",&Tableau__random);
//s.def("Tableau__then",&Tableau__then);
//s.def("Tableau__to_circuit",&Tableau__to_circuit);
//s.def("Tableau__to_numpy",&Tableau__to_numpy);
//s.def("Tableau__to_pauli_string",&Tableau__to_pauli_string);
//s.def("Tableau__to_stabilizers",&Tableau__to_stabilizers);
//s.def("Tableau__to_state_vector",&Tableau__to_state_vector);
//s.def("Tableau__to_unitary_matrix",&Tableau__to_unitary_matrix);
//s.def("Tableau__x_output",&Tableau__x_output);
//s.def("Tableau__x_output_pauli",&Tableau__x_output_pauli);
//s.def("Tableau__x_sign",&Tableau__x_sign);
//s.def("Tableau__y_output",&Tableau__y_output);
//s.def("Tableau__y_output_pauli",&Tableau__y_output_pauli);
//s.def("Tableau__y_sign",&Tableau__y_sign);
//s.def("Tableau__z_output",&Tableau__z_output);
//s.def("Tableau__z_output_pauli",&Tableau__z_output_pauli);
//s.def("Tableau__z_sign",&Tableau__z_sign);
//s.def("TableauIterator__iter",&TableauIterator__iter);
//s.def("TableauIterator__next",&TableauIterator__next);
//s.def("TableauSimulator__init",&TableauSimulator__init);
//s.def("TableauSimulator__c_xyz",&TableauSimulator__c_xyz);
//s.def("TableauSimulator__c_zyx",&TableauSimulator__c_zyx);
//s.def("TableauSimulator__canonical_stabilizers",&TableauSimulator__canonical_stabilizers);
//s.def("TableauSimulator__cnot",&TableauSimulator__cnot);
//s.def("TableauSimulator__copy",&TableauSimulator__copy);
//s.def("TableauSimulator__current_inverse_tableau",&TableauSimulator__current_inverse_tableau);
//s.def("TableauSimulator__current_measurement_record",&TableauSimulator__current_measurement_record);
//s.def("TableauSimulator__cx",&TableauSimulator__cx);
//s.def("TableauSimulator__cy",&TableauSimulator__cy);
//s.def("TableauSimulator__cz",&TableauSimulator__cz);
//s.def("TableauSimulator__depolarize1",&TableauSimulator__depolarize1);
//s.def("TableauSimulator__depolarize2",&TableauSimulator__depolarize2);
//s.def("TableauSimulator__do",&TableauSimulator__do);
//s.def("TableauSimulator__do_circuit",&TableauSimulator__do_circuit);
//s.def("TableauSimulator__do_pauli_string",&TableauSimulator__do_pauli_string);
//s.def("TableauSimulator__do_tableau",&TableauSimulator__do_tableau);
//s.def("TableauSimulator__h",&TableauSimulator__h);
//s.def("TableauSimulator__h_xy",&TableauSimulator__h_xy);
//s.def("TableauSimulator__h_xz",&TableauSimulator__h_xz);
//s.def("TableauSimulator__h_yz",&TableauSimulator__h_yz);
//s.def("TableauSimulator__iswap",&TableauSimulator__iswap);
//s.def("TableauSimulator__iswap_dag",&TableauSimulator__iswap_dag);
//s.def("TableauSimulator__measure",&TableauSimulator__measure);
//s.def("TableauSimulator__measure_kickback",&TableauSimulator__measure_kickback);
//s.def("TableauSimulator__measure_many",&TableauSimulator__measure_many);
//s.def("TableauSimulator__measure_observable",&TableauSimulator__measure_observable);
//s.def("TableauSimulator__num_qubits",&TableauSimulator__num_qubits);
//s.def("TableauSimulator__peek_bloch",&TableauSimulator__peek_bloch);
//s.def("TableauSimulator__peek_observable_expectation",&TableauSimulator__peek_observable_expectation);
//s.def("TableauSimulator__peek_x",&TableauSimulator__peek_x);
//s.def("TableauSimulator__peek_y",&TableauSimulator__peek_y);
//s.def("TableauSimulator__peek_z",&TableauSimulator__peek_z);
//s.def("TableauSimulator__postselect_observable",&TableauSimulator__postselect_observable);
//s.def("TableauSimulator__postselect_x",&TableauSimulator__postselect_x);
//s.def("TableauSimulator__postselect_y",&TableauSimulator__postselect_y);
//s.def("TableauSimulator__postselect_z",&TableauSimulator__postselect_z);
//s.def("TableauSimulator__reset",&TableauSimulator__reset);
//s.def("TableauSimulator__reset_x",&TableauSimulator__reset_x);
//s.def("TableauSimulator__reset_y",&TableauSimulator__reset_y);
//s.def("TableauSimulator__reset_z",&TableauSimulator__reset_z);
//s.def("TableauSimulator__s",&TableauSimulator__s);
//s.def("TableauSimulator__s_dag",&TableauSimulator__s_dag);
//s.def("TableauSimulator__set_inverse_tableau",&TableauSimulator__set_inverse_tableau);
//s.def("TableauSimulator__set_num_qubits",&TableauSimulator__set_num_qubits);
//s.def("TableauSimulator__set_state_from_stabilizers",&TableauSimulator__set_state_from_stabilizers);
//s.def("TableauSimulator__set_state_from_state_vector",&TableauSimulator__set_state_from_state_vector);
//s.def("TableauSimulator__sqrt_x",&TableauSimulator__sqrt_x);
//s.def("TableauSimulator__sqrt_x_dag",&TableauSimulator__sqrt_x_dag);
//s.def("TableauSimulator__sqrt_y",&TableauSimulator__sqrt_y);
//s.def("TableauSimulator__sqrt_y_dag",&TableauSimulator__sqrt_y_dag);
//s.def("TableauSimulator__state_vector",&TableauSimulator__state_vector);
//s.def("TableauSimulator__swap",&TableauSimulator__swap);
//s.def("TableauSimulator__x",&TableauSimulator__x);
//s.def("TableauSimulator__x_error",&TableauSimulator__x_error);
//s.def("TableauSimulator__xcx",&TableauSimulator__xcx);
//s.def("TableauSimulator__xcy",&TableauSimulator__xcy);
//s.def("TableauSimulator__xcz",&TableauSimulator__xcz);
//s.def("TableauSimulator__y",&TableauSimulator__y);
//s.def("TableauSimulator__y_error",&TableauSimulator__y_error);
//s.def("TableauSimulator__ycx",&TableauSimulator__ycx);
//s.def("TableauSimulator__ycy",&TableauSimulator__ycy);
//s.def("TableauSimulator__ycz",&TableauSimulator__ycz);
//s.def("TableauSimulator__z",&TableauSimulator__z);
//s.def("TableauSimulator__z_error",&TableauSimulator__z_error);
//s.def("TableauSimulator__zcx",&TableauSimulator__zcx);
//s.def("TableauSimulator__zcy",&TableauSimulator__zcy);
//s.def("TableauSimulator__zcz",&TableauSimulator__zcz);

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
          for (auto ai = val.begin(); ai != val.end(); ai++) {
            vo->rowMajorAset(i++, core::DoubleFloat_O::create(*ai));
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
