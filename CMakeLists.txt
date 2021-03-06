cmake_minimum_required(VERSION 3.9)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum OS X deployment version")

project("lua-formatter" VERSION 1.3.0 LANGUAGES CXX)

option(BUILD_TESTS "set ON to build tests" ON)
option(COVERAGE "set ON to enable coverage" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

include(CheckIPOSupported)
check_ipo_supported(RESULT lto OUTPUT error)

if(lto)
  message(STATUS "IPO / LTO enabled")
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
  message(STATUS "IPO / LTO not supported: <${error}>")
endif()

# The code is modified from
# https://gitlab.kitware.com/cmake/community/-/wikis/doc/tutorials/How-To-Write-Platform-Checks
include(CheckIncludeFileCXX)
check_include_file_cxx("filesystem" HAVE_FILESYSTEM_H)
if(NOT HAVE_FILESYSTEM_H)
    message(WARNING "filesystem not found, use experimental/filesystem as fallback."
        " It's recommended to use a stable C++17 compliant compiler/libstdc++.")
endif()
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/ConfigCheck.h)

if(NOT CMAKE_BUILD_TYPE)
  message("set build type to Release.")
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

if ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") OR
    (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND
    ((CMAKE_SYSTEM_NAME STREQUAL "Linux") OR (CMAKE_CXX_COMPILER_VERSION LESS 9))))
  set(extra-libs "stdc++fs")
else()
  set(extra-libs "")
endif()

try_run(TEST_RUN_RESULT
  TEST_COMPILE_RESULT
  ${CMAKE_CURRENT_BINARY_DIR}/
  ${PROJECT_SOURCE_DIR}/test/cpp17/fs.cpp
  LINK_LIBRARIES ${extra-libs}
  OUTPUT_VARIABLE var)

message("${var}")

if(NOT "${TEST_COMPILE_RESULT}" OR (NOT "${TEST_RUN_RESULT}" EQUAL 0))
  message(FATAL_ERROR "Your compiler does not fully support the C++17 standard and libraries")
endif()

if( ${CMAKE_BUILD_TYPE} MATCHES "Debug")
  add_definitions(-DDEBUG)
endif()

include_directories(
  ${PROJECT_SOURCE_DIR}/generated/
  ${PROJECT_SOURCE_DIR}/third_party/
  ${PROJECT_SOURCE_DIR}/third_party/Catch2/single_include
  ${PROJECT_SOURCE_DIR}/third_party/yaml-cpp/include
  ${PROJECT_SOURCE_DIR}/third_party/antlr4/runtime/Cpp/runtime/src
  ${PROJECT_SOURCE_DIR}/src/
  )

set(src_dir
  ${PROJECT_SOURCE_DIR}/src/lua-format.cpp
  ${PROJECT_SOURCE_DIR}/src/Config.cpp
  ${PROJECT_SOURCE_DIR}/src/FormatVisitor.cpp
  ${PROJECT_SOURCE_DIR}/generated/LuaLexer.cpp
  ${PROJECT_SOURCE_DIR}/generated/LuaParser.cpp
  ${PROJECT_SOURCE_DIR}/generated/LuaVisitor.cpp
  ${PROJECT_SOURCE_DIR}/generated/LuaBaseVisitor.cpp
  )

file(GLOB_RECURSE antlr4-cpp-src
  ${PROJECT_SOURCE_DIR}/third_party/antlr4/runtime/Cpp/runtime/src/*.cpp
  )

file(GLOB_RECURSE yaml-cpp-src
  ${PROJECT_SOURCE_DIR}/third_party/yaml-cpp/src/*.cpp
  )

add_library (antlr4-cpp-runtime ${antlr4-cpp-src})
add_library (yaml-cpp ${yaml-cpp-src})

add_executable(ivan-format ${src_dir} src/main.cpp)

if(WIN32)
  target_compile_definitions(antlr4-cpp-runtime PRIVATE ANTLR4CPP_EXPORTS)
  target_compile_definitions(yaml-cpp PRIVATE YAMLCPP_EXPORTS)
endif()

set_target_properties(ivan-format PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(ivan-format yaml-cpp antlr4-cpp-runtime ${extra-libs})

install(TARGETS ivan-format
  RUNTIME DESTINATION bin
  )

