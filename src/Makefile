CXX = g++
CXXFLAGS = -g -std=c++11 
INCS = -I./
LIBS = -ldl

FILES = main.o
FILES += GameField.o
FILES += AsciiGameMisc.o
FILES += Actor.o
FILES += AsciiTankActor.o
FILES += MapData.o
FILES += ProjectileActor.o
FILES += ActorInfo.o
FILES += DynamicLoader.o
Files += DynamicAsciiGame.o
FILES += SimpleAI.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

platform: $(FILES) $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(INCS) -o platform $(FILES) $(TEST_FILES) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

clean:
	rm -rf platform *.o
