cmake_minimum_required (VERSION 2.8)
include(CheckCXXCompilerFlag)
# custom <includes>
# end <includes>
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -DDEBUG")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# custom <set_statements>
# end <set_statements>
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
# custom <boost_support>
# end <boost_support>

include_directories(
  ${CMAKE_CURRENT_LIST_DIR}
  ${Boost_INCLUDE_DIRS}
# custom <include directories>

  /usr/local/HDF_Group/HDF5/1.8.16/include
  ../install/catch/include
  ../install/spdlog/include
  /opt/mongo-client-install/include
  .
# end <include directories>
)

link_directories(

# custom <link directories>

/usr/local/HDF_Group/HDF5/1.8.16/lib
/opt/mongo-client-install/lib

# end <link directories>
)
# custom <misc section>

add_definitions(-DOTL_ODBC_UNIX)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets)

message(status " Found qt include dirs: " ${Qt5Widgets_INCLUDE_DIRS})
message(status " Found qt libs: " ${Qt5Widgets_LIBRARIES})

##### Add --save-temps to see assembly
##### Add -Winline to see what is not inlined (gcc)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLIB_INIT_LOGGING")

# end <misc section>
enable_testing()
add_subdirectory(lib/ebisu/gui/environment)
add_library(lib_linux_specific INTERFACE)
target_sources(lib_linux_specific INTERFACE
 ebisu/linux_specific/application_signal_handler.hpp
 ebisu/linux_specific/umask_scoped_set.hpp
 ebisu/linux_specific/linux_exceptions.hpp
 ebisu/linux_specific/cpu_info.hpp
 ebisu/linux_specific/linux_specific_logging.hpp
)
add_library(lib_utils INTERFACE)
target_sources(lib_utils INTERFACE
 ebisu/utils/block_indenter.hpp
 ebisu/utils/buffer.hpp
 ebisu/utils/fixed_size_char_array.hpp
 ebisu/utils/version_control_commit.hpp
 ebisu/utils/histogram.hpp
)
add_library(lib_exception INTERFACE)
target_sources(lib_exception INTERFACE
 ebisu/utils/exception/make_exception.hpp
)
add_library(lib_streamers INTERFACE)
target_sources(lib_streamers INTERFACE
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
 ebisu/utils/streamers/printer.hpp
)
add_library(lib_raii INTERFACE)
target_sources(lib_raii INTERFACE
 ebisu/raii/change_tracker.hpp
 ebisu/raii/api_initializer.hpp
 ebisu/raii/raii_common.hpp
 ebisu/raii/raii_logging.hpp
 ebisu/raii/raii_initialization.hpp
)
add_library(lib_orm INTERFACE)
target_sources(lib_orm INTERFACE
 ebisu/orm/orm_to_string_table.hpp
 ebisu/orm/otl_utils.hpp
 ebisu/orm/orm_common.hpp
)
add_library(lib_timestamp INTERFACE)
target_sources(lib_timestamp INTERFACE
 ebisu/timestamp/timestamp.hpp
 ebisu/timestamp/cereal.hpp
)
add_library(lib_conversion INTERFACE)
target_sources(lib_conversion INTERFACE
 ebisu/timestamp/conversion.hpp
)
add_library(lib_performance INTERFACE)
target_sources(lib_performance INTERFACE
 ebisu/performance/block_timers.hpp
 ebisu/performance/block_rusage.hpp
 ebisu/performance/performance_common.hpp
 ebisu/performance/performance_logging.hpp
 ebisu/performance/performance_initialization.hpp
)
add_library(lib_h5_utils INTERFACE)
target_sources(lib_h5_utils INTERFACE
 ebisu/h5/utils/h5_random_access_store.hpp
 ebisu/h5/utils/h5_utils_logging.hpp
)
add_library(lib_mongo INTERFACE)
target_sources(lib_mongo INTERFACE
 ebisu/mongo/connection_registry.hpp
 ebisu/mongo/mongo_ini.hpp
 ebisu/mongo/mongo_logging.hpp
)
add_library(lib_logger INTERFACE)
target_sources(lib_logger INTERFACE
 ebisu/logger/logger.hpp
)
add_library(lib_environment INTERFACE)
target_sources(lib_environment INTERFACE
 ebisu/environment/environment.hpp
)
add_library(lib_benchmark_make_exception INTERFACE)
target_sources(lib_benchmark_make_exception INTERFACE
 benchmarks/bench/make_exception/benchmark_make_exception.hpp
)
install(FILES ebisu/linux_specific/application_signal_handler.hpp DESTINATION ${DESTDIR}/include/ebisu/linux_specific)
install(FILES ebisu/linux_specific/umask_scoped_set.hpp DESTINATION ${DESTDIR}/include/ebisu/linux_specific)
install(FILES ebisu/linux_specific/linux_exceptions.hpp DESTINATION ${DESTDIR}/include/ebisu/linux_specific)
install(FILES ebisu/linux_specific/cpu_info.hpp DESTINATION ${DESTDIR}/include/ebisu/linux_specific)
install(FILES ebisu/linux_specific/linux_specific_logging.hpp DESTINATION ${DESTDIR}/include/ebisu/linux_specific)
install(FILES ebisu/utils/block_indenter.hpp DESTINATION ${DESTDIR}/include/ebisu/utils)
install(FILES ebisu/utils/buffer.hpp DESTINATION ${DESTDIR}/include/ebisu/utils)
install(FILES ebisu/utils/fixed_size_char_array.hpp DESTINATION ${DESTDIR}/include/ebisu/utils)
install(FILES ebisu/utils/version_control_commit.hpp DESTINATION ${DESTDIR}/include/ebisu/utils)
install(FILES ebisu/utils/histogram.hpp DESTINATION ${DESTDIR}/include/ebisu/utils)
install(FILES ebisu/utils/exception/make_exception.hpp DESTINATION ${DESTDIR}/include/ebisu/utils/exception)
install(FILES ebisu/utils/streamers/containers.hpp DESTINATION ${DESTDIR}/include/ebisu/utils/streamers)
install(FILES ebisu/utils/streamers/streamers.hpp DESTINATION ${DESTDIR}/include/ebisu/utils/streamers)
install(FILES ebisu/utils/streamers/random.hpp DESTINATION ${DESTDIR}/include/ebisu/utils/streamers)
install(FILES ebisu/utils/streamers/table.hpp DESTINATION ${DESTDIR}/include/ebisu/utils/streamers)
install(FILES ebisu/utils/streamers/vector.hpp DESTINATION ${DESTDIR}/include/ebisu/utils/streamers)
install(FILES ebisu/utils/streamers/set.hpp DESTINATION ${DESTDIR}/include/ebisu/utils/streamers)
install(FILES ebisu/utils/streamers/map.hpp DESTINATION ${DESTDIR}/include/ebisu/utils/streamers)
install(FILES ebisu/utils/streamers/list.hpp DESTINATION ${DESTDIR}/include/ebisu/utils/streamers)
install(FILES ebisu/utils/streamers/array.hpp DESTINATION ${DESTDIR}/include/ebisu/utils/streamers)
install(FILES ebisu/utils/streamers/deque.hpp DESTINATION ${DESTDIR}/include/ebisu/utils/streamers)
install(FILES ebisu/utils/streamers/ptr_map.hpp DESTINATION ${DESTDIR}/include/ebisu/utils/streamers)
install(FILES ebisu/utils/streamers/ptr_set.hpp DESTINATION ${DESTDIR}/include/ebisu/utils/streamers)
install(FILES ebisu/utils/streamers/ptr_vector.hpp DESTINATION ${DESTDIR}/include/ebisu/utils/streamers)
install(FILES ebisu/utils/streamers/printer.hpp DESTINATION ${DESTDIR}/include/ebisu/utils/streamers)
install(FILES ebisu/raii/change_tracker.hpp DESTINATION ${DESTDIR}/include/ebisu/raii)
install(FILES ebisu/raii/api_initializer.hpp DESTINATION ${DESTDIR}/include/ebisu/raii)
install(FILES ebisu/raii/raii_common.hpp DESTINATION ${DESTDIR}/include/ebisu/raii)
install(FILES ebisu/raii/raii_logging.hpp DESTINATION ${DESTDIR}/include/ebisu/raii)
install(FILES ebisu/raii/raii_initialization.hpp DESTINATION ${DESTDIR}/include/ebisu/raii)
install(FILES ebisu/orm/orm_to_string_table.hpp DESTINATION ${DESTDIR}/include/ebisu/orm)
install(FILES ebisu/orm/otl_utils.hpp DESTINATION ${DESTDIR}/include/ebisu/orm)
install(FILES ebisu/orm/orm_common.hpp DESTINATION ${DESTDIR}/include/ebisu/orm)
install(FILES ebisu/timestamp/timestamp.hpp DESTINATION ${DESTDIR}/include/ebisu/timestamp)
install(FILES ebisu/timestamp/cereal.hpp DESTINATION ${DESTDIR}/include/ebisu/timestamp)
install(FILES ebisu/timestamp/conversion.hpp DESTINATION ${DESTDIR}/include/ebisu/timestamp)
install(FILES ebisu/performance/block_timers.hpp DESTINATION ${DESTDIR}/include/ebisu/performance)
install(FILES ebisu/performance/block_rusage.hpp DESTINATION ${DESTDIR}/include/ebisu/performance)
install(FILES ebisu/performance/performance_common.hpp DESTINATION ${DESTDIR}/include/ebisu/performance)
install(FILES ebisu/performance/performance_logging.hpp DESTINATION ${DESTDIR}/include/ebisu/performance)
install(FILES ebisu/performance/performance_initialization.hpp DESTINATION ${DESTDIR}/include/ebisu/performance)
install(FILES ebisu/h5/utils/h5_random_access_store.hpp DESTINATION ${DESTDIR}/include/ebisu/h5/utils)
install(FILES ebisu/h5/utils/h5_utils_logging.hpp DESTINATION ${DESTDIR}/include/ebisu/h5/utils)
install(FILES ebisu/mongo/connection_registry.hpp DESTINATION ${DESTDIR}/include/ebisu/mongo)
install(FILES ebisu/mongo/mongo_ini.hpp DESTINATION ${DESTDIR}/include/ebisu/mongo)
install(FILES ebisu/mongo/mongo_logging.hpp DESTINATION ${DESTDIR}/include/ebisu/mongo)
install(FILES ebisu/logger/logger.hpp DESTINATION ${DESTDIR}/include/ebisu/logger)
install(FILES ebisu/environment/environment.hpp DESTINATION ${DESTDIR}/include/ebisu/environment)
install(FILES ebisu/gui/environment/q_environment.hpp DESTINATION ${DESTDIR}/include/ebisu/gui/environment)
install(FILES benchmarks/bench/make_exception/benchmark_make_exception.hpp DESTINATION ${DESTDIR}/include/benchmarks/bench/make_exception)
# custom <lib_public_headers>
# end <lib_public_headers>
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
add_executable(h5ds2csv
  app/h5ds2csv/h5ds2csv.cpp
)

# custom <h5ds2csv exe additions>
# end <h5ds2csv exe additions>

target_link_libraries(h5ds2csv
# custom <h5ds2csv libs>
  -pthread
# end <h5ds2csv libs>
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
)
add_executable(environment
  app/environment/environment.cpp
)

# custom <environment exe additions>

set_source_files_properties(app/environment/environment.cpp PROPERTIES COMPILE_FLAGS -fPIE)

target_include_directories(environment PUBLIC ${Qt5Widgets_INCLUDE_DIRS})

# end <environment exe additions>

target_link_libraries(environment
# custom <environment libs>
  gui_environment
  Qt5::Widgets
  ${Boost_DATE_TIME_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}  
  ${Boost_REGEX_LIBRARY}
# end <environment libs>
  ${Boost_PROGRAM_OPTIONS_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
)

#   test for test_application_signal_handler
#     (Lib:linux_specific), (Header:application_signal_handler), (Test:application_signal_handler)
#   
add_executable(test.linux_specific.header.application_signal_handler
  tests/linux_specific/header.application_signal_handler.cpp
)

# custom <test_application_signal_handler test additions>
# end <test_application_signal_handler test additions>

target_link_libraries(test.linux_specific.header.application_signal_handler
# custom <catch test_application_signal_handler link requirements>
    -pthread
# end <catch test_application_signal_handler link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  test.linux_specific.header.application_signal_handler
  test.linux_specific.header.application_signal_handler)

install(TARGETS test.linux_specific.header.application_signal_handler RUNTIME DESTINATION ${DESTDIR}/bin)

#   test for test_umask_scoped_set
#     (Lib:linux_specific), (Header:umask_scoped_set), (Test:umask_scoped_set)
#   
add_executable(test.linux_specific.header.umask_scoped_set
  tests/linux_specific/header.umask_scoped_set.cpp
)

# custom <test_umask_scoped_set test additions>
# end <test_umask_scoped_set test additions>

target_link_libraries(test.linux_specific.header.umask_scoped_set
# custom <catch test_umask_scoped_set link requirements>
# end <catch test_umask_scoped_set link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  test.linux_specific.header.umask_scoped_set
  test.linux_specific.header.umask_scoped_set)

install(TARGETS test.linux_specific.header.umask_scoped_set RUNTIME DESTINATION ${DESTDIR}/bin)

#   test for test_cpu_info
#     (Lib:linux_specific), (Header:cpu_info), (Class:cpu_info), (Test:cpu_info)
#   
add_executable(test.linux_specific.class.cpu_info.cpu_info
  tests/linux_specific/class.cpu_info.cpu_info.cpp
)

# custom <test_cpu_info test additions>
# end <test_cpu_info test additions>

target_link_libraries(test.linux_specific.class.cpu_info.cpu_info
# custom <catch test_cpu_info link requirements>
  ${Boost_REGEX_LIBRARY}
# end <catch test_cpu_info link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  test.linux_specific.class.cpu_info.cpu_info
  test.linux_specific.class.cpu_info.cpu_info)

install(TARGETS test.linux_specific.class.cpu_info.cpu_info RUNTIME DESTINATION ${DESTDIR}/bin)

#   test for test_buffer
#     (Lib:utils), (Header:buffer), (Test:buffer)
#   
add_executable(test.utils.header.buffer
  tests/utils/header.buffer.cpp
)

# custom <test_buffer test additions>
# end <test_buffer test additions>

target_link_libraries(test.utils.header.buffer
# custom <catch test_buffer link requirements>
# end <catch test_buffer link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  test.utils.header.buffer
  test.utils.header.buffer)

install(TARGETS test.utils.header.buffer RUNTIME DESTINATION ${DESTDIR}/bin)

#   test for test_fixed_size_char_array
#     (Lib:utils), (Header:fixed_size_char_array), (Test:fixed_size_char_array)
#   
add_executable(test.utils.header.fixed_size_char_array
  tests/utils/header.fixed_size_char_array.cpp
)

# custom <test_fixed_size_char_array test additions>
# end <test_fixed_size_char_array test additions>

target_link_libraries(test.utils.header.fixed_size_char_array
# custom <catch test_fixed_size_char_array link requirements>
# end <catch test_fixed_size_char_array link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  test.utils.header.fixed_size_char_array
  test.utils.header.fixed_size_char_array)

install(TARGETS test.utils.header.fixed_size_char_array RUNTIME DESTINATION ${DESTDIR}/bin)

#   test for test_change_tracker_next_value
#     (Lib:raii), (Header:change_tracker), (Class:change_tracker_next_value), (Test:change_tracker_next_value)
#   
add_executable(test.raii.class.change_tracker.change_tracker_next_value
  tests/raii/class.change_tracker.change_tracker_next_value.cpp
)

# custom <test_change_tracker_next_value test additions>
# end <test_change_tracker_next_value test additions>

target_link_libraries(test.raii.class.change_tracker.change_tracker_next_value
# custom <catch test_change_tracker_next_value link requirements>
# end <catch test_change_tracker_next_value link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  test.raii.class.change_tracker.change_tracker_next_value
  test.raii.class.change_tracker.change_tracker_next_value)

install(TARGETS test.raii.class.change_tracker.change_tracker_next_value RUNTIME DESTINATION ${DESTDIR}/bin)

#   test for test_change_until_end_of_block
#     (Lib:raii), (Header:change_tracker), (Class:change_until_end_of_block), (Test:change_until_end_of_block)
#   
add_executable(test.raii.class.change_tracker.change_until_end_of_block
  tests/raii/class.change_tracker.change_until_end_of_block.cpp
)

# custom <test_change_until_end_of_block test additions>
# end <test_change_until_end_of_block test additions>

target_link_libraries(test.raii.class.change_tracker.change_until_end_of_block
# custom <catch test_change_until_end_of_block link requirements>
# end <catch test_change_until_end_of_block link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  test.raii.class.change_tracker.change_until_end_of_block
  test.raii.class.change_tracker.change_until_end_of_block)

install(TARGETS test.raii.class.change_tracker.change_until_end_of_block RUNTIME DESTINATION ${DESTDIR}/bin)

#   test for test_functor_scope_exit
#     (Lib:raii), (Header:api_initializer), (Class:functor_scope_exit), (Test:functor_scope_exit)
#   
add_executable(test.raii.class.api_initializer.functor_scope_exit
  tests/raii/class.api_initializer.functor_scope_exit.cpp
)

# custom <test_functor_scope_exit test additions>
# end <test_functor_scope_exit test additions>

target_link_libraries(test.raii.class.api_initializer.functor_scope_exit
# custom <catch test_functor_scope_exit link requirements>
# end <catch test_functor_scope_exit link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  test.raii.class.api_initializer.functor_scope_exit
  test.raii.class.api_initializer.functor_scope_exit)

install(TARGETS test.raii.class.api_initializer.functor_scope_exit RUNTIME DESTINATION ${DESTDIR}/bin)

#   test for test_block_timer
#     (Lib:performance), (Header:block_timers), (Class:block_timer), (Test:block_timer)
#   
add_executable(test.performance.class.block_timers.block_timer
  tests/performance/class.block_timers.block_timer.cpp
)

# custom <test_block_timer test additions>
# end <test_block_timer test additions>

target_link_libraries(test.performance.class.block_timers.block_timer
# custom <catch test_block_timer link requirements>
# end <catch test_block_timer link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  test.performance.class.block_timers.block_timer
  test.performance.class.block_timers.block_timer)

install(TARGETS test.performance.class.block_timers.block_timer RUNTIME DESTINATION ${DESTDIR}/bin)

#   test for test_block_timer_logger
#     (Lib:performance), (Header:block_timers), (Class:block_timer_logger), (Test:block_timer_logger)
#   
add_executable(test.performance.class.block_timers.block_timer_logger
  tests/performance/class.block_timers.block_timer_logger.cpp
)

# custom <test_block_timer_logger test additions>
# end <test_block_timer_logger test additions>

target_link_libraries(test.performance.class.block_timers.block_timer_logger
# custom <catch test_block_timer_logger link requirements>
  ${Boost_REGEX_LIBRARY}  
# end <catch test_block_timer_logger link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  test.performance.class.block_timers.block_timer_logger
  test.performance.class.block_timers.block_timer_logger)

install(TARGETS test.performance.class.block_timers.block_timer_logger RUNTIME DESTINATION ${DESTDIR}/bin)

#   test for test_block_rusage
#     (Lib:performance), (Header:block_rusage), (Class:block_rusage), (Test:block_rusage)
#   
add_executable(test.performance.class.block_rusage.block_rusage
  tests/performance/class.block_rusage.block_rusage.cpp
)

# custom <test_block_rusage test additions>
# end <test_block_rusage test additions>

target_link_libraries(test.performance.class.block_rusage.block_rusage
# custom <catch test_block_rusage link requirements>
# end <catch test_block_rusage link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  test.performance.class.block_rusage.block_rusage
  test.performance.class.block_rusage.block_rusage)

install(TARGETS test.performance.class.block_rusage.block_rusage RUNTIME DESTINATION ${DESTDIR}/bin)

#   test for test_h5_random_access_store
#     (Lib:h5_utils), (Header:h5_random_access_store), (Class:h5_random_access_store), (Test:h5_random_access_store)
#   
add_executable(test.h5_utils.class.h5_random_access_store.h5_random_access_store
  tests/h5_utils/class.h5_random_access_store.h5_random_access_store.cpp
)

# custom <test_h5_random_access_store test additions>
# end <test_h5_random_access_store test additions>

target_link_libraries(test.h5_utils.class.h5_random_access_store.h5_random_access_store
# custom <catch test_h5_random_access_store link requirements>

  -lhdf5_hl_cpp-static
  -lhdf5_hl-static
  -lhdf5_cpp-static
  -lhdf5-static
  -lszip-static
  -lz
  -ldl
  ${Boost_FILESYSTEM_LIBRARY}
  
# end <catch test_h5_random_access_store link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  test.h5_utils.class.h5_random_access_store.h5_random_access_store
  test.h5_utils.class.h5_random_access_store.h5_random_access_store)

install(TARGETS test.h5_utils.class.h5_random_access_store.h5_random_access_store RUNTIME DESTINATION ${DESTDIR}/bin)

#   test for test_mongo
#     (Lib:mongo), (Test:mongo)
#   
add_executable(test.mongo.lib.mongo
  tests/mongo/lib.mongo.cpp
)

# custom <test_mongo test additions>
# end <test_mongo test additions>

target_link_libraries(test.mongo.lib.mongo
# custom <catch test_mongo link requirements>
# end <catch test_mongo link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  test.mongo.lib.mongo
  test.mongo.lib.mongo)

install(TARGETS test.mongo.lib.mongo RUNTIME DESTINATION ${DESTDIR}/bin)

#   test for test_logger
#     (Lib:logger), (Header:logger), (Test:logger)
#   
add_executable(test.logger.header.logger
  tests/logger/header.logger.cpp
)

# custom <test_logger test additions>
# end <test_logger test additions>

target_link_libraries(test.logger.header.logger
# custom <catch test_logger link requirements>
# end <catch test_logger link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  test.logger.header.logger
  test.logger.header.logger)

install(TARGETS test.logger.header.logger RUNTIME DESTINATION ${DESTDIR}/bin)

#   test for test_environment
#     (Lib:environment), (Header:environment), (Test:environment)
#   
add_executable(test.environment.header.environment
  tests/environment/header.environment.cpp
)

# custom <test_environment test additions>
# end <test_environment test additions>

target_link_libraries(test.environment.header.environment
  # custom <catch test_environment link requirements>
  ${Boost_REGEX_LIBRARY}  
# end <catch test_environment link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  pthread
)

add_test(
  test.environment.header.environment
  test.environment.header.environment)

install(TARGETS test.environment.header.environment RUNTIME DESTINATION ${DESTDIR}/bin)
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

install(TARGETS bench_make_exception RUNTIME DESTINATION ${DESTDIR}/bin)
