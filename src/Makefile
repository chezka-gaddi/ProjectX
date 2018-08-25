CXX = g++
CXXFLAGS = -g 
INCS = -I./  

FILES = main.cpp


platform: $(FILES) $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(INCS) -o platform $(FILES) $(TEST_FILES)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

clean:
	rm platform 
