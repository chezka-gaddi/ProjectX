CXX = g++
CXXFLAGS = -g 
INCS = -I./  

FILES = main.o
FILES += GameField.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

platform: $(FILES) $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(INCS) -o platform $(FILES) $(TEST_FILES)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

clean:
	rm -rf platform *.o
