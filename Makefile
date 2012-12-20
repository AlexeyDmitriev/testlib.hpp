CPP := g++
CPP_FLAGS := -Wall -Wextra -Werror -Wno-type-limits -Wno-unused-parameter -std=c++11 -I. -Ibuild/release
LINK_FLAGS := -lboost_unit_test_framework
TEST_CPP_FILES := $(wildcard tests/*.cpp)
TEST_OBJ_FILES := $(TEST_CPP_FILES:%.cpp=build/%.o)
EXAMPLES_CPP_FILES := $(wildcard examples/checkers/*.cpp examples/validators/*cpp)
EXAMPLES_OBJ_FILES := $(EXAMPLES_CPP_FILES:%.cpp=build/%.o)
EXAMPLES_RUN_FILES := $(EXAMPLES_OBJ_FILES:%.o=%.bin)
OBJ_FILES := $(TEST_OBJ_FILES) $(EXAMPLES_OBJ_FILES)
DEP_FILES := $(OBJ_FILES:%.o=%.d)
OUTPUT_FILES := exitCodes streamReader core verdictFunctions reader alias utility istream char string int float macro separator pair vector readerWrapper
OUTPUT_FILES := $(wildcard $(OUTPUT_FILES:%=testlib/%.hpp))

default:
	@echo "Default target disallowed"

test: build-tests
	@echo "Run test"
	@build/test

release: test example build/release/testlib.hpp
	@mkdir -p dist
	@cp build/release/testlib.hpp dist/testlib.hpp

example: build/release/testlib.hpp Makefile $(EXAMPLES_RUN_FILES)
	@echo "Run examples"
	@scripts/runExample.py --files $(EXAMPLES_CPP_FILES)

build/release/testlib.hpp: Makefile scripts/output_head.txt $(OUTPUT_FILES)
	@echo "Make realease header"
	@mkdir -p build/release
	@cp scripts/output_head.txt build/release/testlib.hpp
	@cat $(OUTPUT_FILES) | grep -v -e "^#pragma once" -e "^#include \"" >> build/release/testlib.hpp

EXAMPLE_OBJ_FILES: build/release/testlib.hpp

build-tests: $(TEST_OBJ_FILES) Makefile
	@echo "build test"
	@$(CPP) $(TEST_OBJ_FILES) $(LINK_FLAGS) -o build/test

build/%.bin: build/%.o Makefile
	@echo "build $*.bin"
	@$(CPP) $< $(LINK_FLAGS) -o $@

build/%.d: build/release/testlib.hpp %.cpp
	@mkdir -p build/$(*D)
	@echo Make dependencies for $*.cpp
	@$(CPP) -MM -MP -MT $@ -MT build/$*.o $(CPP_FLAGS) $*.cpp -o $@

clean:
	@echo "clean"
	@rm -rf build
	@rm -rf dist 

build/%.o: Makefile %.cpp
	@echo "Compile $*.o"
	@$(CPP) $*.cpp $(CPP_FLAGS) -c -o $@

include $(DEP_FILES)
