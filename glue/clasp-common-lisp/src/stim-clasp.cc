#include <fmt/format.h>
#include <clasp/clasp.h>

namespace hw {

  void hello_world(double x, double y) { fmt::print("Hello World! Did you know that {} + {} = {}?\n", x, y, x + y); }

  extern "C" void startup_clasp_extension() {
    using namespace clbind;
    fmt::print("Entered {}:{}:{}\n", __FILE__, __LINE__, __FUNCTION__);
    package_ s("HELLO-WORLD", {}, {"COMMON-LISP"});
    s.def("hello-world", &hello_world, "(x y)"_ll, "Hello world that adds numbers."_docstring);
    fmt::print("Exited {}:{}:{}\n", __FILE__, __LINE__, __FUNCTION__);
  }
 
}; // namespace hw
