CPP := g++
CPP_FLAGS := -Wall -Wextra -Werror -Wno-type-limits -Wno-unused-parameter -std=c++11 -I. -Ibuild/release -g
LINK_FLAGS := -lboost_unit_test_framework
TEST_CPP_FILES := $(wildcard tests/*.cpp)
TEST_OBJ_FILES := $(TEST_CPP_FILES:%.cpp=build/%.o)
EXAMPLES_CPP_FILES := $(wildcard examples/checkers/*.cpp examples/validators/*.cpp examples/generators/*.cpp)
EXAMPLES_RUN_FILES := $(EXAMPLES_CPP_FILES:%.cpp=build/%.bin)
EXAMPLES_OBJ_FILES := $(EXAMPLES_RUN_FILES:%.bin=%.o)
LIBRARIES := $(wildcard libs/*)
LIBRARIES := $(LIBRARIES:libs/%=%)

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

release: release-files test example
	@mkdir -p dist
	@echo copying to dist
	@cp -r build/release/* dist

release-files: build/release/testlib.hpp build/release/testlib.full.hpp $(LIBRARIES:%=build/release/%.hpp)

build/test: $(TEST_OBJ_FILES)
	@echo Build test
	@$(CPP) $(TEST_OBJ_FILES) $(LINK_FLAGS) -o build/test

build/release/testlib.hpp: testlib/**
	@echo "Make release header"
	@mkdir -p build/release
	@cp scripts/output_head.txt $@
	@scripts/headerSorter.py testlib >> $@

build/release/testlib.full.hpp: testlib/** libs/**
	@echo Make full edition
	@mkdir -p build/release
	@cp scripts/output_head.txt $@
	@scripts/headerSorter.py testlib libs >> $@

build/release/%.hpp: libs/%/**
	@echo Make $* lib
	@mkdir -p build/release
	@cp scripts/output_head.txt $@
	@scripts/makeLibrary.py libs/$* >> $@

build/%.bin: build/%.o
	@echo "Build $*"
	@$(CPP) $< $(LINK_FLAGS) -o $@

$(EXAMPLES_OBJ_FILES): release-files

build/%.o: %.cpp
	@mkdir -p build/$(*D)
	@echo Make dependencies for $*
	@$(CPP) -MM -MP -MT build/$*.o $(CPP_FLAGS) $*.cpp -o build/$*.d

	@echo "Compile $*"
	@$(CPP) $< $(CPP_FLAGS) -c -o $@


-include build/**/*.d
