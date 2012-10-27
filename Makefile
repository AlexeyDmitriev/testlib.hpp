CPP := g++
CPP_FLAGS := -Wall -Wextra -Werror -std=c++11 -I.
LINK_FLAGS := -lboost_unit_test_framework
TEST_CPP_FILES = $(wildcard tests/*.cpp)
TEST_OBJ_FILES = $(TEST_CPP_FILES:%.cpp=build/%.o)
EXAMPLES_CPP_FILES = $(wildcard examples/checkers/*.cpp)
EXAMPLES_OBJ_FILES = $(EXAMPLES_CPP_FILES:%.cpp=build/%.o)
EXAMPLES_RUN_FILES = $(EXAMPLES_OBJ_FILES:%.o=%.bin)
OBJ_FILES = $(TEST_OBJ_FILES) $(EXAMPLES_OBJ_FILES)
DEP_FILES = $(OBJ_FILES:%.o=%.d)

default:
	@echo "Default target disallowed"

test: build-tests
	@echo "run test"
	@build/test

examples: $(EXAMPLES_RUN_FILES) 
	@echo "run examples"
	@scripts/runExamples.py $(EXAMPLES_CPP_FILES)

build-tests: $(TEST_OBJ_FILES) 
	@echo "build test"
	@$(CPP) $(TEST_OBJ_FILES) $(LINK_FLAGS) -o build/test

build/%.bin: build/%.o
	@echo "build $*.bin"
	@$(CPP) $< $(LINK_FLAGS) -o $@

build/%.d: %.cpp
	@mkdir -p build/$(*D)
	@echo Make dependencies for $*.cpp
	@$(CPP) -MM -MP -MT $@ -MT build/$*.o $(CPP_FLAGS) $< -o $@

clean:
	@echo "clean"
	@rm -rf build

build/%.o: 
	@echo "Compile $*.o"
	@$(CPP) $*.cpp $(CPP_FLAGS) -c -o $@
																		
include $(DEP_FILES)
