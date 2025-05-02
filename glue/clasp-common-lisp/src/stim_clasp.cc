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

}
