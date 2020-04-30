cmake_minimum_required(VERSION 2.8)
find_package (Threads)

# build the library sources from all sources, removing the test sources
file(GLOB lib_sources *.cpp)
foreach(source_file ${test_sources})
  list(REMOVE_ITEM lib_sources ${source_file})
endforeach()

# penum library
add_library(penum ${lib_sources})
