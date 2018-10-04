CXX = g++
CXXFLAGS = -g -std=c++11 
INCS = -I./ -I../../src/ -I../src 
#TEST_FILES = ../src/catch.hpp
TEST_FILES = main.o
TEST_FILES += movement_tests.o
TEST_FILES += projectile_functional_tests.o



FILES = ../../src/GameField.o
FILES += ../../src/AsciiTankActor.o
FILES += ../../src/Actor.o
FILES += ../../src/MapData.o
FILES += ../../src/ProjectileActor.o

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

testAll: $(FILES) $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(INCS) -o testAll $(FILES) $(TEST_FILES)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

clean:
	rm -rf testAll *.o ../../src/*.o
