#ifndef __EBISU_UTILS_HISTOGRAM_HPP__
#define __EBISU_UTILS_HISTOGRAM_HPP__

#include "ebisu/utils/block_indenter.hpp"
#include "ebisu/utils/streamers/containers.hpp"
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/density.hpp>
#include <boost/algorithm/minmax_element.hpp>
#include <iostream>
#include <vector>

namespace ebisu {
namespace utils {
template <typename T = double>
class HistogramStatistical {
 public:
  using AccumulatorT = boost::accumulators::accumulator_set<
      T, boost::accumulators::features<boost::accumulators::tag::density> >;
  using HistResultsT =
      boost::iterator_range<typename std::vector<std::pair<T, T> >::iterator>;

  HistogramStatistical(int numBins = 20, int cacheSize = 10)
      : numBins_(numBins), cacheSize_(cacheSize) {}

  // custom <ClsPublic Histogram_statistical>

  void operator()(T item) { accumulator_(item); }

  // end <ClsPublic Histogram_statistical>

  //! getter for numBins_ (access is Ro)
  int numBins() const { return numBins_; }

  //! getter for cacheSize_ (access is Ro)
  int cacheSize() const { return cacheSize_; }

  //! getter for accumulator_ (access is Ro)
  Accumulator_t accumulator() const { return accumulator_; }

 private:
  int const numBins_;
  int const cacheSize_;
  Accumulator_t accumulator_{
      boost::accumulators::tag::density::num_bins = num_bins_,
      boost::accumulators::tag::density::cache_size = cache_size_};
};

template <typename T = double>
class Histogram {
 public:
  using ResultVector = std::vector<T>;

  explicit template <typename IT>

  Histogram(IT begin, IT end, int numBins = 20)
      : numBins_(numBins) {
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
    out << "\n  numBins:" << item.numBins_;
    out << "\n  results:" << item.results_;
    out << "\n}\n";
    return out;
  }

  //! getter for numBins_ (access is Ro)
  int numBins() const { return numBins_; }

  //! getter for results_ (access is Ro)
  Result_vector_t results() const { return results_; }

 private:
  int const numBins_{20};
  Result_vector_t results_{Result_vector_t(num_bins_)};
};

}  // namespace utils
}  // namespace ebisu

#endif  // __EBISU_UTILS_HISTOGRAM_HPP__
