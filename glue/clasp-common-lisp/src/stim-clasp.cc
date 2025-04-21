#include <fmt/format.h>
#include <clasp/clasp.h>
#include "stim.h"

namespace translate {
  // template <>
  // struct from_object<uint64_t>
  // {
  //   typedef uint64_t DeclareType;
  //   DeclareType _v;
  //   from_object(core::T_sp obj)
  //   {
  //     this->_v = core::clasp_to_int(obj);
  //   }
  // };
  template <> struct to_object<uint64_t> {
    typedef uint64_t DeclareType;
    static core::T_sp convert(DeclareType v)
    {
      return core::Integer_O::create(v);
    }
  };
};

namespace clasp_stim {

  void hello_world(double x, double y) { fmt::print("Hello World! Did you know that {} + {} = {}?\n", x, y, x + y); }

  uint64_t saturate_test(){return 4;}

  extern "C" void startup_clasp_extension() {
    using namespace clbind;
    using namespace stim;
    fmt::print("Entered {}:{}:{}\n", __FILE__, __LINE__, __FUNCTION__);
    package_ s("STIM", {}, {"COMMON-LISP"});
    s.def("hello-world", &hello_world, "(x y)"_ll, "Hello world that adds numbers."_docstring);
    s.def("saturate-test", &saturate_test, "()"_ll, "abc"_docstring);
    fmt::print("saturate-test:{}\n",saturate_test());
    fmt::print("Exited {}:{}:{}\n", __FILE__, __LINE__, __FUNCTION__);
  }
}; // namespace clasp_stim
