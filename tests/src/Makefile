CXX = g++
CXXFLAGS = -g -std=c++11 
INCS = -I./ -I../../src/ 
TEST_FILES = catch.hpp
TEST_FILES += main.cpp


#FILES = main.cpp
#FILES = ../../src/Actor.cpp
#FILES = ../../src/Actor.h
#FILES = ActorTesting.cpp


testAll: $(FILES) $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(INCS) -o testAll $(FILES) $(TEST_FILES)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

clean:
	rm testAll 
