#ifndef __FCS_UTILS_UTILS_HPP__
#define __FCS_UTILS_UTILS_HPP__

#include <cmath>
#include <iostream>

// custom <FcbPreNamespace utils>
// end <FcbPreNamespace utils>

namespace fcs {
namespace utils {
  // custom <FcbBeginNamespace utils>
  // end <FcbBeginNamespace utils>

  // custom <ClsPreDecl Block_indenter>
  // end <ClsPreDecl Block_indenter>

  class Block_indenter
  {

  public:
  // custom <ClsPublic Block_indenter>
  // end <ClsPublic Block_indenter>



  };
  // custom <ClsPostDecl Block_indenter>
  // end <ClsPostDecl Block_indenter>

  class Value_min_max
  {

  };
  class Fixed_size_char_array
  {

  };
  class Version_control_commit
  {

  };
  // custom <ClsPreDecl Histogram>
  // end <ClsPreDecl Histogram>

  template< typename T = double, typename T2 = int >
  class Histogram
  {

  public:
    std::string moo_ { "falal" };

    //! getter for num_bins_ (access is Ro)
    int num_bins() const { return num_bins_; }

    //! getter for results_ (access is Ro)
    Result_vector_t results() const { return results_; }

    //! getter for pi_ (access is Rw)
    double pi() const { return pi_; }
    //! setter for pi_ (access is Rw)
    void pi(double pi) { pi_ = pi; }

    //! getter for goo_ (access is Rw)
    std::string & goo() const { return goo_; }
    //! setter for goo_ (access is Rw)
    void goo(std::string & goo) { goo_ = goo; }


  protected:
    // custom <ClsProtected Histogram>
    // end <ClsProtected Histogram>

    std::string zoo_ { "falal" };

  private:
    int num_bins_ { 20 };
    Result_vector_t results_ { Result_vector_t(num_bins_,999) };
    double pi_;
    somenumtype & pid_ { (3.14**2.0) };
    std::string goo_ { "Fooberger" };

  };
  // custom <FcbEndNamespace utils>
  // end <FcbEndNamespace utils>

} // namespace utils
} // namespace fcs
// custom <FcbPostNamespace utils>
// end <FcbPostNamespace utils>

#endif // __FCS_UTILS_UTILS_HPP__
