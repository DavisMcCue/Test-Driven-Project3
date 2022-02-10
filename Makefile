# Makefile for markup_source_code() problem
#
# To build:
#   make
#
# To run tests in test_code_analyzer:
#   make test
#
# To clean build:
#   make clean
#
# To run tests in both test_get_language_from_filename and test_code_analyzer:
#   make testall

.PHONY.: all
all: test_code_analyzer test_get_language_from_filename

# test program for markup_source_code() and related functions
test_code_analyzer: test_code_analyzer.o code_analyzer.o get_language_from_filename.o
	g++ $^ -o $@

test_code_analyzer.o: test_code_analyzer.cpp
	g++ -std=c++11 -c $<

code_analyzer.o: code_analyzer.cpp code_analyzer.hpp xml_wrapper.hpp
	g++ -std=c++11 -c $<

# test program for get_language_from_filename()
test_get_language_from_filename: test_get_language_from_filename.o get_language_from_filename.o
	g++ $^ -o $@

get_language_from_filename.o: get_language_from_filename.cpp get_language_from_filename.hpp
	g++ -std=c++11 -c $<

test_get_language_from_filename.o: test_get_language_from_filename.cpp get_language_from_filename.hpp
	g++ -std=c++11 -c $<

.PHONY.: clean
clean :
	rm -f test_code_analyzer.o test_code_analyzer get_language_from_filename.o test_get_language_from_filename.o test_get_language_from_filename code_analyzer.o

.PHONY.: testall
testall: test_get_language_from_filename test_code_analyzer
	./test_get_language_from_filename
	./test_code_analyzer

.PHONY.: test
test: test_code_analyzer
	./test_code_analyzer
