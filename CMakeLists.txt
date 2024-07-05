cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (
  "Luna"
  VERSION 0.0.0
  LANGUAGES CXX
)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "include/*.h" "include/*.hpp")

add_library (Luna SHARED
  ${SRC_FILES} ${HEADER_FILES}
 "src/Lunacy/Image.cpp" "src/Luna/Luna.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Luna PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(Luna PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(libs/minhook)
target_link_libraries(Luna PRIVATE minhook)

# toggle off some of the Luau build options
set(LUAU_BUILD_CLI OFF CACHE BOOL "")
set(LUAU_BUILD_TESTS OFF CACHE BOOL "")
set(LUAU_BUILD_WEB OFF CACHE BOOL "")
add_subdirectory(libs/luau)

target_link_libraries(Luna PRIVATE Luau.Compiler)
target_link_libraries(Luna PRIVATE Luau.Ast)
target_link_libraries(Luna PRIVATE isocline)
target_link_libraries(Luna PRIVATE Luau.VM)

add_subdirectory(libs/proxy)

add_definitions(-DLUNA_VERSION="${PROJECT_VERSION}")

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
   target_compile_options(Luna PRIVATE /Zi)

   # Tell linker to include symbol data
   target_link_options(Luna PUBLIC "/DEBUG")

    # Set file name & location
    set_target_properties(Luna PROPERTIES 
        COMPILE_PDB_NAME Luna
        COMPILE_PDB_OUTPUT_DIR ${CMAKE_BINARY_DIR}
    )
endif()

# target_link_libraries(Luna PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Include/Lua/lua54.lib)