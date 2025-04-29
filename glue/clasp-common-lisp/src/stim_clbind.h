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
  // stim_pybind::pybind_read_write
  //void write_shot_data_file(core::MDArray_sp data, std::string path_obj, SampleFormat format, size_t num_measurements, size_t num_detectors, size_t num_observables);
  //core::MDArray_sp read_shot_data_file(std::string path_obj, SampleFormat format, size_t num_measurements, size_t num_detectors, size_t num_observables, bool separate_observables, bool bit_packed, bool _legacy_bit_pack);

  GateTarget gate_target_from_target_str(std::string v);
  FlexPauliString flex_pauli_from_text(std::string v);
  FlexPauliString pauli_iterator_get_current(const PauliStringIterator<MAX_BITWORD_WIDTH> iterator);
    }
