cmake_minimum_required (VERSION 3.0)

include(CheckCXXCompilerFlag)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

######################################################################
# Find boost and include desired components
######################################################################
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.56.0 COMPONENTS program_options system thread
# custom <boost lib components>
  date_time
  regex
# end <boost lib components>
)

# custom <misc section>

add_definitions(-DOTL_ODBC_UNIX)

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
# test for test_fixed_size_char_array
add_executable(test_fixed_size_char_array
  tests/fcs/utils/test_fixed_size_char_array.cpp
)

target_link_libraries(test_fixed_size_char_array
# custom <test_fixed_size_char_array link requirements>
# end <test_fixed_size_char_array link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
)

add_test(test_fixed_size_char_array test_fixed_size_char_array)

# test for test_random
add_executable(test_random
  tests/fcs/utils/streamers/test_random.cpp
)

target_link_libraries(test_random
# custom <test_random link requirements>
# end <test_random link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
)

add_test(test_random test_random)

# test for test_change_tracker
add_executable(test_change_tracker
  tests/fcs/raii/test_change_tracker.cpp
)

target_link_libraries(test_change_tracker
# custom <test_change_tracker link requirements>
# end <test_change_tracker link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
)

add_test(test_change_tracker test_change_tracker)

# test for test_api_initializer
add_executable(test_api_initializer
  tests/fcs/raii/test_api_initializer.cpp
)

target_link_libraries(test_api_initializer
# custom <test_api_initializer link requirements>
# end <test_api_initializer link requirements>
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
)

add_test(test_api_initializer test_api_initializer)
