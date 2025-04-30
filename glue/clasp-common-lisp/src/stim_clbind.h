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

//         stim.Circuit.generated
//         stim.Circuit.get_detector_coordinates
//         stim.Circuit.get_final_qubit_coordinates
//         stim.Circuit.has_all_flows
//         stim.Circuit.has_flow
//         stim.Circuit.inverse
//         stim.Circuit.likeliest_error_sat_problem
//         stim.Circuit.num_detectors
//         stim.Circuit.num_measurements
//         stim.Circuit.num_observables
//         stim.Circuit.num_qubits
//         stim.Circuit.num_sweep_bits
//         stim.Circuit.num_ticks
//         stim.Circuit.reference_sample
//         stim.Circuit.search_for_undetectable_logical_errors
//         stim.Circuit.shortest_error_sat_problem
//         stim.Circuit.shortest_graphlike_error
//         stim.Circuit.to_file
//         stim.Circuit.to_qasm
//         stim.Circuit.to_tableau
//         stim.Circuit.with_inlined_feedback
//         stim.Circuit.without_noise
//     stim.CircuitErrorLocation
//         stim.CircuitErrorLocation.__init__
//         stim.CircuitErrorLocation.flipped_measurement
//         stim.CircuitErrorLocation.flipped_pauli_product
//         stim.CircuitErrorLocation.instruction_targets
//         stim.CircuitErrorLocation.stack_frames
//         stim.CircuitErrorLocation.tick_offset
//     stim.CircuitErrorLocationStackFrame
//         stim.CircuitErrorLocationStackFrame.__init__
//         stim.CircuitErrorLocationStackFrame.instruction_offset
//         stim.CircuitErrorLocationStackFrame.instruction_repetitions_arg
//         stim.CircuitErrorLocationStackFrame.iteration_index
//     stim.CircuitInstruction
//         stim.CircuitInstruction.__eq__
//         stim.CircuitInstruction.__init__
//         stim.CircuitInstruction.__ne__
//         stim.CircuitInstruction.__repr__
//         stim.CircuitInstruction.__str__
//         stim.CircuitInstruction.gate_args_copy
//         stim.CircuitInstruction.name
//         stim.CircuitInstruction.targets_copy
//     stim.CircuitRepeatBlock
//         stim.CircuitRepeatBlock.__eq__
//         stim.CircuitRepeatBlock.__init__
//         stim.CircuitRepeatBlock.__ne__
//         stim.CircuitRepeatBlock.__repr__
//         stim.CircuitRepeatBlock.body_copy
//         stim.CircuitRepeatBlock.name
//         stim.CircuitRepeatBlock.repeat_count
//     stim.CircuitTargetsInsideInstruction
//         stim.CircuitTargetsInsideInstruction.__init__
//         stim.CircuitTargetsInsideInstruction.args
//         stim.CircuitTargetsInsideInstruction.gate
//         stim.CircuitTargetsInsideInstruction.target_range_end
//         stim.CircuitTargetsInsideInstruction.target_range_start
//         stim.CircuitTargetsInsideInstruction.targets_in_range
//     stim.CompiledDemSampler
//         stim.CompiledDemSampler.sample
//         stim.CompiledDemSampler.sample_write
//     stim.CompiledDetectorSampler
//         stim.CompiledDetectorSampler.__init__
//         stim.CompiledDetectorSampler.__repr__
//         stim.CompiledDetectorSampler.sample
//         stim.CompiledDetectorSampler.sample_write
//     stim.CompiledMeasurementSampler
//         stim.CompiledMeasurementSampler.__init__
//         stim.CompiledMeasurementSampler.__repr__
//         stim.CompiledMeasurementSampler.sample
//         stim.CompiledMeasurementSampler.sample_write
//     stim.CompiledMeasurementsToDetectionEventsConverter
//         stim.CompiledMeasurementsToDetectionEventsConverter.__init__
//         stim.CompiledMeasurementsToDetectionEventsConverter.__repr__
//         stim.CompiledMeasurementsToDetectionEventsConverter.convert
//         stim.CompiledMeasurementsToDetectionEventsConverter.convert_file
//     stim.DemInstruction
//         stim.DemInstruction.__eq__
//         stim.DemInstruction.__init__
//         stim.DemInstruction.__ne__
//         stim.DemInstruction.__repr__
//         stim.DemInstruction.__str__
//         stim.DemInstruction.args_copy
//         stim.DemInstruction.targets_copy
//         stim.DemInstruction.type
//     stim.DemRepeatBlock
//         stim.DemRepeatBlock.__eq__
//         stim.DemRepeatBlock.__init__
//         stim.DemRepeatBlock.__ne__
//         stim.DemRepeatBlock.__repr__
//         stim.DemRepeatBlock.body_copy
//         stim.DemRepeatBlock.repeat_count
//         stim.DemRepeatBlock.type
//     stim.DemTarget
//         stim.DemTarget.__eq__
//         stim.DemTarget.__ne__
//         stim.DemTarget.__repr__
//         stim.DemTarget.__str__
//         stim.DemTarget.is_logical_observable_id
//         stim.DemTarget.is_relative_detector_id
//         stim.DemTarget.is_separator
//         stim.DemTarget.logical_observable_id
//         stim.DemTarget.relative_detector_id
//         stim.DemTarget.separator
//         stim.DemTarget.val
//     stim.DemTargetWithCoords
//         stim.DemTargetWithCoords.__init__
//         stim.DemTargetWithCoords.coords
//         stim.DemTargetWithCoords.dem_target
//     stim.DetectorErrorModel
//         stim.DetectorErrorModel.__add__
//         stim.DetectorErrorModel.__eq__
//         stim.DetectorErrorModel.__getitem__
//         stim.DetectorErrorModel.__iadd__
//         stim.DetectorErrorModel.__imul__
//         stim.DetectorErrorModel.__init__
//         stim.DetectorErrorModel.__len__
//         stim.DetectorErrorModel.__mul__
//         stim.DetectorErrorModel.__ne__
//         stim.DetectorErrorModel.__repr__
//         stim.DetectorErrorModel.__rmul__
//         stim.DetectorErrorModel.__str__
//         stim.DetectorErrorModel.append
//         stim.DetectorErrorModel.approx_equals
//         stim.DetectorErrorModel.clear
//         stim.DetectorErrorModel.compile_sampler
//         stim.DetectorErrorModel.copy
//         stim.DetectorErrorModel.diagram
//         stim.DetectorErrorModel.flattened
//         stim.DetectorErrorModel.from_file
//         stim.DetectorErrorModel.get_detector_coordinates
//         stim.DetectorErrorModel.num_detectors
//         stim.DetectorErrorModel.num_errors
//         stim.DetectorErrorModel.num_observables
//         stim.DetectorErrorModel.rounded
//         stim.DetectorErrorModel.shortest_graphlike_error
//         stim.DetectorErrorModel.to_file
//     stim.ExplainedError
//         stim.ExplainedError.__init__
//         stim.ExplainedError.circuit_error_locations
//         stim.ExplainedError.dem_error_terms
//     stim.FlipSimulator
//         stim.FlipSimulator.__init__
//         stim.FlipSimulator.batch_size
//         stim.FlipSimulator.broadcast_pauli_errors
//         stim.FlipSimulator.do
//         stim.FlipSimulator.get_detector_flips
//         stim.FlipSimulator.get_measurement_flips
//         stim.FlipSimulator.get_observable_flips
//         stim.FlipSimulator.num_detectors
//         stim.FlipSimulator.num_measurements
//         stim.FlipSimulator.num_observables
//         stim.FlipSimulator.num_qubits
//         stim.FlipSimulator.peek_pauli_flips
//         stim.FlipSimulator.set_pauli_flip
//     stim.FlippedMeasurement
//         stim.FlippedMeasurement.__init__
//         stim.FlippedMeasurement.observable
//         stim.FlippedMeasurement.record_index
//     stim.Flow
//         stim.Flow.__eq__
//         stim.Flow.__init__
//         stim.Flow.__ne__
//         stim.Flow.__repr__
//         stim.Flow.__str__
//         stim.Flow.input_copy
//         stim.Flow.measurements_copy
//         stim.Flow.output_copy
//     stim.GateData
//         stim.GateData.__eq__
//         stim.GateData.__init__
//         stim.GateData.__ne__
//         stim.GateData.__repr__
//         stim.GateData.__str__
//         stim.GateData.aliases
//         stim.GateData.flows
//         stim.GateData.generalized_inverse
//         stim.GateData.inverse
//         stim.GateData.is_noisy_gate
//         stim.GateData.is_reset
//         stim.GateData.is_single_qubit_gate
//         stim.GateData.is_two_qubit_gate
//         stim.GateData.is_unitary
//         stim.GateData.name
//         stim.GateData.num_parens_arguments_range
//         stim.GateData.produces_measurements
//         stim.GateData.tableau
//         stim.GateData.takes_measurement_record_targets
//         stim.GateData.takes_pauli_targets
//         stim.GateData.unitary_matrix
//     stim.GateTarget
//         stim.GateTarget.__eq__
//         stim.GateTarget.__init__
//         stim.GateTarget.__ne__
//         stim.GateTarget.__repr__
//         stim.GateTarget.is_combiner
//         stim.GateTarget.is_inverted_result_target
//         stim.GateTarget.is_measurement_record_target
//         stim.GateTarget.is_qubit_target
//         stim.GateTarget.is_sweep_bit_target
//         stim.GateTarget.is_x_target
//         stim.GateTarget.is_y_target
//         stim.GateTarget.is_z_target
//         stim.GateTarget.pauli_type
//         stim.GateTarget.qubit_value
//         stim.GateTarget.value
//     stim.GateTargetWithCoords
//         stim.GateTargetWithCoords.__init__
//         stim.GateTargetWithCoords.coords
//         stim.GateTargetWithCoords.gate_target
//     stim.PauliString
//         stim.PauliString.__add__
//         stim.PauliString.__eq__
//         stim.PauliString.__getitem__
//         stim.PauliString.__iadd__
//         stim.PauliString.__imul__
//         stim.PauliString.__init__
//         stim.PauliString.__itruediv__
//         stim.PauliString.__len__
//         stim.PauliString.__mul__
//         stim.PauliString.__ne__
//         stim.PauliString.__neg__
//         stim.PauliString.__pos__
//         stim.PauliString.__repr__
//         stim.PauliString.__rmul__
//         stim.PauliString.__setitem__
//         stim.PauliString.__str__
//         stim.PauliString.__truediv__
//         stim.PauliString.after
//         stim.PauliString.before
//         stim.PauliString.commutes
//         stim.PauliString.copy
//         stim.PauliString.from_numpy
//         stim.PauliString.from_unitary_matrix
//         stim.PauliString.iter_all
//         stim.PauliString.pauli_indices
//         stim.PauliString.random
//         stim.PauliString.sign
//         stim.PauliString.to_numpy
//         stim.PauliString.to_tableau
//         stim.PauliString.to_unitary_matrix
//         stim.PauliString.weight
//     stim.PauliStringIterator
//         stim.PauliStringIterator.__iter__
//         stim.PauliStringIterator.__next__
//     stim.Tableau
//         stim.Tableau.__add__
//         stim.Tableau.__call__
//         stim.Tableau.__eq__
//         stim.Tableau.__iadd__
//         stim.Tableau.__init__
//         stim.Tableau.__len__
//         stim.Tableau.__mul__
//         stim.Tableau.__ne__
//         stim.Tableau.__pow__
//         stim.Tableau.__repr__
//         stim.Tableau.__str__
//         stim.Tableau.append
//         stim.Tableau.copy
//         stim.Tableau.from_circuit
//         stim.Tableau.from_conjugated_generators
//         stim.Tableau.from_named_gate
//         stim.Tableau.from_numpy
//         stim.Tableau.from_stabilizers
//         stim.Tableau.from_state_vector
//         stim.Tableau.from_unitary_matrix
//         stim.Tableau.inverse
//         stim.Tableau.inverse_x_output
//         stim.Tableau.inverse_x_output_pauli
//         stim.Tableau.inverse_y_output
//         stim.Tableau.inverse_y_output_pauli
//         stim.Tableau.inverse_z_output
//         stim.Tableau.inverse_z_output_pauli
//         stim.Tableau.iter_all
//         stim.Tableau.prepend
//         stim.Tableau.random
//         stim.Tableau.then
//         stim.Tableau.to_circuit
//         stim.Tableau.to_numpy
//         stim.Tableau.to_pauli_string
//         stim.Tableau.to_stabilizers
//         stim.Tableau.to_state_vector
//         stim.Tableau.to_unitary_matrix
//         stim.Tableau.x_output
//         stim.Tableau.x_output_pauli
//         stim.Tableau.x_sign
//         stim.Tableau.y_output
//         stim.Tableau.y_output_pauli
//         stim.Tableau.y_sign
//         stim.Tableau.z_output
//         stim.Tableau.z_output_pauli
//         stim.Tableau.z_sign
//     stim.TableauIterator
//         stim.TableauIterator.__iter__
//         stim.TableauIterator.__next__
//     stim.TableauSimulator
//         stim.TableauSimulator.__init__
//         stim.TableauSimulator.c_xyz
//         stim.TableauSimulator.c_zyx
//         stim.TableauSimulator.canonical_stabilizers
//         stim.TableauSimulator.cnot
//         stim.TableauSimulator.copy
//         stim.TableauSimulator.current_inverse_tableau
//         stim.TableauSimulator.current_measurement_record
//         stim.TableauSimulator.cx
//         stim.TableauSimulator.cy
//         stim.TableauSimulator.cz
//         stim.TableauSimulator.depolarize1
//         stim.TableauSimulator.depolarize2
//         stim.TableauSimulator.do
//         stim.TableauSimulator.do_circuit
//         stim.TableauSimulator.do_pauli_string
//         stim.TableauSimulator.do_tableau
//         stim.TableauSimulator.h
//         stim.TableauSimulator.h_xy
//         stim.TableauSimulator.h_xz
//         stim.TableauSimulator.h_yz
//         stim.TableauSimulator.iswap
//         stim.TableauSimulator.iswap_dag
//         stim.TableauSimulator.measure
//         stim.TableauSimulator.measure_kickback
//         stim.TableauSimulator.measure_many
//         stim.TableauSimulator.measure_observable
//         stim.TableauSimulator.num_qubits
//         stim.TableauSimulator.peek_bloch
//         stim.TableauSimulator.peek_observable_expectation
//         stim.TableauSimulator.peek_x
//         stim.TableauSimulator.peek_y
//         stim.TableauSimulator.peek_z
//         stim.TableauSimulator.postselect_observable
//         stim.TableauSimulator.postselect_x
//         stim.TableauSimulator.postselect_y
//         stim.TableauSimulator.postselect_z
//         stim.TableauSimulator.reset
//         stim.TableauSimulator.reset_x
//         stim.TableauSimulator.reset_y
//         stim.TableauSimulator.reset_z
//         stim.TableauSimulator.s
//         stim.TableauSimulator.s_dag
//         stim.TableauSimulator.set_inverse_tableau
//         stim.TableauSimulator.set_num_qubits
//         stim.TableauSimulator.set_state_from_stabilizers
//         stim.TableauSimulator.set_state_from_state_vector
//         stim.TableauSimulator.sqrt_x
//         stim.TableauSimulator.sqrt_x_dag
//         stim.TableauSimulator.sqrt_y
//         stim.TableauSimulator.sqrt_y_dag
//         stim.TableauSimulator.state_vector
//         stim.TableauSimulator.swap
//         stim.TableauSimulator.x
//         stim.TableauSimulator.x_error
//         stim.TableauSimulator.xcx
//         stim.TableauSimulator.xcy
//         stim.TableauSimulator.xcz
//         stim.TableauSimulator.y
//         stim.TableauSimulator.y_error
//         stim.TableauSimulator.ycx
//         stim.TableauSimulator.ycy
//         stim.TableauSimulator.ycz
//         stim.TableauSimulator.z
//         stim.TableauSimulator.z_error
//         stim.TableauSimulator.zcx
//         stim.TableauSimulator.zcy
//         stim.TableauSimulator.zcz
//     stim.gate_data
//     stim.main
//     stim.read_shot_data_file
//     stim.target_combined_paulis
//     stim.target_combiner
//     stim.target_inv
//     stim.target_logical_observable_id
//     stim.target_pauli
//     stim.target_rec
//     stim.target_relative_detector_id
//     stim.target_separator
//     stim.target_sweep_bit
//     stim.target_x
//     stim.target_y
//     stim.target_z
//     stim.write_shot_data_file
}

// enum exposing:

// {{"NOT-A-GATE", GateType::NOT_A_GATE},
//     {"DETECTOR",GateType::DETECTOR},
//       {"OBSERVABLE-INCLUDE",GateType::OBSERVABLE_INCLUDE}}
#define UNWRAP(...) __VA_ARGS__

#define CLBIND_EXPOSE_MACRO(_ENUM_TYPE_, _KV_ ) \
namespace translate \
{ \
  template <> \
    struct to_object<_ENUM_TYPE_> \
  { \
    static core::T_sp convert(_ENUM_TYPE_ arg)                          \
    {  std::map<std::string, _ENUM_TYPE_> kv UNWRAP _KV_;        \
      std::map<_ENUM_TYPE_,std::string> vk=clasp_stim::reverse_map(kv); \
      return core::lisp_intern(vk[arg],"KEYWORD"); \
    } \
  }; \
  template <> \
  struct from_object<_ENUM_TYPE_>               \
  { \
    typedef _ENUM_TYPE_ DeclareType;            \
    DeclareType _v; \
    from_object(core::T_sp obj) \
    { \
      if(cl__keywordp(obj)){ \
        core::Symbol_sp s = obj.asOrNull<core::Symbol_O>(); \
        std::string name = s->_Name->get_std_string(); \
        std::map<std::string, _ENUM_TYPE_> kv UNWRAP _KV_; \
        if(kv.count(name)) \
        this->_v= kv[name]; \
        else SIMPLE_ERROR("key not found");     \
      } \
      else TYPE_ERROR(obj,cl::_sym_Symbol_O); \
    } \
  }; \
}; \
