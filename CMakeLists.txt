cmake_minimum_required(VERSION 2.8.12)
project(CodeAnalyzer)

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_definitions(-std=c++11)
endif()

file(GLOB CODE_ANALYZER_HEADER *.hpp)
add_executable(test_code_analyzer test_code_analyzer.cpp get_language_from_filename.cpp code_analyzer.cpp ${CODE_ANALYZER_HEADER})
add_test(NAME test_code_analyzer COMMAND  $<TARGET_FILE:test_code_analyzer>)

add_executable(test_get_language_from_filename test_get_language_from_filename.cpp get_language_from_filename.cpp ${CODE_ANALYZER_HEADER})
add_test(NAME test_get_language_from_filename COMMAND  $<TARGET_FILE:test_get_language_from_filename>)