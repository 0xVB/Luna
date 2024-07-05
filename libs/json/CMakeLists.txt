cmake_minimum_required (VERSION 3.8)

project(
    json
    VERSION 1.0
    DESCRIPTION "JSON library"
    LANGUAGES CXX
)

target_include_directories(minhook PRIVATE "include/")

add_library(nlohmann_json INTERFACE
    "json.cpp" "include/json.hpp"
)