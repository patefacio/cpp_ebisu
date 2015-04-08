#ifndef __FCS_UTILS_HISTOGRAM_HPP__
#define __FCS_UTILS_HISTOGRAM_HPP__

#include "fcs/utils/block_indenter.hpp"
#include "fcs/utils/streamers/containers.hpp"
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/density.hpp>
#include <boost/algorithm/minmax_element.hpp>
#include <iostream>
#include <vector>

namespace fcs {
namespace utils {
template <typename T = double>
class Histogram_statistical {
 public:
  using Accumulator_t = boost::accumulators::accumulator_set<
      T, boost::accumulators::features<boost::accumulators::tag::density> >;
  using Hist_results_t =
      boost::iterator_range<typename std::vector<std::pair<T, T> >::iterator>;

  Histogram_statistical(int num_bins = 20, int cache_size = 10)
      : num_bins_{num_bins}, cache_size_{cache_size} {}

  // custom <ClsPublic Histogram_statistical>

  void operator()(T item) { accumulator_(item); }

  // end <ClsPublic Histogram_statistical>

  //! getter for num_bins_ (access is Ro)
  int num_bins() const { return num_bins_; }

  //! getter for cache_size_ (access is Ro)
  int cache_size() const { return cache_size_; }

  //! getter for accumulator_ (access is Ro)
  Accumulator_t accumulator() const { return accumulator_; }

 private:
  int const num_bins_;
  int const cache_size_;
  Accumulator_t accumulator_{
      boost::accumulators::tag::density::num_bins = num_bins_,
      boost::accumulators::tag::density::cache_size = cache_size_};
};

template <typename T = double>
class Histogram {
 public:
  using Result_vector_t = vector<T>;

  template <typename IT>

  Histogram(IT begin, IT end, int num_bins = 20)
      : num_bins_{num_bins} {
    // custom <Histogram(from_iterator)>

    std::pair<IT, IT> min_and_max(boost::minmax_element(begin, end));
    T smallest(*min_and_max.first);
    T largest(*min_and_max.second);
    std::cout << "Smallest is: " << smallest << " largest is: " << largest
              << std::endl;

    // end <Histogram(from_iterator)>
  }

  friend inline std::ostream& operator<<(std::ostream& out,
                                         Histogram const& item) {
    out << "Histogram(" << &item << ") {";
    out << "\n  num_bins:" << item.num_bins_;
    out << "\n  results:" << item.results_;
    out << "\n}\n";
    return out;
  }

  //! getter for num_bins_ (access is Ro)
  int num_bins() const { return num_bins_; }

  //! getter for results_ (access is Ro)
  Result_vector_t results() const { return results_; }

 private:
  int const num_bins_{20};
  Result_vector_t results_{Result_vector_t(num_bins_)};
};

}  // namespace utils
}  // namespace fcs

#endif  // __FCS_UTILS_HISTOGRAM_HPP__
