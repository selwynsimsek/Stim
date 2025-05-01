#include <fmt/format.h>
#include <clasp/clasp.h>
#include "stim.h"

// clbind API to Stim, inspired by the pybind API.

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

using namespace stim;

namespace clasp_stim {
  class CircuitOperation {};
  class CompiledM2DConverter {};
  class CompiledDemSampler {};
  class CompiledDetectorSampler {};
  class CompiledMeasurementSampler {};
  class CompiledM2DSampler {};
  class CircuitInstruction {};
  class CircuitRepeatBlock {};
  class ExposedDemInstruction {};
    class ExposedDemTarget {};
  class ExposedDemRepeatBlock {};
    class DiagramHelper {};

  template<typename K, typename V> std::map<V, K> reverse_map(const std::map<K, V>& m);
  int stim_main(const std::vector<std::string> args);
  GateTarget target_rec(int32_t lookback);
  GateTarget target_inv_target(const GateTarget &qubit);
  GateTarget target_inv_uint32_t(const uint32_t &qubit);
  GateTarget target_x_target(const GateTarget &qubit, bool invert);
  GateTarget target_x_uint32_t(const uint32_t &qubit, bool invert);
  GateTarget target_y_target(const GateTarget &qubit, bool invert);
  GateTarget target_y_uint32_t(const uint32_t &qubit, bool invert);
  GateTarget target_z_target(const GateTarget &qubit, bool invert);
  GateTarget target_z_uint32_t(const uint32_t &qubit, bool invert);
  std::vector<GateTarget> target_combined_paulis_gate_targets(std::vector<GateTarget> &paulis, bool invert);
  std::vector<GateTarget> target_combined_paulis_string(const FlexPauliString &paulis, bool invert);
  GateTarget target_pauli_string(uint32_t qubit_index, const std::string &pauli, bool invert);
  GateTarget target_pauli_uint8_t(uint32_t qubit_index, const uint8_t &pauli, bool invert);
  GateTarget target_sweep_bit(uint32_t qubit);

  GateTarget gate_target_from_target_str(std::string v);
  FlexPauliString flex_pauli_from_text(std::string v);
  FlexPauliString pauli_iterator_get_current(const PauliStringIterator<MAX_BITWORD_WIDTH> iterator);

  // Stim v1.13 API Reference
  // Each Python function or variable must be followed by either one or more corresponding clbind function declarations to be exposed, or a reason why this oughtn't be done.

//     stim.Circuit
//         stim.Circuit.__add__
  Circuit circuit__add(Circuit &self, Circuit &c2);
//         stim.Circuit.__eq__
  bool circuit__eq(Circuit &self, Circuit &c2);
//         stim.Circuit.__getitem__
  core::T_sp circuit__getitem_uint32_t(Circuit &self,uint32_t index);
  Circuit circuit__getitem_slice(Circuit &self, uint32_t start, uint32_t stop, uint32_t step);
//         stim.Circuit.__iadd__
  void circuit__iadd(Circuit &self, Circuit &second);
//         stim.Circuit.__imul__
  void circuit__imul(Circuit &self, uint32_t repetitions);
//         stim.Circuit.__init__
  Circuit circuit__init(std::string program_text);
//         stim.Circuit.__len__
  uint32_t circuit__len(Circuit &self);
//         stim.Circuit.__mul__
  Circuit circuit__mul(Circuit &self, uint32_t repetitions);
//         stim.Circuit.__ne__
  bool circuit__ne(Circuit &self, Circuit &c2);
//         stim.Circuit.__repr__
  std::string circuit__repr(Circuit &self);
//         stim.Circuit.__rmul__
  Circuit circuit__rmul(Circuit &self, uint32_t repetitions);
//         stim.Circuit.__str__
  std::string circuit__str(Circuit &self);
//         stim.Circuit.append
  void circuit__append_int_array(Circuit &self, std::string name, std::vector<int> targets, std::vector<double> arg);
  void circuit__append_gate_target_array(Circuit &self, std::string name, std::vector<GateTarget> targets, std::vector<double> arg);
  void circuit__append_circuit_operation(Circuit &self, CircuitOperation operation);
  void circuit__append_circuit_repeat_block(Circuit &self, CircuitRepeatBlock repeat_block);
//         stim.Circuit.append_from_stim_program_text
  void circuit__append_from_stim_program_text(Circuit &self, std::string stim_program_text);
//         stim.Circuit.approx_equals
  bool circuit__approx_equals(Circuit &self, Circuit &other, float atol);
//         stim.Circuit.clear
  void circuit__clear(Circuit &self);
  //         stim.Circuit.compile_detector_sampler
  CompiledDetectorSampler circuit__compile_detector_sampler(Circuit &self);
  CompiledDetectorSampler circuit__compile_detector_sampler_seed(Circuit &self,uint32_t seed);
//         stim.Circuit.compile_m2d_converter
  CompiledM2DConverter circuit__compile_m2d_converter(Circuit &self, bool skip_reference_sample);
  //         stim.Circuit.compile_sampler
  CompiledMeasurementSampler circuit__compile_sampler(Circuit &self, bool skip_reference_sample);
  CompiledMeasurementSampler circuit__compile_sampler_seed(Circuit &self, bool skip_reference_sample,uint32_t seedn);
  CompiledMeasurementSampler circuit__compile_sampler_reference_sample(Circuit &self, bool skip_reference_sample, core::Array_sp reference_sample);
  CompiledMeasurementSampler circuit__compile_sampler_reference_sample_seed(Circuit &self, bool skip_reference_sample, core::Array_sp reference_sample,uint32_t seed);
//         stim.Circuit.copy
  Circuit circuit__copy(Circuit &self);
//         stim.Circuit.count_determined_measurements
  uint32_t circuit__count_determined_measurements(Circuit &self);
//         stim.Circuit.decomposed
  Circuit circuit__decomposed(Circuit &self);
//         stim.Circuit.detecting_regions
  core::T_sp circuit__detecting_regions(Circuit &self);
  // T_sp circuit__detecting_regions_targets_dem_targets(Circuit &self, std::vector<DemTarget> targets);
  core::T_sp circuit__detecting_regions_targets_strings(Circuit &self, std::vector<std::string> targets);
  core::T_sp circuit__detecting_regions_targets_floats(Circuit &self, std::vector<std::vector<float>> targets);
  // T_sp circuit__detecting_regions_targets_dem_targets_ticks(Circuit &self, std::vector<DemTarget> targets, std::vector<int> ticks);
  core::T_sp circuit__detecting_regions_targets_strings_ticks(Circuit &self, std::vector<std::string> targets, std::vector<int> ticks);
  core::T_sp circuit__detecting_regions_targets_floats_ticks(Circuit &self, std::vector<std::vector<float>> targets, std::vector<int> ticks);
  core::T_sp circuit__detecting_regions_ticks(Circuit &self, std::vector<int> ticks);
//         stim.Circuit.detector_error_model
  DetectorErrorModel circuit__detector_error_model(Circuit &self, bool decompose_errors, bool flatten_loops, bool allow_gauge_detectors, bool approximate_disjoint_errors, bool ignore_decomposition_failures, bool block_decomposition_from_introducting_remnant_edges);
//         stim.Circuit.diagram
      DiagramHelper circuit__diagram_range_float(Circuit &self, std::string type,
                                                          uint32_t start, uint32_t stop, uint32_t range,
                                                          std::vector<std::vector<float>> filter_coords);
  DiagramHelper circuit__diagram_range_dem_target(Circuit &self, std::string type,
                                                               uint32_t start, uint32_t stop, uint32_t range,
                                                               std::vector<DemTarget> filter_coords);
  DiagramHelper circuit__diagram_tick_float(Circuit &self, std::string type,
                                                    uint32_t tick,
                                                    std::vector<std::vector<float>> filter_coords);
  DiagramHelper circuit__diagram_tick_dem_target(Circuit &self, std::string type,
                                                          uint32_t tick,
                                                 std::vector<DemTarget> filter_coords);
  DiagramHelper circuit__diagram_float(Circuit &self, std::string type,
                                            std::vector<std::vector<float>> filter_coords);
  DiagramHelper circuit__diagram_dem_target(Circuit &self, std::string type,
                                            std::vector<DemTarget> filter_coords);
  DiagramHelper circuit__diagram(Circuit &self, std::string type);
//         stim.Circuit.explain_detector_error_model_errors
  std::vector<ExplainedError> circuit__explain_detector_error_model_errors(Circuit &self, DetectorErrorModel dem_filter, bool reduce_to_one_representative_error);
//         stim.Circuit.flattened
  Circuit circuit__flattened(Circuit &self);
//         stim.Circuit.from_file
  Circuit circuit__from_file(std::string file);
//         stim.Circuit.generated
  Circuit circuit__generated(std::string code_task, uint32_t distance, uint32_t rounds,
                             float after_clifford_depolarization, float before_round_data_depolarization,
                             float before_measure_flip_probability, float after_reset_flip_probability);
  //         stim.Circuit.get_detector_coordinates
  core::T_sp circuit__get_detector_coordinates(Circuit self);
  core::T_sp circuit__get_detector_coordinates_only(Circuit self, std::vector<uint32_t> only);
//         stim.Circuit.get_final_qubit_coordinates
  core::T_sp circuit__get_final_qubit_coordinates(Circuit self);
//         stim.Circuit.has_all_flows
  bool circuit__has_all_flows(Circuit self, std::vector<Flow<MAX_BITWORD_WIDTH>> flows, bool unsigned_p);
  //         stim.Circuit.has_flow
  bool circuit__has_flow(Circuit self, Flow<MAX_BITWORD_WIDTH> flow, bool unsigned_p);
//         stim.Circuit.inverse
  Circuit circuit__inverse(Circuit self);
//         stim.Circuit.likeliest_error_sat_problem
  std::string circuit__likeliest_error_sat_problem_wdimacs(Circuit self, uint32_t quantization);
//         stim.Circuit.num_detectors
  uint32_t circuit__num_detectors(Circuit self);
  //         stim.Circuit.num_measurements
  uint32_t circuit__num_measurements(Circuit self);
  //         stim.Circuit.num_observables
  uint32_t circuit__num_observables(Circuit self);
  //         stim.Circuit.num_qubits
  uint32_t circuit__num_qubits(Circuit self);
  //         stim.Circuit.num_sweep_bits
  uint32_t circuit__num_sweep_bits(Circuit self);
  //         stim.Circuit.num_ticks
  uint32_t circuit__num_ticks(Circuit self);
//         stim.Circuit.reference_sample
  core::T_sp circuit__reference_sample(Circuit self, bool bit_packed);
//         stim.Circuit.search_for_undetectable_logical_errors
  std::vector<ExplainedError> circuit__search_for_undetectable_logical_errors(Circuit self,
                                                                              uint32_t a, uint32_t b,
                                                                              bool c, bool d);
//         stim.Circuit.shortest_error_sat_problem
  std::string circuit__shortest_error_sat_problem_dimacs(Circuit self);
//         stim.Circuit.shortest_graphlike_error
  std::vector<ExplainedError> circuit__shortest_graphlike_error(Circuit self, bool a, bool b);
//         stim.Circuit.to_file
  void circuit__to_file(Circuit self, std::string file);
//         stim.Circuit.to_qasm
  std::string circuit__to_qasm(Circuit self, uint32_t open_qasm_version, bool skip_dets_and_obs);
//         stim.Circuit.to_tableau
  Tableau<MAX_BITWORD_WIDTH> circuit__to_tableau(Circuit self, bool ignore_noise, bool ignore_measurement,
                                                 bool ignore_reset);
//         stim.Circuit.with_inlined_feedback
  Circuit circuit__with_inlined_feedback(Circuit self);
//         stim.Circuit.without_noise
  Circuit circuit__without_noise(Circuit self);
//     stim.CircuitErrorLocation
//         stim.CircuitErrorLocation.__init__
  // Not sure if it merits a constructor, and the flipped_measurement argument isn't clear
  //         stim.CircuitErrorLocation.flipped_measurement
  bool circuit_error_location__flipped_measurement_p(CircuitErrorLocation self);
  FlippedMeasurement circuit_error_location__flipped_measurement(CircuitErrorLocation self);
//         stim.CircuitErrorLocation.flipped_pauli_product
  std::vector<GateTargetWithCoords> circuit_error_location__flipped_pauli_product(CircuitErrorLocation self);
//         stim.CircuitErrorLocation.instruction_targets
  CircuitTargetsInsideInstruction circuit_error_location__instruction_targets(CircuitErrorLocation self);
//         stim.CircuitErrorLocation.stack_frames
  std::vector<CircuitErrorLocationStackFrame> circuit_error_location__stack_frames(CircuitErrorLocation self);
//         stim.CircuitErrorLocation.tick_offset
  uint32_t circuit_error_location__tick_offset(CircuitErrorLocation self);
//     stim.CircuitErrorLocationStackFrame
//         stim.CircuitErrorLocationStackFrame.__init__
  CircuitErrorLocationStackFrame circuit_error_location_stack_frame__init(int instruction_offset,
                                                                          int iteration_index,
                                                                          int instruction_repetitions_arg);
//         stim.CircuitErrorLocationStackFrame.instruction_offset
  int circuit_error_location_stack_frame__offset(CircuitErrorLocationStackFrame frame);
  //         stim.CircuitErrorLocationStackFrame.instruction_repetitions_arg
  int circuit_error_location_stack_frame__repetitions_arg(CircuitErrorLocationStackFrame frame);
//         stim.CircuitErrorLocationStackFrame.iteration_index
  int circuit_error_location_stack_frame__iteration_index(CircuitErrorLocationStackFrame frame);
//     stim.CircuitInstruction
//         stim.CircuitInstruction.__eq__
  bool circuit_instruction__eq(CircuitInstruction self, CircuitInstruction other);
  //         stim.CircuitInstruction.__init__
  CircuitRepeatBlock circuit_instruction__init_ints(std::string name, std::vector<int> targets,
                                                    std::vector<float> gate_args);
  CircuitRepeatBlock circuit_instruction__init_gate_targets(std::string name, std::vector<GateTarget> targets,
                                                            std::vector<float> gate_args);
  //         stim.CircuitInstruction.__ne__
  bool circuit_instruction__ne(CircuitInstruction self, CircuitInstruction other);
  //         stim.CircuitInstruction.__repr_
  std::string circuit_instruction__repr(CircuitInstruction self);
  //         stim.CircuitInstruction.__str__
  std::string circuit_instruction__str(CircuitInstruction self);
  //         stim.CircuitInstruction.gate_args_copy
  std::vector<float> circuit_instruction__gate_args_copy(CircuitInstruction self);
  //         stim.CircuitInstruction.name
  std::string circuit_instruction__name(CircuitInstruction self);
  //         stim.CircuitInstruction.targets_copy
  std::vector<GateTarget> circuit_instruction__targets_copy(CircuitInstruction self);
//     stim.CircuitRepeatBlock
//         stim.CircuitRepeatBlock.__eq__
  bool circuit_repeat_block__eq(CircuitRepeatBlock self, CircuitRepeatBlock other);
  //         stim.CircuitRepeatBlock.__init__
  CircuitRepeatBlock circuit_repeat_block__init(int repeat_count, Circuit body);
  //         stim.CircuitRepeatBlock.__ne__
  bool circuit_repeat_block__ne(CircuitRepeatBlock self, CircuitRepeatBlock other);
  //         stim.CircuitRepeatBlock.__repr__
  std::string circuit_repeat_block__repr(CircuitRepeatBlock self);
  //         stim.CircuitRepeatBlock.body_copy
  Circuit circuit_repeat_block__body_copy(CircuitRepeatBlock self);
  //         stim.CircuitRepeatBlock.name
  bool circuit_repeat_block__name(CircuitRepeatBlock);
//         stim.CircuitRepeatBlock.repeat_count
  uint32_t circuit_repeat_block__repeat_count(CircuitRepeatBlock block);
//     stim.CircuitTargetsInsideInstruction
//         stim.CircuitTargetsInsideInstruction.__init__
  CircuitTargetsInsideInstruction circuit_targets_inside_instruction__init(std::string gate, std::vector<float> args, int target_range_start, int target_range_end, std::vector<GateTargetWithCoords> targets_in_range);
//         stim.CircuitTargetsInsideInstruction.args
  std::vector<float>  circuit_targets_inside_instruction__args(CircuitTargetsInsideInstruction self);
//         stim.CircuitTargetsInsideInstruction.gate
  bool circuit_targets_inside_instruction__gate_p(CircuitTargetsInsideInstruction self);
  std::string circuit_targets_inside_instruction__gate(CircuitTargetsInsideInstruction self);
//         stim.CircuitTargetsInsideInstruction.target_range_end
  int circuit_targets_inside_instruction__target_range_end(CircuitTargetsInsideInstruction self);
  //         stim.CircuitTargetsInsideInstruction.target_range_start
int circuit_targets_inside_instruction__target_range_start(CircuitTargetsInsideInstruction self);
//         stim.CircuitTargetsInsideInstruction.targets_in_range
std::vector<GateTargetWithCoords> circuit_targets_inside_instruction__targets_in_range(CircuitTargetsInsideInstruction self);
//     stim.CompiledDemSampler
//         stim.CompiledDemSampler.sample
  core::T_sp compiled_dem_sampler__sample(CompiledDemSampler self, int shots, bool bit_packed, bool return_errors);
  core::T_sp compiled_dem_sampler__sample_recorded_errors_to_replay(CompiledDemSampler self, int shots,
                                                              bool bit_packed, bool return_errors,
                                                              core::T_sp recorded_errors_to_replay);
//         stim.CompiledDemSampler.sample_write
  void compiled_dem_sampler__sample_write(CompiledDemSampler self, int shots,
                                          std::string det_out_file, SampleFormat det_out_format,
                                          std::string obs_out_file, SampleFormat obs_out_format,
                                          std::string err_out_file, SampleFormat err_out_format,
                                          std::string replay_err_out_file, SampleFormat replay_err_out_format);
//     stim.CompiledDetectorSampler
//         stim.CompiledDetectorSampler.__init__
  CompiledDetectorSampler compiled_detector_sampler__init(Circuit circuit);
  CompiledDetectorSampler compiled_detector_sampler__init_seed(Circuit circuit, uint32_t seed);
//         stim.CompiledDetectorSampler.__repr__
  std::string compiled_detector_sampler__repr(CompiledDetectorSampler self);
//         stim.CompiledDetectorSampler.sample
  core::T_sp compiled_detector_sampler__sample(CompiledDetectorSampler self, int shots,
                                               bool prepend_observables, bool append_observables,
                                               bool separate_observables,
                                               bool bit_packed);
//         stim.CompiledDetectorSampler.sample_write
  void compiled_detector_sampler__sample_write(CompiledDetectorSampler self, int shots,
                                               std::string filepath, SampleFormat format,
                                               bool prepend_observables, bool append_observables,
                                               std::string obs_out_filepath, SampleFormat obs_out_format);
//     stim.CompiledMeasurementSampler
//         stim.CompiledMeasurementSampler.__init__
void compiled_measurement_sampler__init();
  //         stim.CompiledMeasurementSampler.__repr__
 void compiled_measurement_sampler__repr();
  //         stim.CompiledMeasurementSampler.sample
 void compiled_measurement_sampler__sample();
  //         stim.CompiledMeasurementSampler.sample_write
 void compiled_measurement_sampler__sample_write();
void CompiledMeasurementsToDetectionEventsConverter__init();
void CompiledMeasurementsToDetectionEventsConverter__repr();
void CompiledMeasurementsToDetectionEventsConverter__convert();
void CompiledMeasurementsToDetectionEventsConverter__convert_file();
void DemInstruction__eq();
void DemInstruction__init();
void DemInstruction__ne();
void DemInstruction__repr();
void DemInstruction__str();
void DemInstruction__args_copy();
void DemInstruction__targets_copy();
void DemInstruction__type();
void DemRepeatBlock__eq();
void DemRepeatBlock__init();
void DemRepeatBlock__ne();
void DemRepeatBlock__repr();
void DemRepeatBlock__body_copy();
void DemRepeatBlock__repeat_count();
void DemRepeatBlock__type();
void DemTarget__eq();
void DemTarget__ne();
void DemTarget__repr();
void DemTarget__str();
void DemTarget__is_logical_observable_id();
void DemTarget__is_relative_detector_id();
void DemTarget__is_separator();
void DemTarget__logical_observable_id();
void DemTarget__relative_detector_id();
void DemTarget__separator();
void DemTarget__val();
void DemTargetWithCoords__init();
void DemTargetWithCoords__coords();
void DemTargetWithCoords__dem_target();
void DetectorErrorModel__add();
void DetectorErrorModel__eq();
void DetectorErrorModel__getitem();
void DetectorErrorModel__iadd();
void DetectorErrorModel__imul();
void DetectorErrorModel__init();
void DetectorErrorModel__len();
void DetectorErrorModel__mul();
void DetectorErrorModel__ne();
void DetectorErrorModel__repr();
void DetectorErrorModel__rmul();
void DetectorErrorModel__str();
void DetectorErrorModel__append();
void DetectorErrorModel__approx_equals();
void DetectorErrorModel__clear();
void DetectorErrorModel__compile_sampler();
void DetectorErrorModel__copy();
void DetectorErrorModel__diagram();
void DetectorErrorModel__flattened();
void DetectorErrorModel__from_file();
void DetectorErrorModel__get_detector_coordinates();
void DetectorErrorModel__num_detectors();
void DetectorErrorModel__num_errors();
void DetectorErrorModel__num_observables();
void DetectorErrorModel__rounded();
void DetectorErrorModel__shortest_graphlike_error();
void DetectorErrorModel__to_file();
void ExplainedError();
void ExplainedError__init();
void ExplainedError__circuit_error_locations();
void ExplainedError__dem_error_terms();
void FlipSimulator();
void FlipSimulator__init();
void FlipSimulator__batch_size();
void FlipSimulator__broadcast_pauli_errors();
void FlipSimulator__do();
void FlipSimulator__get_detector_flips();
void FlipSimulator__get_measurement_flips();
void FlipSimulator__get_observable_flips();
void FlipSimulator__num_detectors();
void FlipSimulator__num_measurements();
void FlipSimulator__num_observables();
void FlipSimulator__num_qubits();
void FlipSimulator__peek_pauli_flips();
void FlipSimulator__set_pauli_flip();
void FlippedMeasurement__init();
void FlippedMeasurement__observable();
void FlippedMeasurement__record_index();
void Flow__eq();
void Flow__init();
void Flow__ne();
void Flow__repr();
void Flow__str();
void Flow__input_copy();
void Flow__measurements_copy();
void Flow__output_copy();
void GateData__eq();
void GateData__init();
void GateData__ne();
void GateData__repr();
void GateData__str();
void GateData__aliases();
void GateData__flows();
void GateData__generalized_inverse();
void GateData__inverse();
void GateData__is_noisy_gate();
void GateData__is_reset();
void GateData__is_single_qubit_gate();
void GateData__is_two_qubit_gate();
void GateData__is_unitary();
void GateData__name();
void GateData__num_parens_arguments_range();
void GateData__produces_measurements();
void GateData__tableau();
void GateData__takes_measurement_record_targets();
void GateData__takes_pauli_targets();
void GateData__unitary_matrix();
void GateTarget__eq();
void GateTarget__init();
void GateTarget__ne();
void GateTarget__repr();
void GateTarget__is_combiner();
void GateTarget__is_inverted_result_target();
void GateTarget__is_measurement_record_target();
void GateTarget__is_qubit_target();
void GateTarget__is_sweep_bit_target();
void GateTarget__is_x_target();
void GateTarget__is_y_target();
void GateTarget__is_z_target();
void GateTarget__pauli_type();
void GateTarget__qubit_value();
void GateTarget__value();
void GateTargetWithCoords__init();
void GateTargetWithCoords__coords();
void GateTargetWithCoords__gate_target();
void PauliString__add();
void PauliString__eq();
void PauliString__getitem();
void PauliString__iadd();
void PauliString__imul();
void PauliString__init();
void PauliString__itruediv();
void PauliString__len();
void PauliString__mul();
void PauliString__ne();
void PauliString__neg();
void PauliString__pos();
void PauliString__repr();
void PauliString__rmul();
void PauliString__setitem();
void PauliString__str();
void PauliString__truediv();
void PauliString__after();
void PauliString__before();
void PauliString__commutes();
void PauliString__copy();
void PauliString__from_numpy();
void PauliString__from_unitary_matrix();
void PauliString__iter_all();
void PauliString__pauli_indices();
void PauliString__random();
void PauliString__sign();
void PauliString__to_numpy();
void PauliString__to_tableau();
void PauliString__to_unitary_matrix();
void PauliString__weight();
void PauliStringIterator__iter();
void PauliStringIterator__next();
void Tableau__add();
void Tableau__call();
void Tableau__eq();
void Tableau__iadd();
void Tableau__init();
void Tableau__len();
void Tableau__mul();
void Tableau__ne();
void Tableau__pow();
void Tableau__repr();
void Tableau__str();
void Tableau__append();
void Tableau__copy();
void Tableau__from_circuit();
void Tableau__from_conjugated_generators();
void Tableau__from_named_gate();
void Tableau__from_numpy();
void Tableau__from_stabilizers();
void Tableau__from_state_vector();
void Tableau__from_unitary_matrix();
void Tableau__inverse();
void Tableau__inverse_x_output();
void Tableau__inverse_x_output_pauli();
void Tableau__inverse_y_output();
void Tableau__inverse_y_output_pauli();
void Tableau__inverse_z_output();
void Tableau__inverse_z_output_pauli();
void Tableau__iter_all();
void Tableau__prepend();
void Tableau__random();
void Tableau__then();
void Tableau__to_circuit();
void Tableau__to_numpy();
void Tableau__to_pauli_string();
void Tableau__to_stabilizers();
void Tableau__to_state_vector();
void Tableau__to_unitary_matrix();
void Tableau__x_output();
void Tableau__x_output_pauli();
void Tableau__x_sign();
void Tableau__y_output();
void Tableau__y_output_pauli();
void Tableau__y_sign();
void Tableau__z_output();
void Tableau__z_output_pauli();
void Tableau__z_sign();
void TableauIterator__iter();
void TableauIterator__next();
void TableauSimulator__init();
void TableauSimulator__c_xyz();
void TableauSimulator__c_zyx();
void TableauSimulator__canonical_stabilizers();
void TableauSimulator__cnot();
void TableauSimulator__copy();
void TableauSimulator__current_inverse_tableau();
void TableauSimulator__current_measurement_record();
void TableauSimulator__cx();
void TableauSimulator__cy();
void TableauSimulator__cz();
void TableauSimulator__depolarize1();
void TableauSimulator__depolarize2();
void TableauSimulator__do();
void TableauSimulator__do_circuit();
void TableauSimulator__do_pauli_string();
void TableauSimulator__do_tableau();
void TableauSimulator__h();
void TableauSimulator__h_xy();
void TableauSimulator__h_xz();
void TableauSimulator__h_yz();
void TableauSimulator__iswap();
void TableauSimulator__iswap_dag();
void TableauSimulator__measure();
void TableauSimulator__measure_kickback();
void TableauSimulator__measure_many();
void TableauSimulator__measure_observable();
void TableauSimulator__num_qubits();
void TableauSimulator__peek_bloch();
void TableauSimulator__peek_observable_expectation();
void TableauSimulator__peek_x();
void TableauSimulator__peek_y();
void TableauSimulator__peek_z();
void TableauSimulator__postselect_observable();
void TableauSimulator__postselect_x();
void TableauSimulator__postselect_y();
void TableauSimulator__postselect_z();
void TableauSimulator__reset();
void TableauSimulator__reset_x();
void TableauSimulator__reset_y();
void TableauSimulator__reset_z();
void TableauSimulator__s();
void TableauSimulator__s_dag();
void TableauSimulator__set_inverse_tableau();
void TableauSimulator__set_num_qubits();
void TableauSimulator__set_state_from_stabilizers();
void TableauSimulator__set_state_from_state_vector();
void TableauSimulator__sqrt_x();
void TableauSimulator__sqrt_x_dag();
void TableauSimulator__sqrt_y();
void TableauSimulator__sqrt_y_dag();
void TableauSimulator__state_vector();
void TableauSimulator__swap();
void TableauSimulator__x();
void TableauSimulator__x_error();
void TableauSimulator__xcx();
void TableauSimulator__xcy();
void TableauSimulator__xcz();
void TableauSimulator__y();
void TableauSimulator__y_error();
void TableauSimulator__ycx();
void TableauSimulator__ycy();
void TableauSimulator__ycz();
void TableauSimulator__z();
void TableauSimulator__z_error();
void TableauSimulator__zcx();
void TableauSimulator__zcy();
void TableauSimulator__zcz();
void gate_data();
void main();
// read_shot_data_file - doesn't make sense to expose
void target_combined_paulis();
void target_combiner();
void target_inv();
void target_logical_observable_id();
void target_pauli();
void target_rec();
void target_relative_detector_id();
void target_separator();
void target_sweep_bit();
void target_x();
void target_y();
void target_z();
// write_shot_data_file - doesn't make sense to expose
}

// enum exposing:

// {{"NOT-A-GATE", GateType::NOT_A_GATE},
//     {"DETECTOR",GateType::DETECTOR},
//       {"OBSERVABLE-INCLUDE",GateType::OBSERVABLE_INCLUDE}}
#define UNWRAP(...) __VA_ARGS__

#define CLBIND_EXPOSE_MACRO(_ENUM_TYPE_, _KV_ )                         \
  namespace translate                                                   \
  {                                                                     \
   template <>                                                          \
    struct to_object<_ENUM_TYPE_>                                       \
    {                                                                   \
      static core::T_sp convert(_ENUM_TYPE_ arg)                        \
      {  std::map<std::string, _ENUM_TYPE_> kv UNWRAP _KV_;             \
        auto vk=clasp_stim::reverse_map(kv);                            \
        return core::lisp_intern(vk[arg],"KEYWORD");                    \
      }                                                                 \
    };                                                                  \
    template <>                                                         \
    struct from_object<_ENUM_TYPE_>                                     \
    {                                                                   \
      typedef _ENUM_TYPE_ DeclareType;                                  \
      DeclareType _v;                                                   \
      from_object(core::T_sp obj)                                       \
      {                                                                 \
        if(cl__keywordp(obj)){                                          \
          core::Symbol_sp s = obj.asOrNull<core::Symbol_O>();           \
          std::string name = s->_Name->get_std_string();                \
          std::map<std::string, _ENUM_TYPE_> kv UNWRAP _KV_;            \
          if(kv.count(name))                                            \
            this->_v= kv[name];                                         \
          else SIMPLE_ERROR("key not found");                           \
        }                                                               \
        else TYPE_ERROR(obj,cl::_sym_Symbol_O);                         \
      }                                                                 \
    };                                                                  \
  };                                                                    \
