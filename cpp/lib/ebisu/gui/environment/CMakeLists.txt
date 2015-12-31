set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIE")

# Instruct CMake to run moc automatically when needed.

qt5_wrap_cpp(q-environment-moc ../../../../ebisu/gui/environment/q_environment.hpp)
add_library(gui_environment q_environment.cpp tree_path_model.cpp ${q-environment-moc})
target_include_directories(gui_environment PUBLIC ${Qt5Widgets_INCLUDE_DIRS})
target_compile_options(gui_environment PRIVATE "-fPIE")
install(TARGETS gui_environment ARCHIVE DESTINATION ${DESTDIR}/lib/static)
