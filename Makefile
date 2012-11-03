CPP := g++
CPP_FLAGS := -Wall -Wextra -Werror -std=c++11 -I. -Wno-type-limits
LINK_FLAGS := -lboost_unit_test_framework
CPP_FILES = $(wildcard tests/*.cpp)
OBJ_FILES = $(CPP_FILES:tests/%.cpp=build/%.o)
DEP_FILES = $(OBJ_FILES:%.o=%.d)

default:
	@echo "Default target disallowed"

test: build-tests
	@echo "run test"
	@build/test

build-tests: $(OBJ_FILES) 
	@echo "build test"
	@$(CPP) $(OBJ_FILES) $(LINK_FLAGS) -o build/test
	
build/%.d: tests/%.cpp
	@mkdir -p build
	@echo Make dependencies for $*.cpp
	@$(CPP) -MM -MP -MT build/$*.d -MT build/$*.o $(CPP_FLAGS) $< -o $@

clean:
	@echo "clean"
	@rm -rf build

build/%.o: 
	@echo "Compile $*.d"
	@$(CPP) $(@:build/%.o=tests/%.cpp) $(CPP_FLAGS) -c -o $@
																		
include $(DEP_FILES)
