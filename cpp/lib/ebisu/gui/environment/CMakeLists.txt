set(CMAKE_VERBOSE_MAKEFILE ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
add_library(gui_environment q_environment.cpp tree_path_model.cpp)
target_include_directories(gui_environment PUBLIC ${Qt5Widgets_INCLUDE_DIRS})