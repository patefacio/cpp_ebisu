#ifndef __FCS_UTILS_BLOCK_INDENTER_HPP__
#define __FCS_UTILS_BLOCK_INDENTER_HPP__

#include <boost/thread/tss.hpp>

namespace fcs {
namespace utils {
class Block_current_indent {
 public:
  static Block_current_indent& instance() {
    static Block_current_indent instance_s;
    return instance_s;
  }

    // custom <ClsPublic Block_current_indent>

    inline void increment_indent() {
      initialize_tss();
      ++(*indentation_length_);
    }

    inline void decrement_indent() {
      initialize_tss();
      --(*indentation_length_);
    }

    inline char const* current_indentation_text() {
        char const* result("");
        switch(*indentation_length_) {
         case 0: result = ""; break;
         case 1: result = "  "; break;
         case 2: result = "    "; break;
         case 3: result = "      "; break;
         case 4: result = "        "; break;
         case 5: result = "          "; break;
         case 6: result = "            "; break;
         case 7: result = "              "; break;
         case 8: result = "                "; break;
         case 9: result = "                  "; break;
         default: result = "                    "; break;
        }
        return result;
    }

    // end <ClsPublic Block_current_indent>

 private:
    // custom <ClsPrivate Block_current_indent>

    inline void initialize_tss() {
      if(!indentation_length_.get()) {
        indentation_length_.reset(new int(0));
      }
    }

    // end <ClsPrivate Block_current_indent>

  boost::thread_specific_ptr<int> indentation_length_{};
};

class Block_indenter {
 public:
    // custom <ClsPublic Block_indenter>

    Block_indenter() {
      Block_current_indent::instance().increment_indent();
    }

    ~Block_indenter() {
      Block_current_indent::instance().decrement_indent();
    }

    inline char const* current_indentation_text() {
      return Block_current_indent::instance().current_indentation_text();
    }

    // end <ClsPublic Block_indenter>
};

}  // namespace utils
}  // namespace fcs
#endif  // __FCS_UTILS_BLOCK_INDENTER_HPP__
