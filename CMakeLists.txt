## Konfiguration des Buildsystems CMake ##




# Minimale Version des Buildsystems
cmake_minimum_required(VERSION 3.14)
# Name des Projekts
project(VierGewinnt)

## Optionen ##

# Setzte verwendeten C++-Standard auf C++17
set(CMAKE_CXX_STANDARD 17)

# Prüfe ob Heapspeicher gefunden wird,
# der nicht freigegeben wurde
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

# Füge selbsgeschriebene Includes hinzu
include_directories(include)
# Füge externe Includes hinzu
#include_directories(external)


#find_package(pybind11 REQUIRED)

## Baue Programme ##

# Baue das Programm 'demo1' aus den genannten Quelldateien
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(demo1
  examples/main.cpp
  ${SRC_FILES}
)

#pybind11_add_module(hangman
#  examples/demo_pybind.cpp
#  ${SRC_FILES}
#)

## Installiere die Bibliothek
#install(TARGETS hangman
#  COMPONENT python
#  LIBRARY DESTINATION "${PROJECT_SOURCE_DIR}/extra"

include(FetchContent)
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

FetchContent_Declare(
  include(GoogleTest)
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
include(GoogleTest)

enable_testing()

add_executable(Spielertest test/Spielertest.cpp)
target_link_libraries(Spielertest GTest::gtest_main)
gtest_discover_tests(Spielertest)