cmake_minimum_required(VERSION 3.25)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
set(CMAKE_VERBOSE_MAKEFILE ON)
project(StrangeCharacters-Refactoring-Kata VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

if(MINGW)
    add_compile_options(-Wno-attributes)
endif()

# uncomment these lines to enable coverage measurements using gcov
#set(CMAKE_CXX_FLAGS "--coverage")

enable_testing()
add_subdirectory(src)
add_subdirectory(test-catch2)
add_subdirectory(test-doctest)
add_subdirectory(test-gtest)

