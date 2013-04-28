CPP := g++
CPP_FLAGS := -Wall -Wextra -Werror -Wno-type-limits -Wno-unused-parameter -std=c++11 -I. -Ibuild/release -g
LINK_FLAGS := -lboost_unit_test_framework
TEST_CPP_FILES := $(wildcard tests/*.cpp)
TEST_OBJ_FILES := $(TEST_CPP_FILES:%.cpp=build/%.o)
EXAMPLES_CPP_FILES := $(wildcard examples/checkers/*.cpp examples/validators/*.cpp examples/generators/*.cpp)
EXAMPLES_RUN_FILES := $(EXAMPLES_CPP_FILES:%.cpp=build/%.bin)
EXAMPLES_OBJ_FILES := $(EXAMPLES_RUN_FILES:%.bin=%.o)

default:
	@echo Default target disallowed

test: build/test
	@echo Run test
	@build/test

example: $(EXAMPLES_RUN_FILES)
	@echo Run examples
	@scripts/runExample.py --files $(EXAMPLES_CPP_FILES)

clean:
	@echo clean
	@rm -rf build
	@rm -rf dist

release: build/release/testlib.hpp test example
	@mkdir -p dist
	@echo copying to dist
	@cp $< dist/testlib.hpp

build/test: $(TEST_OBJ_FILES)
	@echo Build test
	@$(CPP) $(TEST_OBJ_FILES) $(LINK_FLAGS) -o build/test

build/release/testlib.hpp: testlib/** 
	@echo "Make release header"
	@mkdir -p build/release
	@cp scripts/output_head.txt $@
	@scripts/headerSorter.py testlib >> $@

build/%.bin: build/%.o
	@echo "Build $*"
	@$(CPP) $< $(LINK_FLAGS) -o $@

$(EXAMPLES_OBJ_FILES): build/release/testlib.hpp

build/%.o: %.cpp
	@mkdir -p build/$(*D)
	@echo Make dependencies for $*
	@$(CPP) -MM -MP -MT build/$*.o $(CPP_FLAGS) $*.cpp -o build/$*.d

	@echo "Compile $*"
	@$(CPP) $< $(CPP_FLAGS) -c -o $@


-include build/**/*.d
