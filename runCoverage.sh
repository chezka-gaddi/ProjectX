#!/bin/bash

make clean-tests
make coverage -j8
mkdir -p coverage

echo ""
echo "Running ./covTanks to create gco files"
./platform -coverage

echo ""
echo "Ceating gcda files"
gcov src/*.gcno

lcov --no-external --capture --initial --directory src --output-file coverage/platform_base.info
find src -type f -name '*.gc*' -exec rm {} +

#echo ""
#echo "Running gprof for timing"
#gprof ./platform > gprofresults.txt

echo "Creating test files"
make tests PROFILE="-pg -fprofile-arcs -ftest-coverage"

echo "Running Unit Test files"
./testUnitAll

echo ""
echo "Creating gcda files"
gcov src/*.gcno

lcov --no-external --capture --initial --directory src --output-file coverage/platform_unit.info
find src -type f -name '*.gc*' -exec rm {} +

echo ""
echo "Running Functional Test files"
./testFunctionalAll

echo ""
echo "Ceating gcda files"
gcov src/*.gcno

lcov --no-external --capture --initial --directory src --output-file coverage/platform_functional.info
find src -type f -name '*.gc*' -exec rm {} +

echo ""
echo "Creating report with lcov"
#lcov --no-external --directory src/ --capture --output-file coverage/coverage.info
lcov --no-external --add-tracefile coverage/platform_base.info \
        --add-tracefile coverage/platform_unit.info \
        --add-tracefile coverage/platform_functional.info \
        --output-file coverage/coverage.info

echo ""
echo "Cleaning up after, coverage files in coverage/ folder"
find . -type f -name '*.gc*' -exec rm {} +

echo ""
echo "Create a fancy web page"
lcov --summary coverage/coverage.info;
genhtml coverage/coverage.info --output-directory coverage -quiet;
