#include "benchmark/benchmark_api.h"
#include "benchmarks/bench/make_exception/benchmark_make_exception.hpp"

namespace benchmarks {
namespace bench {
namespace make_exception {
BENCHMARK_F(Benchmark_make_exception,
            MakeExceptionBasic)(benchmark::State& st) {
  // custom <make_exception_basic benchmark pre while>
  // end <make_exception_basic benchmark pre while>

  while (st.KeepRunning()) {
    // custom <make_exception_basic benchmark while>

    try {
      function_with_exception();
    } catch (Sample_exception const& e) {
      // std::cout << boost::diagnostic_information(e);
    }

    // end <make_exception_basic benchmark while>
  }
  // custom <make_exception_basic benchmark post while>
  // end <make_exception_basic benchmark post while>
}
BENCHMARK_F(Benchmark_make_exception,
            MakeExceptionWithFunctionName)(benchmark::State& st) {
  // custom <make_exception_with_function_name benchmark pre while>
  // end <make_exception_with_function_name benchmark pre while>

  while (st.KeepRunning()) {
    // custom <make_exception_with_function_name benchmark while>

    try {
      named_function_with_exception();
    } catch (Sample_exception const& e) {
      // std::cout << boost::diagnostic_information(e);
    }

    // end <make_exception_with_function_name benchmark while>
  }
  // custom <make_exception_with_function_name benchmark post while>
  // end <make_exception_with_function_name benchmark post while>
}
BENCHMARK_F(Benchmark_make_exception, BoostThrow)(benchmark::State& st) {
  // custom <boost_throw benchmark pre while>
  // end <boost_throw benchmark pre while>

  while (st.KeepRunning()) {
    // custom <boost_throw benchmark while>

    try {
      boost_throw_exception();
    } catch (Boost_style_exception const& e) {
    }

    // end <boost_throw benchmark while>
  }
  // custom <boost_throw benchmark post while>
  // end <boost_throw benchmark post while>
}
BENCHMARK_F(Benchmark_make_exception, NoThrow)(benchmark::State& st) {
  // custom <no_throw benchmark pre while>
  // end <no_throw benchmark pre while>

  while (st.KeepRunning()) {
    // custom <no_throw benchmark while>

    no_throw();

    // end <no_throw benchmark while>
  }
  // custom <no_throw benchmark post while>
  // end <no_throw benchmark post while>
}

}  // namespace make_exception
}  // namespace bench
}  // namespace benchmarks

BENCHMARK_MAIN()
