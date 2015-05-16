cmake_minimum_required (VERSION 2.8)

include(CheckCXXCompilerFlag)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

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
# end <boost lib components>
)

# custom <misc section>

add_definitions(-DOTL_ODBC_UNIX)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

# end <misc section>


######################################################################
# Add additional link directories
######################################################################
link_directories(
# custom <link directories>
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
  ~/install/cpp/include
  ~/install/cpp/include/catch  
# end <include directories>

)

######################################################################
# Application build directives
######################################################################
add_executable(date_time_converter
  app/date_time_converter/date_time_converter.cpp
)

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

#   test for test_umask_scoped_set
#     (Lib:linux_specific), (Header:umask_scoped_set), (Test:umask_scoped_set)
#   
add_executable(header.umask_scoped_set
  tests/linux_specific/header.umask_scoped_set.cpp
)

target_link_libraries(header.umask_scoped_set
# custom <catch test_umask_scoped_set link requirements>
# end <catch test_umask_scoped_set link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
)

add_test(
  header.umask_scoped_set
  header.umask_scoped_set)


#   test for test_cpu_info
#     (Lib:linux_specific), (Header:cpu_info), (Class:cpu_info), (Test:cpu_info)
#   
add_executable(class.cpu_info.cpu_info
  tests/linux_specific/class.cpu_info.cpu_info.cpp
)

target_link_libraries(class.cpu_info.cpu_info
# custom <catch test_cpu_info link requirements>
  ${Boost_REGEX_LIBRARY}
# end <catch test_cpu_info link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
)

add_test(
  class.cpu_info.cpu_info
  class.cpu_info.cpu_info)


#   test for test_fixed_size_char_array
#     (Lib:utils), (Header:fixed_size_char_array), (Test:fixed_size_char_array)
#   
add_executable(header.fixed_size_char_array
  tests/utils/header.fixed_size_char_array.cpp
)

target_link_libraries(header.fixed_size_char_array
# custom <catch test_fixed_size_char_array link requirements>
# end <catch test_fixed_size_char_array link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
)

add_test(
  header.fixed_size_char_array
  header.fixed_size_char_array)


#   test for test_change_tracker_next_value
#     (Lib:raii), (Header:change_tracker), (Class:change_tracker_next_value), (Test:change_tracker_next_value)
#   
add_executable(class.change_tracker.change_tracker_next_value
  tests/raii/class.change_tracker.change_tracker_next_value.cpp
)

target_link_libraries(class.change_tracker.change_tracker_next_value
# custom <catch test_change_tracker_next_value link requirements>
# end <catch test_change_tracker_next_value link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
)

add_test(
  class.change_tracker.change_tracker_next_value
  class.change_tracker.change_tracker_next_value)


#   test for test_change_until_end_of_block
#     (Lib:raii), (Header:change_tracker), (Class:change_until_end_of_block), (Test:change_until_end_of_block)
#   
add_executable(class.change_tracker.change_until_end_of_block
  tests/raii/class.change_tracker.change_until_end_of_block.cpp
)

target_link_libraries(class.change_tracker.change_until_end_of_block
# custom <catch test_change_until_end_of_block link requirements>
# end <catch test_change_until_end_of_block link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
)

add_test(
  class.change_tracker.change_until_end_of_block
  class.change_tracker.change_until_end_of_block)


#   test for test_functor_scope_exit
#     (Lib:raii), (Header:api_initializer), (Class:functor_scope_exit), (Test:functor_scope_exit)
#   
add_executable(class.api_initializer.functor_scope_exit
  tests/raii/class.api_initializer.functor_scope_exit.cpp
)

target_link_libraries(class.api_initializer.functor_scope_exit
# custom <catch test_functor_scope_exit link requirements>
# end <catch test_functor_scope_exit link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
)

add_test(
  class.api_initializer.functor_scope_exit
  class.api_initializer.functor_scope_exit)


#   test for test_code_packages
#     (Lib:code_metrics), (Header:code_packages), (Class:code_packages), (Test:code_packages)
#   
add_executable(class.code_packages.code_packages
  tests/code_metrics/class.code_packages.code_packages.cpp
)

target_link_libraries(class.code_packages.code_packages
# custom <catch test_code_packages link requirements>
# end <catch test_code_packages link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
)

add_test(
  class.code_packages.code_packages
  class.code_packages.code_packages)


#   test for test_code_locations
#     (Lib:code_metrics), (Header:code_locations), (Class:code_locations), (Test:code_locations)
#   
add_executable(class.code_locations.code_locations
  tests/code_metrics/class.code_locations.code_locations.cpp
)

target_link_libraries(class.code_locations.code_locations
# custom <catch test_code_locations link requirements>
# end <catch test_code_locations link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
)

add_test(
  class.code_locations.code_locations
  class.code_locations.code_locations)


#   test for test_code_tick_timings
#     (Lib:code_metrics), (Header:code_tick_timings), (Class:code_tick_timings), (Test:code_tick_timings)
#   
add_executable(class.code_tick_timings.code_tick_timings
  tests/code_metrics/class.code_tick_timings.code_tick_timings.cpp
)

target_link_libraries(class.code_tick_timings.code_tick_timings
# custom <catch test_code_tick_timings link requirements>
# end <catch test_code_tick_timings link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
)

add_test(
  class.code_tick_timings.code_tick_timings
  class.code_tick_timings.code_tick_timings)


#   test for test_rusage_delta
#     (Lib:code_metrics), (Header:rusage_delta), (Class:rusage_delta), (Test:rusage_delta)
#   
add_executable(class.rusage_delta.rusage_delta
  tests/code_metrics/class.rusage_delta.rusage_delta.cpp
)

target_link_libraries(class.rusage_delta.rusage_delta
# custom <catch test_rusage_delta link requirements>
# end <catch test_rusage_delta link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
)

add_test(
  class.rusage_delta.rusage_delta
  class.rusage_delta.rusage_delta)

