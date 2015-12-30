set(CMAKE_VERBOSE_MAKEFILE ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
qt5_wrap_cpp(q-environment-moc ../../../../ebisu/gui/environment/q_environment.hpp)
add_library(gui_environment q_environment.cpp tree_path_model.cpp ${q-environment-moc})
target_include_directories(gui_environment PUBLIC ${Qt5Widgets_INCLUDE_DIRS})