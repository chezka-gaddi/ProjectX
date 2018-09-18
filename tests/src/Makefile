CXX = g++
CXXFLAGS = -g -std=c++11 -Dtesting
INCS = -I./ -I../../src/ 
TEST_FILES = main.o
TEST_FILES += ../../src/Actor.o
TEST_FILES += ActorTesting.o

#FILES = main.cpp
#FILES = ../../src/Actor.cpp
#FILES = ActorTesting.cpp


testAll: $(FILES) $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(INCS) -o testAll $(FILES) $(TEST_FILES)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

clean:
	rm testAll 
