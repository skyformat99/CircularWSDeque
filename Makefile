HDRS		:= $(wildcard include/*.h)
CMAKE_FILES	:= CMakeLists.txt include/CMakeLists.txt test/CMakeLists.txt

all: test

test-verbose: export BOOST_TEST_LOG_LEVEL=all
test-verbose: test

test: export CTEST_OUTPUT_ON_FAILURE=1
test:
	@mkdir -p build &&\
		cd build &&\
		cmake .. &&\
		cmake --build . &&\
		ctest

clean:
	@rm -rf Testing
	@rm -rf build

fmt:
	@$(foreach file,$(HDRS),clang-format -i $(file);)
	@$(foreach file,$(CMAKE_FILES),cmake-format -i $(file);)

.PHONY: test clean format
