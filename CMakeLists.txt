cmake_minimum_required(VERSION 3.27)
project(Project_2)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

include(FetchContent)
FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2
        USES_TERMINAL_DOWNLOAD ON
)
FetchContent_MakeAvailable(catch2)

include_directories(include)

add_library(primality_lib src/primality.cpp)
target_include_directories(primality_lib PUBLIC include)

# Add executable for tests, including the relevant source files
add_executable(primality_tests tests/primality_tests.cpp
)
target_link_libraries(primality_tests PRIVATE Catch2::Catch2WithMain primality_lib)

add_executable(find_primes src/find_primes.cpp)
target_link_libraries(find_primes PRIVATE primality_lib)

