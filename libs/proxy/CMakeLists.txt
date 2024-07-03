cmake_minimum_required (VERSION 3.8)

project (
  "LunaProxy"
  VERSION 0.0.0
  LANGUAGES CXX
)

add_library(LunaProxy SHARED
    "version.cpp"
)

# disable optimizations
target_compile_options(LunaProxy PRIVATE -O0)

# set C++ standard to 2011
target_compile_features(LunaProxy PRIVATE cxx_std_11)

# output proxy as target dll
set_target_properties(LunaProxy PROPERTIES
    OUTPUT_NAME version
)
target_sources(LunaProxy PRIVATE version.def)