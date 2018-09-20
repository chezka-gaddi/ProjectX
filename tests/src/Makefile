CXX = g++
CXXFLAGS = -g -std=c++11 -Dtesting
INCS = -I./ -I../../src/ 
TEST_FILES = catch.hpp
TEST_FILES += main.o
TEST_FILES += GameFeildTests.o
TEST_FILES += ../../src/GameField.o
TEST_FILES += ../../src/Actor.o


#FILES = ../../src/test.cpp

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

testAll: $(FILES) $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(INCS) -o testAll $(FILES) $(TEST_FILES)

clean:
	rm -rf testAll *.o
