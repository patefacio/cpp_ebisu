#ifndef __BENCHMARKS_BENCH_MAKE_EXCEPTION_BENCHMARK_MAKE_EXCEPTION_HPP__
#define __BENCHMARKS_BENCH_MAKE_EXCEPTION_BENCHMARK_MAKE_EXCEPTION_HPP__

#include "benchmark/benchmark.h"
#include "ebisu/utils/exception/make_exception.hpp"
#include <boost/exception/exception.hpp>
#include <stdexcept>

namespace benchmarks {
namespace bench {
namespace make_exception {
// custom <FcbBeginNamespace benchmark_make_exception>

// end <FcbBeginNamespace benchmark_make_exception>

class BoostStyleException : public virtual std::exception,
                            public virtual boost::exception {};

class SampleException : public virtual std::runtime_error,
                        public virtual boost::exception {
 public:
  /// Constructs exception object with explanatory what_arg accessible through
  /// what().
  explicit SampleException(const std::string& what_arg)
      : std::runtime_error(what_arg) {}

  /// Constructs exception object with explanatory what_arg accessible through
  /// what().
  explicit SampleException(const char* what_arg)
      : std::runtime_error(what_arg) {}
};

class BenchmarkMakeException : public ::benchmark::Fixture {
 public:
  // custom <ClsPublic Benchmark_make_exception>

  /// Function to do some work
  unsigned fibo(unsigned n) {
    if (n <= 1) return n;
    return fibo(n - 1) + fibo(n - 2);
  }

  void function_with_exception() {
    fibo(15);
    throw ebisu::utils::exception::make_exception<Sample_exception>(
        "fibo", __LINE__, __FILE__);
  }

  void named_function_with_exception() {
    fibo(15);
    throw ebisu::utils::exception::make_exception<Sample_exception>(
        "fibo", __FUNCTION__, __LINE__, __FILE__);
  }

  void boost_throw_exception() {
    fibo(15);
    Boost_style_exception e;
    BOOST_THROW_EXCEPTION(e);
  }

  void no_throw() noexcept { fibo(15); }

  // end <ClsPublic Benchmark_make_exception>

  void SetUp() {
    // custom <benchmark_make_exception setup>
    // end <benchmark_make_exception setup>
  }

  void TearDown() {
    // custom <benchmark_make_exception teardown>
    // end <benchmark_make_exception teardown>
  }
};

// custom <FcbEndNamespace benchmark_make_exception>
// end <FcbEndNamespace benchmark_make_exception>

}  // namespace make_exception
}  // namespace bench
}  // namespace benchmarks

#endif  // __BENCHMARKS_BENCH_MAKE_EXCEPTION_BENCHMARK_MAKE_EXCEPTION_HPP__
