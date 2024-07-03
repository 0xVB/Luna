cmake_minimum_required (VERSION 3.8)

project (
  "kiero"
  VERSION 0.0.0
  LANGUAGES CXX
)

add_library(kiero STATIC
    "kiero.cpp" "kiero.h"
)
target_include_directories(kiero PUBLIC .)

add_subdirectory("minhook")
target_link_libraries(kiero PUBLIC minhook)