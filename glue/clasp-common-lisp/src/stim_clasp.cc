#include <fmt/format.h>
#include <clasp/clasp.h>
#include "stim.h"

using namespace stim;

namespace clasp_stim {
  void stim__gate_data() {}
  void stim__target_separator() {}
  void stim__target_relative_detector_id() {}
  void stim__target_logical_observable_id() {}

  int stim__main(const std::vector<std::string> args){ // adapted from stim.pybind.cc
    std::vector<const char *> argv;
    argv.push_back("stim.main");
    for (const auto &arg : args) {
      argv.push_back(arg.c_str());
    }
    return main(argv.size(), argv.data());
  }

  GateTarget stim__target_rec(int32_t lookback){
    return GateTarget::rec(lookback);
  }
  GateTarget stim__target_inv_target(const GateTarget &qubit){
    return !qubit;
  }
  GateTarget stim__target_inv_uint32_t(const uint32_t &qubit){
    return GateTarget::qubit(qubit, true);
  }

  GateTarget stim__target_x_target(const GateTarget &t, bool invert){
    if (!t.is_qubit_target()) {
      throw std::invalid_argument("result of stim.target_x(" + t.str() + ") is not defined");
    }
    return GateTarget::x(t.qubit_value(), t.is_inverted_result_target() ^ invert);
  }
  GateTarget stim__target_x_uint32_t(const uint32_t &qubit, bool invert){
    return GateTarget::x(qubit, invert);
  }

  GateTarget stim__target_y_target(const GateTarget &t, bool invert){
    if (!t.is_qubit_target()) {
      throw std::invalid_argument("result of stim.target_x(" + t.str() + ") is not defined");
    }
    return GateTarget::y(t.qubit_value(), t.is_inverted_result_target() ^ invert);
  }
  GateTarget stim__target_y_uint32_t(const uint32_t &qubit, bool invert){
    return GateTarget::y(qubit, invert);
  }

  GateTarget stim__target_z_target(const GateTarget &t, bool invert){
    if (!t.is_qubit_target()) {
      throw std::invalid_argument("result of stim.target_x(" + t.str() + ") is not defined");
    }
    return GateTarget::z(t.qubit_value(), t.is_inverted_result_target() ^ invert);
  }
  GateTarget stim__target_z_uint32_t(const uint32_t &qubit, bool invert){
    return GateTarget::z(qubit, invert);
  }
  std::vector<GateTarget> stim__target_combined_paulis_gate_targets(std::vector<GateTarget> &paulis, bool invert){
    std::vector<GateTarget> result;
    for (GateTarget &g : paulis) {
        if (g.pauli_type() != 'I') {
          if (g.is_inverted_result_target()) {
            invert ^= true;
            g.data ^= TARGET_INVERTED_BIT;
          }
          result.push_back(g);
          result.push_back(GateTarget::combiner());
          continue;
        }

      std::stringstream ss;
      ss << "Expected a pauli string or iterable of stim.GateTarget but got this when iterating: ";
      ss << g;
      throw std::invalid_argument(ss.str());
    }

    if (result.empty()) {
      std::stringstream ss;
      ss << "Identity pauli product: paulis=";
      for(GateTarget &g: paulis)
        ss << g.str();
      throw std::invalid_argument(ss.str());
    }
    result.pop_back();
    if (invert) {
      result[0].data ^= TARGET_INVERTED_BIT;
    }
    return result;
  }

  std::vector<GateTarget> stim__target_combined_paulis_string(const FlexPauliString &ps, bool invert){
    std::vector<GateTarget> result;
    if (ps.imag) {
      std::stringstream ss;
      ss << "Imaginary sign: paulis=";
      ss << ps.str();
      throw std::invalid_argument(ss.str());
    }
    invert ^= ps.value.sign;
    for (size_t q = 0; q < ps.value.num_qubits; q++) {
      bool x = ps.value.xs[q];
      bool z = ps.value.zs[q];
      if (x | z) {
        result.push_back(GateTarget::pauli_xz(q, x, z));
        result.push_back(GateTarget::combiner());
      }
    }

    if (result.empty()) {
      std::stringstream ss;
      ss << "Identity pauli product: paulis=";
      ss << ps;
      throw std::invalid_argument(ss.str());
    }
    result.pop_back();
    if (invert) {
      result[0].data ^= TARGET_INVERTED_BIT;
    }
    return result;
  }
  GateTarget stim__target_pauli_string(uint32_t qubit_index, const std::string &p, bool invert){
    if ((qubit_index & TARGET_VALUE_MASK) != qubit_index) {
      std::stringstream ss;
      ss << "qubit_index=" << qubit_index << " is too large. Maximum qubit index is " << TARGET_VALUE_MASK << ".";
      throw std::invalid_argument(ss.str());
    }
    if (p == "X" || p == "x") {
      return GateTarget::x(qubit_index, invert);
    } else if (p == "Y" || p == "y") {
      return GateTarget::y(qubit_index, invert);
    } else if (p == "Z" || p == "z") {
      return GateTarget::z(qubit_index, invert);
    } else if (p == "I") {
      return GateTarget::qubit(qubit_index, invert);
    }

    std::stringstream ss;
    ss << "Expected pauli in [0, 1, 2, 3, *'IXYZxyz'] but got pauli=" << p;
    throw std::invalid_argument(ss.str());
  }
  GateTarget stim__target_pauli_uint8_t(uint32_t qubit_index, const uint8_t &p, bool invert){
    if ((qubit_index & TARGET_VALUE_MASK) != qubit_index) {
      std::stringstream ss;
      ss << "qubit_index=" << qubit_index << " is too large. Maximum qubit index is " << TARGET_VALUE_MASK << ".";
      throw std::invalid_argument(ss.str());
    }
    if (p == 1) {
      return GateTarget::x(qubit_index, invert);
    } else if (p == 2) {
      return GateTarget::y(qubit_index, invert);
    } else if (p == 3) {
      return GateTarget::z(qubit_index, invert);
    } else if (p == 0) {
      return GateTarget::qubit(qubit_index, invert);
    }

    std::stringstream ss;
    ss << "Expected pauli in [0, 1, 2, 3, *'IXYZxyz'] but got pauli=" << p;
    throw std::invalid_argument(ss.str());
  }
  GateTarget stim__target_sweep_bit(uint32_t qubit){
    return GateTarget::sweep_bit(qubit);
  }
  GateTarget stim__gate_target_from_target_str(std::string v){
    return GateTarget::from_target_str(v);
  }
  FlexPauliString flex_pauli_from_text(std::string v){
    return FlexPauliString::from_text(v);
  }
  FlexPauliString pauli_iterator_get_current(const PauliStringIterator<MAX_BITWORD_WIDTH> iterator){
    //& doesn't work?
    FlexPauliString result(iterator.num_qubits);// TODO work out why FlexPauliString constructor doesnt work
    result.value=iterator.result;
    result.imag=false;
    return result;
  }
  Circuit circuit__add(Circuit &self, Circuit &c2){
    return self + c2;
  }
  bool circuit__eq(Circuit &self, Circuit &c2){return self == c2;}
// core::T_sp circuit__getitem_uint32_t(Circuit &self,uint32_t index){}
// Circuit circuit__getitem_slice(Circuit &self, uint32_t start, uint32_t stop, uint32_t step){}
// void circuit__iadd(Circuit &self, Circuit &second){}
// void circuit__imul(Circuit &self, uint32_t repetitions){}
  Circuit circuit__init(std::string program_text)
  {
    Circuit self;
    self.append_from_text(program_text);
    return self;
  }
// uint32_t circuit__len(Circuit &self){}
// Circuit circuit__mul(Circuit &self, uint32_t repetitions){}
  bool circuit__ne(Circuit &self, Circuit &c2){return self != c2;}
  std::string circuit__repr(Circuit &self){
    if (self.operations.empty()) {
      return "stim.Circuit()";
    }
    std::stringstream ss;
    ss << "stim.Circuit('''\n";
    print_circuit(ss, self, 4);
    ss << "\n''')";
    return ss.str();}
  Circuit circuit__rmul(Circuit &self, uint32_t repetitions){return self * repetitions;}
  std::string circuit__str(Circuit &self){return self.str();}
// void circuit__append_int_array(Circuit &self, std::string name, std::vector<int> targets, std::vector<double> arg){}
// void circuit__append_gate_target_array(Circuit &self, std::string name, std::vector<GateTarget> targets, std::vector<double> arg){}
// void circuit__append_circuit_instruction(Circuit &self, clbind_CircuitInstruction operation){}
// void circuit__append_circuit_repeat_block(Circuit &self, clbind_CircuitRepeatBlock repeat_block){}
// void circuit__append_from_stim_program_text(Circuit &self, std::string stim_program_text){}
// bool circuit__approx_equals(Circuit &self, Circuit &other, float atol){}
  void circuit__clear(Circuit &self){self.clear();}
// clbind_CompiledDetectorSampler circuit__compile_detector_sampler(Circuit &self){}
// clbind_CompiledDetectorSampler circuit__compile_detector_sampler_seed(Circuit &self,uint32_t seed){}
// clbind_CompiledMeasurementsToDetectionEventsConverter circuit__compile_m2d_converter(Circuit &self, bool skip_reference_sample){}
// clbind_CompiledMeasurementSampler circuit__compile_sampler(Circuit &self, bool skip_reference_sample){}
// clbind_CompiledMeasurementSampler circuit__compile_sampler_seed(Circuit &self, bool skip_reference_sample,uint32_t seedn){}
// clbind_CompiledMeasurementSampler circuit__compile_sampler_reference_sample(Circuit &self, bool skip_reference_sample, core::Array_sp reference_sample){}
// clbind_CompiledMeasurementSampler circuit__compile_sampler_reference_sample_seed(Circuit &self, bool skip_reference_sample, core::Array_sp reference_sample,uint32_t seed){}
// Circuit circuit__copy(Circuit &self){}
// uint32_t circuit__count_determined_measurements(Circuit &self){}
// Circuit circuit__decomposed(Circuit &self){}
// core::T_sp circuit__detecting_regions(Circuit &self){}
// core::T_sp circuit__detecting_regions_targets_strings(Circuit &self, std::vector<std::string> targets){}
// core::T_sp circuit__detecting_regions_targets_floats(Circuit &self, std::vector<std::vector<float>> targets){}
// core::T_sp circuit__detecting_regions_targets_strings_ticks(Circuit &self, std::vector<std::string> targets, std::vector<int> ticks){}
// core::T_sp circuit__detecting_regions_targets_floats_ticks(Circuit &self, std::vector<std::vector<float>> targets, std::vector<int> ticks){}
// core::T_sp circuit__detecting_regions_ticks(Circuit &self, std::vector<int> ticks){}
// clbind_DetectorErrorModel circuit__detector_error_model(Circuit &self, bool decompose_errors, bool flatten_loops, bool allow_gauge_detectors, bool approximate_disjoint_errors, bool ignore_decomposition_failures, bool block_decomposition_from_introducting_remnant_edges){}
// clbind_DiagramHelper circuit__diagram_range_float(Circuit &self, std::string type,uint32_t start, uint32_t stop, uint32_t range,std::vector<std::vector<float>> filter_coords){}
// clbind_DiagramHelper circuit__diagram_range_dem_target(Circuit &self, std::string type,uint32_t start, uint32_t stop, uint32_t range,std::vector<DemTarget> filter_coords){}
// clbind_DiagramHelper circuit__diagram_tick_float(Circuit &self, std::string type,uint32_t tick,std::vector<std::vector<float>> filter_coords){}
// clbind_DiagramHelper circuit__diagram_tick_dem_target(Circuit &self, std::string type,uint32_t tick,std::vector<DemTarget> filter_coords){}
// clbind_DiagramHelper circuit__diagram_float(Circuit &self, std::string type,std::vector<std::vector<float>> filter_coords){}
// clbind_DiagramHelper circuit__diagram_dem_target(Circuit &self, std::string type,std::vector<DemTarget> filter_coords){}
// clbind_DiagramHelper circuit__diagram(Circuit &self, std::string type){}
// std::vector<clbind_ExplainedError> circuit__explain_detector_error_model_errors(Circuit &self, DetectorErrorModel dem_filter, bool reduce_to_one_representative_error){}
// clbind_Circuit circuit__flattened(Circuit &self){}
// clbind_Circuit circuit__from_file(std::string file){}
// clbind_Circuit circuit__generated(std::string code_task, uint32_t distance, uint32_t rounds,float after_clifford_depolarization, float before_round_data_depolarization,float before_measure_flip_probability, float after_reset_flip_probability){}
// core::T_sp circuit__get_detector_coordinates(Circuit self){}
// core::T_sp circuit__get_detector_coordinates_only(Circuit self, std::vector<uint32_t> only){}
// core::T_sp circuit__get_final_qubit_coordinates(Circuit self){}
// bool circuit__has_all_flows(Circuit self, std::vector<Flow<MAX_BITWORD_WIDTH>> flows, bool unsigned_p){}
// bool circuit__has_flow(Circuit self, Flow<MAX_BITWORD_WIDTH> flow, bool unsigned_p){}
// Circuit circuit__inverse(Circuit self){}
// std::string circuit__likeliest_error_sat_problem_wdimacs(Circuit self, uint32_t quantization){}
// uint32_t circuit__num_detectors(Circuit self){}
// uint32_t circuit__num_measurements(Circuit self){}
// uint32_t circuit__num_observables(Circuit self){}
// uint32_t circuit__num_qubits(Circuit self){}
// uint32_t circuit__num_sweep_bits(Circuit self){}
// uint32_t circuit__num_ticks(Circuit self){}
// core::T_sp circuit__reference_sample(Circuit self, bool bit_packed){}
// std::vector<ExplainedError> circuit__search_for_undetectable_logical_errors(Circuit self,uint32_t a, uint32_t b,bool c, bool d){}
// std::string circuit__shortest_error_sat_problem_dimacs(Circuit self){}
// std::vector<ExplainedError> circuit__shortest_graphlike_error(Circuit self, bool a, bool b){}
// void circuit__to_file(Circuit self, std::string file){}
// std::string circuit__to_qasm(Circuit self, uint32_t open_qasm_version, bool skip_dets_and_obs){}
// Tableau<MAX_BITWORD_WIDTH> circuit__to_tableau(Circuit self, bool ignore_noise, bool ignore_measurement,bool ignore_reset){}
// Circuit circuit__with_inlined_feedback(Circuit self){}
// Circuit circuit__without_noise(Circuit self){}
// bool circuit_error_location__flipped_measurement_p(CircuitErrorLocation self){}
// FlippedMeasurement circuit_error_location__flipped_measurement(CircuitErrorLocation self){}
// std::vector<GateTargetWithCoords> circuit_error_location__flipped_pauli_product(CircuitErrorLocation self){}
// CircuitTargetsInsideInstruction circuit_error_location__instruction_targets(CircuitErrorLocation self){}
// std::vector<CircuitErrorLocationStackFrame> circuit_error_location__stack_frames(CircuitErrorLocation self){}
// uint32_t circuit_error_location__tick_offset(CircuitErrorLocation self){}
// CircuitErrorLocationStackFrame circuit_error_location_stack_frame__init(int instruction_offset,int iteration_index,int instruction_repetitions_arg){}
// int circuit_error_location_stack_frame__offset(CircuitErrorLocationStackFrame frame){}
// int circuit_error_location_stack_frame__repetitions_arg(CircuitErrorLocationStackFrame frame){}
// int circuit_error_location_stack_frame__iteration_index(CircuitErrorLocationStackFrame frame){}
// bool circuit_instruction__eq(CircuitInstruction self, CircuitInstruction other){}
// CircuitRepeatBlock circuit_instruction__init_ints(std::string name, std::vector<int> targets,std::vector<float> gate_args){}
// CircuitRepeatBlock circuit_instruction__init_gate_targets(std::string name, std::vector<GateTarget> targets,std::vector<float> gate_args){}
// bool circuit_instruction__ne(CircuitInstruction self, CircuitInstruction other){}
// std::string circuit_instruction__repr(CircuitInstruction self){}
// std::string circuit_instruction__str(CircuitInstruction self){}
// std::vector<float> circuit_instruction__gate_args_copy(CircuitInstruction self){}
// std::string circuit_instruction__name(CircuitInstruction self){}
// std::vector<GateTarget> circuit_instruction__targets_copy(CircuitInstruction self){}
// bool circuit_repeat_block__eq(CircuitRepeatBlock self, CircuitRepeatBlock other){}
// CircuitRepeatBlock circuit_repeat_block__init(int repeat_count, Circuit body){}
// bool circuit_repeat_block__ne(CircuitRepeatBlock self, CircuitRepeatBlock other){}
// std::string circuit_repeat_block__repr(CircuitRepeatBlock self){}
// Circuit circuit_repeat_block__body_copy(CircuitRepeatBlock self){}
// bool circuit_repeat_block__name(CircuitRepeatBlock){}
// uint32_t circuit_repeat_block__repeat_count(CircuitRepeatBlock block){}
// CircuitTargetsInsideInstruction circuit_targets_inside_instruction__init(std::string gate, std::vector<float> args, int target_range_start, int target_range_end, std::vector<GateTargetWithCoords> targets_in_range){}
// std::vector<float> circuit_targets_inside_instruction__args(CircuitTargetsInsideInstruction self){}
// bool circuit_targets_inside_instruction__gate_p(CircuitTargetsInsideInstruction self){}
// std::string circuit_targets_inside_instruction__gate(CircuitTargetsInsideInstruction self){}
// int circuit_targets_inside_instruction__target_range_end(CircuitTargetsInsideInstruction self){}
// int circuit_targets_inside_instruction__target_range_start(CircuitTargetsInsideInstruction self){}
// std::vector<GateTargetWithCoords> circuit_targets_inside_instruction__targets_in_range(CircuitTargetsInsideInstruction self){}
// core::T_sp compiled_dem_sampler__sample(clbind_CompiledDemSampler self, int shots, bool bit_packed, bool return_errors){}
// core::T_sp compiled_dem_sampler__sample_recorded_errors_to_replay(clbind_CompiledDemSampler self, int shots,bool bit_packed, bool return_errors,core::T_sp recorded_errors_to_replay){}
// void compiled_dem_sampler__sample_write(clbind_CompiledDemSampler self, int shots,std::string det_out_file, SampleFormat det_out_format,std::string obs_out_file, SampleFormat obs_out_format,std::string err_out_file, SampleFormat err_out_format,std::string replay_err_out_file, SampleFormat replay_err_out_format){}
// CompiledDetectorSampler compiled_detector_sampler__init(Circuit circuit){}
// CompiledDetectorSampler compiled_detector_sampler__init_seed(Circuit circuit, uint32_t seed){}
// std::string compiled_detector_sampler__repr(CompiledDetectorSampler self){}
// core::T_sp compiled_detector_sampler__sample(CompiledDetectorSampler self, int shots,bool prepend_observables, bool append_observables,bool separate_observables,bool bit_packed){}
// void compiled_detector_sampler__sample_write(CompiledDetectorSampler self, int shots,std::string filepath, SampleFormat format,bool prepend_observables, bool append_observables,std::string obs_out_filepath, SampleFormat obs_out_format){}
// void compiled_measurement_sampler__init(){}
// void compiled_measurement_sampler__repr(){}
// void compiled_measurement_sampler__sample(){}
// void compiled_measurement_sampler__sample_write(){}
// void CompiledMeasurementsToDetectionEventsConverter__init(){}
// void CompiledMeasurementsToDetectionEventsConverter__repr(){}
// void CompiledMeasurementsToDetectionEventsConverter__convert(){}
// void CompiledMeasurementsToDetectionEventsConverter__convert_file(){}
// void DemInstruction__eq(){}
// void DemInstruction__init(){}
// void DemInstruction__ne(){}
// void DemInstruction__repr(){}
// void DemInstruction__str(){}
// void DemInstruction__args_copy(){}
// void DemInstruction__targets_copy(){}
// void DemInstruction__type(){}
// void DemRepeatBlock__eq(){}
// void DemRepeatBlock__init(){}
// void DemRepeatBlock__ne(){}
// void DemRepeatBlock__repr(){}
// void DemRepeatBlock__body_copy(){}
// void DemRepeatBlock__repeat_count(){}
// void DemRepeatBlock__type(){}
// void DemTarget__eq(){}
// void DemTarget__ne(){}
// void DemTarget__repr(){}
// void DemTarget__str(){}
// void DemTarget__is_logical_observable_id(){}
// void DemTarget__is_relative_detector_id(){}
// void DemTarget__is_separator(){}
// void DemTarget__logical_observable_id(){}
// void DemTarget__relative_detector_id(){}
// void DemTarget__separator(){}
// void DemTarget__val(){}
// void DemTargetWithCoords__init(){}
// void DemTargetWithCoords__coords(){}
// void DemTargetWithCoords__dem_target(){}
// void DetectorErrorModel__add(){}
// void DetectorErrorModel__eq(){}
// void DetectorErrorModel__getitem(){}
// void DetectorErrorModel__iadd(){}
// void DetectorErrorModel__imul(){}
// void DetectorErrorModel__init(){}
// void DetectorErrorModel__len(){}
// void DetectorErrorModel__mul(){}
// void DetectorErrorModel__ne(){}
// void DetectorErrorModel__repr(){}
// void DetectorErrorModel__rmul(){}
// void DetectorErrorModel__str(){}
// void DetectorErrorModel__append(){}
// void DetectorErrorModel__approx_equals(){}
// void DetectorErrorModel__clear(){}
// void DetectorErrorModel__compile_sampler(){}
// void DetectorErrorModel__copy(){}
// void DetectorErrorModel__diagram(){}
// void DetectorErrorModel__flattened(){}
// void DetectorErrorModel__from_file(){}
// void DetectorErrorModel__get_detector_coordinates(){}
// void DetectorErrorModel__num_detectors(){}
// void DetectorErrorModel__num_errors(){}
// void DetectorErrorModel__num_observables(){}
// void DetectorErrorModel__rounded(){}
// void DetectorErrorModel__shortest_graphlike_error(){}
// void DetectorErrorModel__to_file(){}
// void ExplainedError(){}
// void ExplainedError__init(){}
// void ExplainedError__circuit_error_locations(){}
// void ExplainedError__dem_error_terms(){}
// void FlipSimulator(){}
// void FlipSimulator__init(){}
// void FlipSimulator__batch_size(){}
// void FlipSimulator__broadcast_pauli_errors(){}
// void FlipSimulator__do(){}
// void FlipSimulator__get_detector_flips(){}
// void FlipSimulator__get_measurement_flips(){}
// void FlipSimulator__get_observable_flips(){}
// void FlipSimulator__num_detectors(){}
// void FlipSimulator__num_measurements(){}
// void FlipSimulator__num_observables(){}
// void FlipSimulator__num_qubits(){}
// void FlipSimulator__peek_pauli_flips(){}
// void FlipSimulator__set_pauli_flip(){}
// void FlippedMeasurement__init(){}
// void FlippedMeasurement__observable(){}
// void FlippedMeasurement__record_index(){}
// void Flow__eq(){}
// void Flow__init(){}
// void Flow__ne(){}
// void Flow__repr(){}
// void Flow__str(){}
// void Flow__input_copy(){}
// void Flow__measurements_copy(){}
// void Flow__output_copy(){}
// void GateData__eq(){}
// void GateData__init(){}
// void GateData__ne(){}
// void GateData__repr(){}
// void GateData__str(){}
// void GateData__aliases(){}
// void GateData__flows(){}
// void GateData__generalized_inverse(){}
// void GateData__inverse(){}
// void GateData__is_noisy_gate(){}
// void GateData__is_reset(){}
// void GateData__is_single_qubit_gate(){}
// void GateData__is_two_qubit_gate(){}
// void GateData__is_unitary(){}
// void GateData__name(){}
// void GateData__num_parens_arguments_range(){}
// void GateData__produces_measurements(){}
// void GateData__tableau(){}
// void GateData__takes_measurement_record_targets(){}
// void GateData__takes_pauli_targets(){}
// void GateData__unitary_matrix(){}
// void GateTarget__eq(){}
// void GateTarget__init(){}
// void GateTarget__ne(){}
// void GateTarget__repr(){}
// void GateTarget__is_combiner(){}
// void GateTarget__is_inverted_result_target(){}
// void GateTarget__is_measurement_record_target(){}
// void GateTarget__is_qubit_target(){}
// void GateTarget__is_sweep_bit_target(){}
// void GateTarget__is_x_target(){}
// void GateTarget__is_y_target(){}
// void GateTarget__is_z_target(){}
// void GateTarget__pauli_type(){}
// void GateTarget__qubit_value(){}
// void GateTarget__value(){}
// void GateTargetWithCoords__init(){}
// void GateTargetWithCoords__coords(){}
// void GateTargetWithCoords__gate_target(){}
// void PauliString__add(){}
// void PauliString__eq(){}
// void PauliString__getitem(){}
// void PauliString__iadd(){}
// void PauliString__imul(){}
// void PauliString__init(){}
// void PauliString__itruediv(){}
// void PauliString__len(){}
// void PauliString__mul(){}
// void PauliString__ne(){}
// void PauliString__neg(){}
// void PauliString__pos(){}
// void PauliString__repr(){}
// void PauliString__rmul(){}
// void PauliString__setitem(){}
// void PauliString__str(){}
// void PauliString__truediv(){}
// void PauliString__after(){}
// void PauliString__before(){}
// void PauliString__commutes(){}
// void PauliString__copy(){}
// void PauliString__from_numpy(){}
// void PauliString__from_unitary_matrix(){}
// void PauliString__iter_all(){}
// void PauliString__pauli_indices(){}
// void PauliString__random(){}
// void PauliString__sign(){}
// void PauliString__to_numpy(){}
// void PauliString__to_tableau(){}
// void PauliString__to_unitary_matrix(){}
// void PauliString__weight(){}
// void PauliStringIterator__iter(){}
// void PauliStringIterator__next(){}
// void Tableau__add(){}
// void Tableau__call(){}
// void Tableau__eq(){}
// void Tableau__iadd(){}
// void Tableau__init(){}
// void Tableau__len(){}
// void Tableau__mul(){}
// void Tableau__ne(){}
// void Tableau__pow(){}
// void Tableau__repr(){}
// void Tableau__str(){}
// void Tableau__append(){}
// void Tableau__copy(){}
// void Tableau__from_circuit(){}
// void Tableau__from_conjugated_generators(){}
// void Tableau__from_named_gate(){}
// void Tableau__from_numpy(){}
// void Tableau__from_stabilizers(){}
// void Tableau__from_state_vector(){}
// void Tableau__from_unitary_matrix(){}
// void Tableau__inverse(){}
// void Tableau__inverse_x_output(){}
// void Tableau__inverse_x_output_pauli(){}
// void Tableau__inverse_y_output(){}
// void Tableau__inverse_y_output_pauli(){}
// void Tableau__inverse_z_output(){}
// void Tableau__inverse_z_output_pauli(){}
// void Tableau__iter_all(){}
// void Tableau__prepend(){}
// void Tableau__random(){}
// void Tableau__then(){}
// void Tableau__to_circuit(){}
// void Tableau__to_numpy(){}
// void Tableau__to_pauli_string(){}
// void Tableau__to_stabilizers(){}
// void Tableau__to_state_vector(){}
// void Tableau__to_unitary_matrix(){}
// void Tableau__x_output(){}
// void Tableau__x_output_pauli(){}
// void Tableau__x_sign(){}
// void Tableau__y_output(){}
// void Tableau__y_output_pauli(){}
// void Tableau__y_sign(){}
// void Tableau__z_output(){}
// void Tableau__z_output_pauli(){}
// void Tableau__z_sign(){}
// void TableauIterator__iter(){}
// void TableauIterator__next(){}
// void TableauSimulator__init(){}
// void TableauSimulator__c_xyz(){}
// void TableauSimulator__c_zyx(){}
// void TableauSimulator__canonical_stabilizers(){}
// void TableauSimulator__cnot(){}
// void TableauSimulator__copy(){}
// void TableauSimulator__current_inverse_tableau(){}
// void TableauSimulator__current_measurement_record(){}
// void TableauSimulator__cx(){}
// void TableauSimulator__cy(){}
// void TableauSimulator__cz(){}
// void TableauSimulator__depolarize1(){}
// void TableauSimulator__depolarize2(){}
// void TableauSimulator__do(){}
// void TableauSimulator__do_circuit(){}
// void TableauSimulator__do_pauli_string(){}
// void TableauSimulator__do_tableau(){}
// void TableauSimulator__h(){}
// void TableauSimulator__h_xy(){}
// void TableauSimulator__h_xz(){}
// void TableauSimulator__h_yz(){}
// void TableauSimulator__iswap(){}
// void TableauSimulator__iswap_dag(){}
// void TableauSimulator__measure(){}
// void TableauSimulator__measure_kickback(){}
// void TableauSimulator__measure_many(){}
// void TableauSimulator__measure_observable(){}
// void TableauSimulator__num_qubits(){}
// void TableauSimulator__peek_bloch(){}
// void TableauSimulator__peek_observable_expectation(){}
// void TableauSimulator__peek_x(){}
// void TableauSimulator__peek_y(){}
// void TableauSimulator__peek_z(){}
// void TableauSimulator__postselect_observable(){}
// void TableauSimulator__postselect_x(){}
// void TableauSimulator__postselect_y(){}
// void TableauSimulator__postselect_z(){}
// void TableauSimulator__reset(){}
// void TableauSimulator__reset_x(){}
// void TableauSimulator__reset_y(){}
// void TableauSimulator__reset_z(){}
// void TableauSimulator__s(){}
// void TableauSimulator__s_dag(){}
// void TableauSimulator__set_inverse_tableau(){}
// void TableauSimulator__set_num_qubits(){}
// void TableauSimulator__set_state_from_stabilizers(){}
// void TableauSimulator__set_state_from_state_vector(){}
// void TableauSimulator__sqrt_x(){}
// void TableauSimulator__sqrt_x_dag(){}
// void TableauSimulator__sqrt_y(){}
// void TableauSimulator__sqrt_y_dag(){}
// void TableauSimulator__state_vector(){}
// void TableauSimulator__swap(){}
// void TableauSimulator__x(){}
// void TableauSimulator__x_error(){}
// void TableauSimulator__xcx(){}
// void TableauSimulator__xcy(){}
// void TableauSimulator__xcz(){}
// void TableauSimulator__y(){}
// void TableauSimulator__y_error(){}
// void TableauSimulator__ycx(){}
// void TableauSimulator__ycy(){}
// void TableauSimulator__ycz(){}
// void TableauSimulator__z(){}
// void TableauSimulator__z_error(){}
// void TableauSimulator__zcx(){}
// void TableauSimulator__zcy(){}
// void TableauSimulator__zcz(){}

}
