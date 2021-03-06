# Cpp Ebisu

[![Build Status](https://travis-ci.org/patefacio/cpp_ebisu.svg?branch=master)](https://travis-ci.org/patefacio/cpp_ebisu)

This is the C++ counterpart to
[*ebisu_cpp*](https://github.com/patefacio/ebisu_cpp). It is a small
collection of general purpose C++ code that may be used by code
generated by *ebisu_cpp* - (e.g. for streaming support). So this
repository serves a couple of purposes:

  - Provide example usage of generating code with *ebisu_cpp* (See: the [ebisu cpp scripts](codegen/bin/cpp_ebisu.ebisu_cpp.dart) )

  - Generate code that may be referenced by other code generated by *ebisu_cpp*

While [*ebisu*](https://github.com/patefacio/ebisu) is intended as a
general purpose code generation framework and the code generated by
[*ebisu_cpp*](https://github.com/patefacio/ebisu_cpp) is intended to
be cross platform, the C++ generation is more aligned with linux. 