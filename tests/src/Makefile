CXX = g++
CXXFLAGS = -g -std=c++11
INCS = -I./ -I../../src/ 
TEST_FILES = catch.hpp
TEST_FILES += main.o
TEST_FILES += GameFeildTests.o
TEST_FILES += ../../src/GameField.o
TEST_FILES += ../../src/SimpleActor.o
TEST_FILES += SimpleActorTests.o
#TEST_FILES += ActorTesting.o
#TEST_FILES += ProjectileActorTest.o

FILES = ../../src/Actor.o
#FILES += ../../src/ProjectileActor.o
TEST_FILES += ../../src/ActorInfo.o

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

testAll: $(FILES) $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(INCS) -o testAll $(FILES) $(TEST_FILES)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

clean:
	rm -rf testAll *.o ../../src/*.o
