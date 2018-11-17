#!/bin/bash
#make clean-all
make -j8

echo ""
echo "Running ./covTanks to create gco files"
./platform

echo ""
echo "Running gprof for timing"
gprof ./platform > gprofresults.txt

echo ""
echo "Ceating gcda files"
gcov src/*.gcno

echo ""
echo "Creating report with lcov"
mkdir -p coverage
lcov --no-external --directory src/ --capture --output-file coverage/coverage.info

echo ""
echo "Cleaning up after, coverage files in coverage/ folder"
#find . -type f -name '*.gc*' -exec rm {} +

echo ""
echo "Create a fancy web page"
lcov --summary coverage/coverage.info;
genhtml coverage/coverage.info --output-directory coverage -quiet;
