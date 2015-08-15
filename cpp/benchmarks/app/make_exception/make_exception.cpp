#include "benchmark/benchmark_api.h"
#include "benchmarks/bench/make_exception/make_exception.hpp"

namespace benchmark {

static void make_exception(benchmark::State& state) {
  while (state.KeepRunning()) {
  }
}

BENCHMARK(make_exception);

}  // namespace benchmark

BENCHMARK_MAIN()
