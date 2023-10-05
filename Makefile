COMPILER = g++
COMPILER_VERSION = -std=c++2a
COMPILER_FLAGS = ${COMPILER_VERSION} -O3

WARNINGS = -pedantic -pedantic-errors -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wswitch-default -Wundef -Wno-unused -Wfloat-equal -Wconversion -Winline -Wzero-as-null-pointer-constant -Wmissing-noreturn -Wunreachable-code -Wvariadic-macros -Wwrite-strings -Wunsafe-loop-optimizations -Werror

INCLUDE_FOLDER = .\/include
INCLUDE_ARGUMENT = -I${INCLUDE_FOLDER}
LIBRARIES =
RESOURCES_FOLDER = .\/resources

SOURCE_FOLDER = .\/src
SOURCES = $(shell find ${SOURCE_FOLDER} -name '*.cpp')

OUTPUT_FOLDER = .\/build
OUTPUT_FILE = main

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --verbose -s --track-origins=yes

TEST_FOLDER = .\/tests
TEST_SOURCES = $(shell find ${TEST_FOLDER} ${SOURCE_FOLDER} -type f -not -path '*/main.cpp' -name '*.cpp')
TEST_COMPILER_FLAGS = ${COMPILER_VERSION} --coverage -fPIC -O0
TEST_INCLUDE_FOLDER = .\/includeTests
TEST_INCLUDE_ARGUMENT = -I${TEST_INCLUDE_FOLDER}
TEST_LIBRARIES = ${LIBRARIES} -lgtest
TEST_RESOURCES =
TEST_OUTPUT_FOLDER = .\/testing
TEST_OUTPUT_FILE = test

BRANCH_COVERAGE = --rc lcov_branch_coverage=1

LCOV_FILES = $(shell find . -name '*.gcno' -o -name '*.gcda' -o -name '*.info')
LCOV_FLAGS = --no-external --capture ${BRANCH_COVERAGE} -d .
LCOV_OUTPUT_FOLDER = ${TEST_OUTPUT_FOLDER}
LCOV_OUTPUT_FILE = coverage.info
LCOV_REMOVE_FILES = '*/${TEST_FOLDER}/*' '*/${INCLUDE_FOLDER}/*'

GENHTML_FLAGS = ${BRANCH_COVERAGE}
GENHTML_OUTPUT_FOLDER = .\/coverage

TIDY_SOURCES = ${SOURCES}
TIDY_INCLUDE_CHECKS = *
TIDY_IGNORE_CHECKS = -llvmlibc-callee-namespace,-llvmlibc-implementation-in-namespace,-modernize-use-trailing-return-type,-fuchsia-default-arguments-calls
TIDY_OUTPUT_FILE = .clang-tidy
TIDY_COMPILE_FLAGS = -extra-arg=-std=c++20 --config-file=${TIDY_OUTPUT_FILE}

DOXYGEN_FILE_NAME = Doxyfile
DOXYGEN_PROJECT_NAME = "Database Normalizer"
DOXYGEN_PROJECT_NUMBER = 1.0.0
DOXYGEN_PROJECT_BRIEF = "Create an application to normalize a given sql dataset and their functional dependencies up to 5NF"
DOXYGEN_OUTPUT_DIRECTORY = .\/docs\/
DOXYGEN_EXTRACT_PRIVATE = YES
DOXYGEN_EXTRACT_PRIVATE_VIRTUAL = YES
DOXYGEN_EXTRACT_STATIC = YES
DOXYGEN_WARN_LOGFILE = "${DOXYGEN_OUTPUT_DIRECTORY}warnings.log"
DOXYGEN_RECURSIVE = YES
DOXYGEN_EXCLUDE = "${DOXYGEN_OUTPUT_DIRECTORY}" "${TEST_FOLDER}"
DOXYGEN_GENERATE_HTML = NO
DOXYGEN_GENERATE_LATEX = NO
DOXYGEN_GENERATE_XML = YES

default: compile

compile: ${SOURCES}
	${MAKE} create_folders
	${COMPILER} ${COMPILER_FLAGS} ${WARNINGS} ${INCLUDE_ARGUMENT} $^  ${LIBRARIES} -o ${OUTPUT_FOLDER}/${OUTPUT_FILE}
	cp -r ${RESOURCES_FOLDER} ${OUTPUT_FOLDER}

run: compile
	${OUTPUT_FOLDER}/${OUTPUT_FILE}

debug: ${SOURCES}
	${COMPILER} ${COMPILER_FLAGS} ${WARNINGS} ${INCLUDE_ARGUMENT} -g $^ ${LIBRARIES} -o ${OUTPUT_FOLDER}/${OUTPUT_FILE}

valgrind: debug
	valgrind ${VALGRIND_FLAGS} ${OUTPUT_FOLDER}/${OUTPUT_FILE}

delete_lcov: ${LCOV_FILES}
	rm -rf $^
	mkdir -p ${TEST_OUTPUT_FOLDER}

.PHONY: copy_and_run_test
copy_and_run_test:
	cp -r ${RESOURCES_FOLDER} ${OUTPUT_FOLDER}
	cp ${TEST_OUTPUT_FOLDER}/${TEST_OUTPUT_FILE} ${OUTPUT_FOLDER}/${TEST_OUTPUT_FILE}
	${OUTPUT_FOLDER}/${TEST_OUTPUT_FILE}

build_test: ${TEST_SOURCES}
	${MAKE} create_folders
	${MAKE} delete_lcov
	${COMPILER} ${TEST_COMPILER_FLAGS} ${WARNINGS} ${INCLUDE_ARGUMENT} ${TEST_INCLUDE_ARGUMENT} $^ ${TEST_LIBRARIES} -o ${TEST_OUTPUT_FOLDER}/${TEST_OUTPUT_FILE}
	${MAKE} copy_and_run_test

lcov: build_test
	mkdir -p ${LCOV_OUTPUT_FOLDER}
	lcov ${LCOV_FLAGS} -o ${LCOV_OUTPUT_FOLDER}/${LCOV_OUTPUT_FILE}
	lcov --remove ${LCOV_OUTPUT_FOLDER}/${LCOV_OUTPUT_FILE} ${LCOV_REMOVE_FILES} ${BRANCH_COVERAGE} -o ${LCOV_OUTPUT_FOLDER}/${LCOV_OUTPUT_FILE}

genhtml: lcov
	rm -rf ${GENHTML_OUTPUT_FOLDER}
	mkdir -p ${GENHTML_OUTPUT_FOLDER}
	genhtml ${LCOV_OUTPUT_FOLDER}/${LCOV_OUTPUT_FILE} ${BRANCH_COVERAGE} --output-directory ${GENHTML_OUTPUT_FOLDER}

coverage: genhtml
	rm -rf ${TEST_OUTPUT_FOLDER}
	rm -rf ${LCOV_OUTPUT_FOLDER}

.PHONY: tidy_setup fix_tidy_warnings
tidy_setup:
	clang-tidy -checks=${TIDY_INCLUDE_CHECKS},${TIDY_IGNORE_CHECKS} --dump-config > ${TIDY_OUTPUT_FILE}

fix_tidy_warnings:
	perl -p0e 's/cert-err09-cpp.MaxSize\n    value:           \x27-1\x27/cert-err09-cpp.MaxSize\n    value:           \x272147483647\x27/' .clang-tidy > test.txt
	cp test.txt .clang-tidy
	perl -p0e 's/cert-err61-cpp.MaxSize\n    value:           \x27-1\x27/cert-err61-cpp.MaxSize\n    value:           \x272147483647\x27/' .clang-tidy > test.txt
	cp test.txt .clang-tidy
	perl -p0e 's/misc-throw-by-value-catch-by-reference.MaxSize\n    value:           \x27-1\x27/misc-throw-by-value-catch-by-reference.MaxSize\n    value:           \x272147483647\x27/' .clang-tidy > test.txt
	cp test.txt .clang-tidy
	rm test.txt

tidy: ${TIDY_SOURCES}
	${MAKE} tidy_setup
	${MAKE} fix_tidy_warnings
	clang-tidy ${TIDY_COMPILE_FLAGS} $^ -- ${INCLUDE_ARGUMENT}

.PHONY: create_folders create_doxygen create_breathe_file create_index_rst_file
create_doxygen:
	doxygen -g ${DOXYGEN_FILE_NAME}

change_doxygen_options: create_doxygen
	sed -i 's/PROJECT_NAME           = "My Project"/PROJECT_NAME           = ${DOXYGEN_PROJECT_NAME}/g' ${DOXYGEN_FILE_NAME}
	sed -i 's/PROJECT_NUMBER         =/PROJECT_NUMBER         = ${DOXYGEN_PROJECT_NUMBER}/g' ${DOXYGEN_FILE_NAME}
	sed -i 's/PROJECT_BRIEF          =/PROJECT_BRIEF          = ${DOXYGEN_PROJECT_BRIEF}/g' ${DOXYGEN_FILE_NAME}
	sed -i 's/OUTPUT_DIRECTORY       =/OUTPUT_DIRECTORY       = "${DOXYGEN_OUTPUT_DIRECTORY}"/g' ${DOXYGEN_FILE_NAME}
	sed -i 's/EXTRACT_PRIVATE        = NO/EXTRACT_PRIVATE        = ${DOXYGEN_EXTRACT_PRIVATE}/g' ${DOXYGEN_FILE_NAME}
	sed -i 's/EXTRACT_PRIV_VIRTUAL   = NO/EXTRACT_PRIV_VIRTUAL   = ${DOXYGEN_EXTRACT_PRIVATE_VIRTUAL}/g' ${DOXYGEN_FILE_NAME}
	sed -i 's/EXTRACT_STATIC         = NO/EXTRACT_STATIC         = ${DOXYGEN_EXTRACT_STATIC}/g' ${DOXYGEN_FILE_NAME}
	sed -i 's/WARN_LOGFILE           =/WARN_LOGFILE           = ${DOXYGEN_WARN_LOGFILE}/g' ${DOXYGEN_FILE_NAME}
	sed -i 's/RECURSIVE              = NO/RECURSIVE              = ${DOXYGEN_RECURSIVE}/g' ${DOXYGEN_FILE_NAME}
	sed -i 's/EXCLUDE                =/EXCLUDE                = ${DOXYGEN_EXCLUDE}/g' ${DOXYGEN_FILE_NAME}
	sed -i 's/GENERATE_HTML          = YES/GENERATE_HTML          = ${DOXYGEN_GENERATE_HTML}/g' ${DOXYGEN_FILE_NAME}
	sed -i 's/GENERATE_LATEX         = YES/GENERATE_LATEX         = ${DOXYGEN_GENERATE_LATEX}/g' ${DOXYGEN_FILE_NAME}
	sed -i 's/GENERATE_XML           = NO/GENERATE_XML           = ${DOXYGEN_GENERATE_XML}/g' ${DOXYGEN_FILE_NAME}

create_breathe_file:
	echo "from cgitb import html\n" > conf.py

	echo "extensions = [\"breathe\"]\n" >> conf.py

	echo "html_theme = \"sphinx_rtd_theme\"\n" >> conf.py

	echo "# Breathe configuration" >> conf.py
	echo "breathe_default_project = \"testing\"" >> conf.py
	echo "breathe_default_members = (\"members\", \"protected-members\", \"private-members\")" >> conf.py

create_index_rst_file:
	touch index.rst
	echo "My Project Documentation" >> index.rst
	echo "========================\n" >> index.rst

	echo ".. toctree::" >> index.rst
	echo "\t:maxdepth: 2\n" >> index.rst

	echo "C++ Namespaces" >> index.rst
	echo "--------------" >> index.rst

	echo ".. doxygennamespace:: testing" >> index.rst

determine_index_rst_exists: create_breathe_file
	[ -f ./index.rst ] || ${MAKE} create_index_rst_file

doxygen_complete: change_doxygen_options
	doxygen ${DOXYGEN_FILE_NAME}
	rm -f ${DOXYGEN_FILE_NAME}.bak

docs: doxygen_complete
	${MAKE} determine_index_rst_exists
	sphinx-build -b html -Dbreathe_projects.testing=${DOXYGEN_OUTPUT_DIRECTORY}/xml . ${DOXYGEN_OUTPUT_DIRECTORY}/sphinx/

create_folders:
	mkdir -p ${SOURCE_FOLDER}
	mkdir -p ${RESOURCES_FOLDER}
	mkdir -p ${INCLUDE_FOLDER}
	mkdir -p ${OUTPUT_FOLDER}
	mkdir -p ${TEST_FOLDER}