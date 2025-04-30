#include <clasp/clasp.h>
#include "stim.h"

// Enums
using namespace stim;


// namespace translate
// {
//   template <>
//   struct to_object<clasp_stim::Level>
//   {
//     static core::T_sp convert(clasp_stim::Level arg)
//     {
//       switch(arg){
//       case clasp_stim::LOW: return core::lisp_intern("LOW","KEYWORD");
//       case clasp_stim::MEDIUM: return core::lisp_intern("MEDIUM","KEYWORD");
//       case clasp_stim::HIGH: return core::lisp_intern("HIGH","KEYWORD");
//       }
//     }
//   };
//   template <>
//   struct from_object<clasp_stim::Level>
//   {
//     typedef clasp_stim::Level DeclareType;                             // (1)
//     DeclareType _v;
//     from_object(core::T_sp obj)
//     {
//       if(cl__keywordp(obj)){
//         core::Symbol_sp s = obj.asOrNull<core::Symbol_O>();
//         std::string name = s->_Name->get_std_string();
//         if(name == "HIGH")
//           this->_v=clasp_stim::HIGH;
//         else if(name == "MEDIUM")
//           this->_v=clasp_stim::MEDIUM;
//         else if(name == "LOW")
//           this->_v=clasp_stim::LOW;
//         else SIMPLE_ERROR("Invalid keyword for enum Level, expected one of :HIGH, :MEDIUM or :LOW");
//       }
//       else TYPE_ERROR(obj,cl::_sym_Symbol_O);
//     }
//   };
// };
