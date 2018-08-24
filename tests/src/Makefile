CXX = g++
CXXFLAGS = -g 
INCS = -I./ -I../../src 
TEST_FILES = catch.hpp
TEST_FILES += main.cpp



FILES = ../../src/


testAll: $(FILES) $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(INCS) -o testAll $(FILES) $(TEST_FILES)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

clean:
	rm testAll 
