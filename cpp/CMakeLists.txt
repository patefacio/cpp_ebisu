cmake_minimum_required (VERSION 2.8)

include(CheckCXXCompilerFlag)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -DDEBUG")

######################################################################
# Find boost and include desired components
######################################################################
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.54.0 COMPONENTS program_options system thread
# custom <boost lib components>
  date_time
  regex
  filesystem
# end <boost lib components>
)

## TO ENABLE LIB INIT LOGGING MOVE THIS TO custom
## set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLIB_INIT_LOGGING")

# custom <misc section>

add_definitions(-DOTL_ODBC_UNIX)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLIB_INIT_LOGGING")

# end <misc section>


######################################################################
# Add additional link directories
######################################################################
link_directories(
# custom <link directories>

  ~/dev/open_source/HDF518CMake/build/HDF_Group/HDF5/1.8.15-patch1/lib

# end <link directories>

)

enable_testing()

######################################################################
# Add additional include directories
######################################################################
include_directories(
  ${CMAKE_CURRENT_LIST_DIR}
  ${Boost_INCLUDE_DIRS}
# custom <include directories>

  ../install/catch/include
  ../install/spdlog/include
  ~/dev/open_source/HDF518CMake/build/HDF_Group/HDF5/1.8.15-patch1/include
  
# end <include directories>

)

######################################################################
# Lib sources
######################################################################
set (EBISU_LINUX_SPECIFIC_SOURCES,
  ebisu/linux_specific/application_signal_handler.hpp
  ebisu/linux_specific/umask_scoped_set.hpp
  ebisu/linux_specific/linux_exceptions.hpp
  ebisu/linux_specific/cpu_info.hpp
  ebisu/linux_specific/linux_specific_logging.hpp
)

set (EBISU_UTILS_SOURCES,
  ebisu/utils/block_indenter.hpp
  ebisu/utils/buffer.hpp
  ebisu/utils/fixed_size_char_array.hpp
  ebisu/utils/version_control_commit.hpp
  ebisu/utils/histogram.hpp
)

set (EBISU_UTILS_EXCEPTION_SOURCES,
  ebisu/utils/exception/make_exception.hpp
)

set (EBISU_UTILS_STREAMERS_SOURCES,
  ebisu/utils/streamers/containers.hpp
  ebisu/utils/streamers/streamers.hpp
  ebisu/utils/streamers/random.hpp
  ebisu/utils/streamers/table.hpp
  ebisu/utils/streamers/vector.hpp
  ebisu/utils/streamers/set.hpp
  ebisu/utils/streamers/map.hpp
  ebisu/utils/streamers/list.hpp
  ebisu/utils/streamers/array.hpp
  ebisu/utils/streamers/deque.hpp
  ebisu/utils/streamers/ptr_map.hpp
  ebisu/utils/streamers/ptr_set.hpp
  ebisu/utils/streamers/ptr_vector.hpp
)

set (EBISU_RAII_SOURCES,
  ebisu/raii/change_tracker.hpp
  ebisu/raii/api_initializer.hpp
  ebisu/raii/raii_common.hpp
  ebisu/raii/raii_logging.hpp
  ebisu/raii/raii_initialization.hpp
)

set (EBISU_ORM_SOURCES,
  ebisu/orm/orm_to_string_table.hpp
  ebisu/orm/otl_utils.hpp
  ebisu/orm/orm_common.hpp
)

set (EBISU_TIMESTAMP_SOURCES,
  ebisu/timestamp/timestamp.hpp
  ebisu/timestamp/cereal.hpp
)

set (EBISU_TIMESTAMP_SOURCES,
  ebisu/timestamp/conversion.hpp
)

set (EBISU_PERFORMANCE_SOURCES,
  ebisu/performance/block_timers.hpp
  ebisu/performance/block_rusage.hpp
  ebisu/performance/performance_common.hpp
  ebisu/performance/performance_logging.hpp
  ebisu/performance/performance_initialization.hpp
)

set (EBISU_H5_UTILS_SOURCES,
  ebisu/h5/utils/h5_random_access_store.hpp
  ebisu/h5/utils/h5_utils_logging.hpp
)

set (EBISU_MONGO_SOURCES,
  ebisu/mongo/connection_registry.hpp
  ebisu/mongo/mongo_ini.hpp
  ebisu/mongo/mongo_logging.hpp
)

set (BENCHMARKS_BENCH_MAKE_EXCEPTION_SOURCES,
  benchmarks/bench/make_exception/benchmark_make_exception.hpp
)


######################################################################
# Application build directives
######################################################################
add_executable(date_time_converter
  app/date_time_converter/date_time_converter.cpp
)

# custom <date_time_converter exe additions>
# end <date_time_converter exe additions>

target_link_libraries(date_time_converter
# custom <date_time_converter libs>
  ${Boost_DATE_TIME_LIBRARY}
  ${Boost_REGEX_LIBRARY}
# end <date_time_converter libs>
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
)

add_executable(display_csv
  app/display_csv/display_csv.cpp
)

# custom <display_csv exe additions>
# end <display_csv exe additions>

target_link_libraries(display_csv
# custom <display_csv libs>
# end <display_csv libs>
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
)

add_executable(h5ds2csv
  app/h5ds2csv/h5ds2csv.cpp
)

# custom <h5ds2csv exe additions>
# end <h5ds2csv exe additions>

target_link_libraries(h5ds2csv
# custom <h5ds2csv libs>
# end <h5ds2csv libs>
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
)


######################################################################
# Test directives
######################################################################

#   test for test_application_signal_handler
#     (Lib:linux_specific), (Header:application_signal_handler), (Test:application_signal_handler)
#   
add_executable(linux_specific.header.application_signal_handler
  tests/linux_specific/header.application_signal_handler.cpp
)

# custom <test_application_signal_handler test additions>
# end <test_application_signal_handler test additions>

target_link_libraries(linux_specific.header.application_signal_handler
# custom <catch test_application_signal_handler link requirements>
    -pthread
# end <catch test_application_signal_handler link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  linux_specific.header.application_signal_handler
  linux_specific.header.application_signal_handler)


#   test for test_umask_scoped_set
#     (Lib:linux_specific), (Header:umask_scoped_set), (Test:umask_scoped_set)
#   
add_executable(linux_specific.header.umask_scoped_set
  tests/linux_specific/header.umask_scoped_set.cpp
)

# custom <test_umask_scoped_set test additions>
# end <test_umask_scoped_set test additions>

target_link_libraries(linux_specific.header.umask_scoped_set
# custom <catch test_umask_scoped_set link requirements>
# end <catch test_umask_scoped_set link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  linux_specific.header.umask_scoped_set
  linux_specific.header.umask_scoped_set)


#   test for test_cpu_info
#     (Lib:linux_specific), (Header:cpu_info), (Class:cpu_info), (Test:cpu_info)
#   
add_executable(linux_specific.class.cpu_info.cpu_info
  tests/linux_specific/class.cpu_info.cpu_info.cpp
)

# custom <test_cpu_info test additions>
# end <test_cpu_info test additions>

target_link_libraries(linux_specific.class.cpu_info.cpu_info
# custom <catch test_cpu_info link requirements>
  ${Boost_REGEX_LIBRARY}
# end <catch test_cpu_info link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  linux_specific.class.cpu_info.cpu_info
  linux_specific.class.cpu_info.cpu_info)


#   test for test_buffer
#     (Lib:utils), (Header:buffer), (Test:buffer)
#   
add_executable(utils.header.buffer
  tests/utils/header.buffer.cpp
)

# custom <test_buffer test additions>
# end <test_buffer test additions>

target_link_libraries(utils.header.buffer
# custom <catch test_buffer link requirements>
# end <catch test_buffer link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  utils.header.buffer
  utils.header.buffer)


#   test for test_fixed_size_char_array
#     (Lib:utils), (Header:fixed_size_char_array), (Test:fixed_size_char_array)
#   
add_executable(utils.header.fixed_size_char_array
  tests/utils/header.fixed_size_char_array.cpp
)

# custom <test_fixed_size_char_array test additions>
# end <test_fixed_size_char_array test additions>

target_link_libraries(utils.header.fixed_size_char_array
# custom <catch test_fixed_size_char_array link requirements>
# end <catch test_fixed_size_char_array link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  utils.header.fixed_size_char_array
  utils.header.fixed_size_char_array)


#   test for test_change_tracker_next_value
#     (Lib:raii), (Header:change_tracker), (Class:change_tracker_next_value), (Test:change_tracker_next_value)
#   
add_executable(raii.class.change_tracker.change_tracker_next_value
  tests/raii/class.change_tracker.change_tracker_next_value.cpp
)

# custom <test_change_tracker_next_value test additions>
# end <test_change_tracker_next_value test additions>

target_link_libraries(raii.class.change_tracker.change_tracker_next_value
# custom <catch test_change_tracker_next_value link requirements>
# end <catch test_change_tracker_next_value link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  raii.class.change_tracker.change_tracker_next_value
  raii.class.change_tracker.change_tracker_next_value)


#   test for test_change_until_end_of_block
#     (Lib:raii), (Header:change_tracker), (Class:change_until_end_of_block), (Test:change_until_end_of_block)
#   
add_executable(raii.class.change_tracker.change_until_end_of_block
  tests/raii/class.change_tracker.change_until_end_of_block.cpp
)

# custom <test_change_until_end_of_block test additions>
# end <test_change_until_end_of_block test additions>

target_link_libraries(raii.class.change_tracker.change_until_end_of_block
# custom <catch test_change_until_end_of_block link requirements>
# end <catch test_change_until_end_of_block link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  raii.class.change_tracker.change_until_end_of_block
  raii.class.change_tracker.change_until_end_of_block)


#   test for test_functor_scope_exit
#     (Lib:raii), (Header:api_initializer), (Class:functor_scope_exit), (Test:functor_scope_exit)
#   
add_executable(raii.class.api_initializer.functor_scope_exit
  tests/raii/class.api_initializer.functor_scope_exit.cpp
)

# custom <test_functor_scope_exit test additions>
# end <test_functor_scope_exit test additions>

target_link_libraries(raii.class.api_initializer.functor_scope_exit
# custom <catch test_functor_scope_exit link requirements>
# end <catch test_functor_scope_exit link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  raii.class.api_initializer.functor_scope_exit
  raii.class.api_initializer.functor_scope_exit)


#   test for test_block_timer
#     (Lib:performance), (Header:block_timers), (Class:block_timer), (Test:block_timer)
#   
add_executable(performance.class.block_timers.block_timer
  tests/performance/class.block_timers.block_timer.cpp
)

# custom <test_block_timer test additions>
# end <test_block_timer test additions>

target_link_libraries(performance.class.block_timers.block_timer
# custom <catch test_block_timer link requirements>
# end <catch test_block_timer link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  performance.class.block_timers.block_timer
  performance.class.block_timers.block_timer)


#   test for test_block_timer_logger
#     (Lib:performance), (Header:block_timers), (Class:block_timer_logger), (Test:block_timer_logger)
#   
add_executable(performance.class.block_timers.block_timer_logger
  tests/performance/class.block_timers.block_timer_logger.cpp
)

# custom <test_block_timer_logger test additions>
# end <test_block_timer_logger test additions>

target_link_libraries(performance.class.block_timers.block_timer_logger
# custom <catch test_block_timer_logger link requirements>
  ${Boost_REGEX_LIBRARY}  
# end <catch test_block_timer_logger link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  performance.class.block_timers.block_timer_logger
  performance.class.block_timers.block_timer_logger)


#   test for test_block_rusage
#     (Lib:performance), (Header:block_rusage), (Class:block_rusage), (Test:block_rusage)
#   
add_executable(performance.class.block_rusage.block_rusage
  tests/performance/class.block_rusage.block_rusage.cpp
)

# custom <test_block_rusage test additions>
# end <test_block_rusage test additions>

target_link_libraries(performance.class.block_rusage.block_rusage
# custom <catch test_block_rusage link requirements>
# end <catch test_block_rusage link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  performance.class.block_rusage.block_rusage
  performance.class.block_rusage.block_rusage)


#   test for test_h5_random_access_store
#     (Lib:h5_utils), (Header:h5_random_access_store), (Class:h5_random_access_store), (Test:h5_random_access_store)
#   
add_executable(h5_utils.class.h5_random_access_store.h5_random_access_store
  tests/h5_utils/class.h5_random_access_store.h5_random_access_store.cpp
)

# custom <test_h5_random_access_store test additions>
# end <test_h5_random_access_store test additions>

target_link_libraries(h5_utils.class.h5_random_access_store.h5_random_access_store
# custom <catch test_h5_random_access_store link requirements>

  -lhdf5_hl_cpp
  -lhdf5_hl
  -lhdf5_cpp
  -lhdf5
  -lszip
  -lz
  -ldl
  ${Boost_FILESYSTEM_LIBRARY}
  
# end <catch test_h5_random_access_store link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  h5_utils.class.h5_random_access_store.h5_random_access_store
  h5_utils.class.h5_random_access_store.h5_random_access_store)


#   test for test_mongo
#     (Lib:mongo), (Test:mongo)
#   
add_executable(mongo.lib.mongo
  tests/mongo/lib.mongo.cpp
)

# custom <test_mongo test additions>
# end <test_mongo test additions>

target_link_libraries(mongo.lib.mongo
# custom <catch test_mongo link requirements>
# end <catch test_mongo link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  mongo.lib.mongo
  mongo.lib.mongo)


######################################################################
# Benchmark directives
######################################################################
add_executable(bench_make_exception
  benchmarks/app/make_exception/make_exception.cpp
)

# custom <make_exception bench additions>
# end <make_exception bench additions>

target_link_libraries(bench_make_exception
# custom <benchmark makeException link requirements>
# end <benchmark makeException link requirements>
  benchmark
  pthread
)

