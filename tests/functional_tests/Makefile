CXX = g++
CXXFLAGS = -g -std=c++11 
INCS = -I./ -I../../src/ -I../src 
#TEST_FILES = ../src/catch.hpp
#TEST_FILES += main.cpp
TEST_FILES = proof_of_concept_ft.cpp



#FILES = ../../src/test.cpp


testAll: $(FILES) $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(INCS) -o testAll main.o $(FILES) $(TEST_FILES)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

clean:
	rm testAll 
