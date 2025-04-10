cmake_minimum_required(VERSION 3.10)
project(heap)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE test_heap.cpp ArrayMaxHeap.hpp ArrayMaxHeap.tpp)

add_executable(test-heap catch.hpp abstract_heap.hpp ${SOURCE})

enable_testing()

add_test(test-heap test-heap)

add_custom_target(submission COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/problem8_submission.zip" --format=zip
    ${SOURCE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(starter_download COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/../problem8_starter.zip" --format=zip
    ${SOURCE} CMakeLists.txt catch.hpp abstract_heap.hpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})