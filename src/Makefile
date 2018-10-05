CXX = g++
CXXFLAGS = -g -std=c++11 
INCS = -I./  

FILES = main.o
FILES += GameField.o
FILES += AsciiGameMisc.o
FILES += Actor.o
FILES += AsciiTankActor.o
FILES += MapData.o
FILES += ProjectileActor.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

platform: $(FILES) $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(INCS) -o platform $(FILES) $(TEST_FILES)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

clean:
	rm -rf platform *.o
