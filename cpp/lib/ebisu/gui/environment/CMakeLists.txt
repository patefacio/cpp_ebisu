set(CMAKE_VERBOSE_MAKEFILE ON)
# custom <set_statements>
# end <set_statements>

qt5_wrap_cpp(q-environment-moc ../../../../ebisu/gui/environment/q_environment.hpp)

add_library(gui_environment
  tree_path_model.cc
  q_environment.cc
  ${q-environment-moc}
)

target_include_directories(gui_environment PUBLIC ${Qt5Widgets_INCLUDE_DIRS})
# custom <target_include_directories>
# end <target_include_directories>

target_compile_options(gui_environment PRIVATE "-fPIE")
# custom <target_compile_options>
# end <target_compile_options>

install(TARGETS gui_environment ARCHIVE DESTINATION ${DESTDIR}/lib/static)

